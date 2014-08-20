/*
 * Phoenix2D (RoboCup Soccer Simulation 2D League)
 * Copyright (c) 2013 Ivan Gonzalez
 *
 * This file is part of Phoenix2D.
 *
 * Phoenix2D is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Phoenix2D is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Phoenix2D.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Based on:
 *     Probabilistic Robotics
 *     Sebastian Thruns
 */

#ifndef PFILTER_HPP_
#define PFILTER_HPP_

#include "constants.hpp"
#include <ctime>
#include <boost/random.hpp>
#include <cmath>

namespace Filters {

template <unsigned int N>
struct Particle {
	double dimension[N];
	double weight;
};

template <unsigned int N>
class PFilter {
public:
	PFilter();
	~PFilter();
	void initWithBelief(double mu[N], double dev[N]);
	void update(void(* weight)(Particle<N> &p));
	void predict(void(* predict)(Particle<N> &p));
	void resample();
	double getMean(int n);
	double getVariance(int n);
	double getFit();
	void computeParameters();
private:
	Particle<N> particles[Filters::PARTICLES];
	double means[N];
	double variances[N];
	double w_slow;
	double w_fast;
	double a_slow;
	double a_fast;
	double w_avg;
	double mu[N];
	double dev[N];
	double total_w;
	double fit;
};

template <unsigned int N>
PFilter<N>::PFilter() {
	for (int i = 0; i < N; ++i) {
		means[i] = 0.0;
		variances[i] = 0.0;
	}
	total_w = 1.0;
	fit = 1.0;
	w_slow = 0.0;
	w_fast = 0.0;
	a_slow = 0.1;
	a_fast = 2.0;
	w_avg = 0.0;
}

template <unsigned int N>
PFilter<N>::~PFilter() {

}

template <unsigned int N>
void PFilter<N>::initWithBelief(double mu[N], double dev[N]) {
	for (int i = 0; i < N; ++i) {
		this->mu[i] = mu[i];
		this->dev[i] = dev[i];
	}
	boost::mt19937 rng(time(0));
	for (int i = 0; i < N; ++i) {
		boost::uniform_real<> p_dist(0.0, 2.0 * dev[i]);
		for (int j = 0; j < PARTICLES; ++j) {
			particles[j].dimension[i] = mu[i] - dev[i] + p_dist(rng);
		}
	}
	for (int i = 0; i < PARTICLES; ++i) {
		particles[i].weight = 1.0 / PARTICLES;
	}
}

template <unsigned int N>
void PFilter<N>::resample() {
	w_slow = w_slow + a_slow * (w_avg - w_slow);
	w_fast = w_fast + a_fast * (w_avg - w_fast);
	Particle<N> new_particles[PARTICLES];
	boost::mt19937 rng(time(0));
	boost::uniform_real<> rdist(0.0, 1.0);
	double r = (1.0 / PARTICLES) * rdist(rng);
	double c = particles[0].weight;
	int i = 1;
	for (int j = 0; j < PARTICLES; ++j) {
		if (w_slow != 0.0 && (rdist(rng) < 1.0 - w_fast / w_slow)) {
			std::cout << "Filling" << std::endl;
			boost::uniform_real<> dist(0, 2.0 * dev[i]);
			Particle<N> p;
			for (int k = 0; k < N; ++k) {
				p.dimension[k] = means[k] - dev[k] + dist(rng);
			}
			new_particles[j] = p;
		} else {
			double u = r + ((double)j) * (1.0 / PARTICLES);
			while (u > c) {
				i = (i + 1) % PARTICLES;
				c += particles[i].weight;
			}
			new_particles[j] = particles[i];
		}
	}
	total_w = 0.0;
	for (i = 0; i < PARTICLES; ++i) {
		particles[i] = new_particles[i];
		total_w += particles[i].weight;
	}
	fit = total_w;
	// Re-normalize
	double total_w_bu = 0.0;
	for (int i = 0; i < PARTICLES; ++i) {
		particles[i].weight /= total_w;
		total_w_bu += particles[i].weight;
	}
	total_w = total_w_bu;
}

template <unsigned int N>
void PFilter<N>::predict(void(* predict)(Particle<N> &p)) {
	for (int i = 0; i < PARTICLES; ++i) {
		predict(particles[i]);
	}
}

template <unsigned int N>
void PFilter<N>::update(void(* update)(Particle<N> &p)) {
	total_w = 0.0;
	for (int i = 0; i < PARTICLES; ++i) {
		update(particles[i]);
		total_w += particles[i].weight;
	}
	fit = total_w;
	// Re-normalize
	double total_w_bu = 0.0;
	for (int i = 0; i < PARTICLES; ++i) {
		particles[i].weight /= total_w;
		total_w_bu += particles[i].weight;
		w_avg += particles[i].weight / PARTICLES;
	}
	total_w = total_w_bu;
}

template <unsigned int N>
double PFilter<N>::getMean(int n) {
	return means[n];
}

template <unsigned int N>
double PFilter<N>::getVariance(int n) {
	return variances[n];
}

template <unsigned int N>
double PFilter<N>::getFit() {
	return fit;
}

template <unsigned int N>
void PFilter<N>::computeParameters() {
	for (int i = 0; i < N; ++i) {
		means[i] = 0.0;
		variances[i] = 0.0;
		for (int j = 0; j < PARTICLES; ++j) {
			means[i] += particles[j].dimension[i] * particles[j].weight;
		}
		means[i] /= total_w;
		variances[i] = 0.0;
		for (int j = 0; j < PARTICLES; ++j) {
			variances[i] += pow(means[i] - particles[j].dimension[i], 2.0);
		}
		variances[i] /= (PARTICLES - 1);
	}
}

}

#endif /* PFILTER_HPP_ */
