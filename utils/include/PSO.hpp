/*
 * Phoenix2D (RoboCup Soccer Simulation 2D League)
 * Copyright (c) 2013 - 2015 Nelson I. Gonzalez
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
 *
 * @file PSO.hpp
 *
 * @author Nelson I. Gonzalez
 */

#include <iostream>
#include <boost/random.hpp>
#include <ctime>
#include <algorithm>
#define PARTICLES 40
#define INFORMANTS 6

/*
 * Based on
 *   Particle Swarm Optimization
 *   Maurice Clerc
 */

/*!
 *
 */
template<unsigned int N>
struct Particle {
	double dimension[N];
	double velocity[N];
	double best_found[N];
	double best_shared[N];
};

/*!
 *
 */
template <unsigned int N>
class PSO {
	/*!
	 *
	 */
	typedef bool (* function)(double p0[N], double p1[N]); // must return true if p0 is better than p1 and false if p1 is better than p0
public:
	/*!
	 *
	 */
	PSO(function compare, double c1 = 0.7, double c_max = 1.47);
	/*!
	 *
	 */
	~PSO();
	/*!
	 *
	 */
	void initWithSearchSpace(double lowers[N], double uppers[N]);
	/*!
	 *
	 */
	void evaluate();
	/*!
	 *
	 */
	double* getBestFound();
private:
	double c1;							///<
	double c_max;						///<
	function compare;					///<
	Particle<N> particles[PARTICLES];	///<
	double best_global[N];				///<
};

template <unsigned int N>
PSO<N>::PSO(function compare, double c1, double c_max) {
	this->c1 = c1;
	this->c_max = c_max;
	this->compare = compare;
	for (int i = 0; i < N; ++i) {
		best_global[i] = 10.0;
	}
}

template <unsigned int N>
PSO<N>::~PSO() {

}

template <unsigned int N>
void PSO<N>::initWithSearchSpace(double lowers[N], double uppers[N]) {
	boost::mt19937 rng(time(0));
	for (int i = 0; i < N; ++i) {
		boost::uniform_real<> rdist(lowers[i], uppers[i]);
		for (int j = 0; j < PARTICLES; ++j) {
			double val = rdist(rng);
			particles[j].dimension[i] = val;
			particles[j].velocity[i] = 0.0;
			particles[j].best_found[i] = val;
			particles[j].best_shared[i] = val;
		}
	}
}

template <unsigned int N>
void PSO<N>::evaluate() {
	// Evaluate new positions
	for (int i = 0; i < PARTICLES; ++i) {
		if (compare(particles[i].dimension, particles[i].best_found)) {
			std::copy(particles[i].dimension, particles[i].dimension + N, particles[i].best_found);
		}
		if (compare(particles[i].best_found, best_global)) {
			std::copy(particles[i].dimension, particles[i].dimension + N, best_global);
		}
	}
	// Using random informants
	boost::mt19937 rng(time(0));
	boost::uniform_int<> idist(0, PARTICLES - 1);
	for (int i = 0; i < PARTICLES; ++i) {
		for (int j = 0; j < INFORMANTS; ++j) {
			int p = idist(rng);
			if (compare(particles[p].best_shared, particles[i].best_found)) {
				std::copy(particles[p].best_found, particles[p].best_found + N, particles[i].best_shared);
			}
		}
	}
	// Update positions
	boost::uniform_real<> rdist(0.0, 1.0);
	for (int i = 0; i < PARTICLES; ++i) {
		for (int j = 0; j < N; ++j) {
			particles[i].velocity[j] = c1 * particles[i].velocity[j] 
				+ c_max * rdist(rng) * (particles[i].best_found[j] - particles[i].dimension[j])
				+ c_max * rdist(rng) * (particles[i].best_shared[j] - particles[i].dimension[j]);
			particles[i].dimension[j] += particles[i].velocity[j];
		}	
	}
}

template <unsigned int N>
double* PSO<N>::getBestFound() {
	return best_global;
}