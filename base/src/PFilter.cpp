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
 *
 */

#include "PFilter.hpp"
#include <ctime>
#include <boost/random.hpp>
#include <cmath>

namespace Phoenix {

PFilter::PFilter() {
	boost::mt19937 rng(time(0));
	boost::uniform_int<> xdist(0, 11500);
	boost::uniform_int<> ydist(0, 7800);
	boost::uniform_int<> ddist(0, 36000);
	for (int i = 0; i < Filter::PARTICLES; ++i) {
		double x = ((double)xdist(rng)) / 100.0 - 57.5;
		double y = ((double)ydist(rng)) / 100.0 - 39.0;
		double dir = ((double)ddist(rng)) / 100.0 - 180.0;
		Particle p = {x, y, dir, 1.0 / Filter::PARTICLES};
		set[i] = p;
	}
	mean = 1.0 / Filter::PARTICLES;
	variance = 0.0;
	x_mean = 0.0;
	y_mean = 0.0;
	dir_mean = 0.0;
}

PFilter::~PFilter() {

}

void PFilter::resample() {
	Particle newSet[Filter::PARTICLES];
	boost::mt19937 rng(time(0));
	boost::uniform_int<> rdist(0, 1000);
	double r = (1.0 / Filter::PARTICLES) * ((double)rdist(rng)) / 1000.0;
	double c = set[0].weight;
	int i = 1;
	for (int j = 0; j < Filter::PARTICLES; ++j) {
		double u = r + ((double)j) * (1.0 / Filter::PARTICLES);
		while (u > c) {
			i = (i + 1) % Filter::PARTICLES;
			c += set[i].weight;
		}
		newSet[j] = set[i];
	}
	for (i = 0; i < Filter::PARTICLES; ++i) {
		set[i] = newSet[i];
	}
	computeParams();
}

void PFilter::predict(void(* predict)(Particle &particle)) {
	for (int i = 0; i < Filter::PARTICLES; ++i) {
		predict(set[i]);
	}
}

void PFilter::update(void(* weight)(Particle &particle)) {
	double total_w = 0.0;
	for (int i = 0; i < Filter::PARTICLES; ++i) {
		weight(set[i]);
		total_w += set[i].weight;
	}
	//Normalize
	for (int i = 0; i < Filter::PARTICLES; ++i) {
		set[i].weight /= total_w;
	}
	computeParams();
}

void PFilter::computeParams() {
	mean = 0.0;
	x_mean = 0.0;
	y_mean = 0.0;
	dir_mean = 0.0;
	variance = 0.0;
	double dir_x_mean = 0.0;
	double dir_y_mean = 0.0;
	for (int i = 0; i < Filter::PARTICLES; ++i) {
		mean += set[i].weight;
		x_mean += set[i].x * set[i].weight;
		y_mean += set[i].y * set[i].weight;
		dir_x_mean += cos(Math::PI * set[i].direction / 180.0) * set[i].weight;
		dir_y_mean += sin(Math::PI * set[i].direction / 180.0) * set[i].weight;
	}
	x_mean /= mean;
	y_mean /= mean;
	dir_x_mean /= mean;
	dir_y_mean /= mean;
	dir_mean = 180.0 * atan2(dir_y_mean, dir_x_mean) / Math::PI;
	mean /= Filter::PARTICLES;
	for (int i = 0; i < Filter::PARTICLES; ++i) {
		variance += set[i].weight * set[i].weight;
	}
	variance = variance / (Filter::PARTICLES - 1);
}

}
