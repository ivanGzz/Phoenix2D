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

#include "GAlgorithm.hpp"
#include <boost/random.hpp>
#include <ctime>

namespace Genetics {

GAlgorithm::GAlgorithm(double p_cross, double p_mutation) {
	generations = 0;
	this->p_cross = p_cross;
	this->p_mutation = p_mutation;
	max_var_size = 8 * sizeof(int);
}

GAlgorithm::~GAlgorithm() {

}

void GAlgorithm::addVariable(int bits) {
	if (bits > max_var_size) {
		return;
	}
	Variable var;
	var.bits = bits;
	int ones = 0;
	for (int i = 0; i < bits; ++i) {
		ones = ones | 1;
		ones = ones << 1;
	}
	var.ones = ones;
	variables.push_back(var);
}

void GAlgorithm::generatePopulation(int size) {
	boost::mt19937 rng(time(0));
	boost::uniform_real<> dist(0.0, 1.0);
	for (int p = 0; p < size; ++p) {
		Individual individual;
		for (int i = 0; i < variables.size(); ++i) {
			int var = 0;
			for (int j = 0; j < variables[i].bits; ++j) {
				if (dist(rng) > 0.5) {
					var = mutate(var, j);
				}
			}
			individual.variables.push_back(var);
		}
		individual.fit = 0.0;
		generation.push_back(individual);
	}
}

void GAlgorithm::runGeneration(bool per_individual) {
	double total_fit = 0.0;
	for (std::vector<Individual>::iterator it = generation.begin(); it != generation.end(); ++it) {
		total_fit += it->fit;
	}
	if (total_fit > 0) {
		for (std::vector<Individual>::iterator it = generation.begin(); it != generation.end(); ++it) {
			it->fit = it->fit / total_fit;
		}
	} else {
		return;
	}
	std::vector<Individual> new_gen;
	boost::mt19937 rng(time(0));
	boost::uniform_int<>  ndist(0, variables.size() - 1);
	boost::uniform_real<> rdist(0.0, 1.0);
	double p_inv = 1.0 / generation.size();
	double r = p_inv * rdist(rng);
	double c = generation[0].fit;
	int i = 1;
	Individual first;
	for (int j = 0; j < 2 * generation.size(); ++j) {
		double u = r + p_inv * (double)j;
		while (u > c) {
			i = (i + 1) % generation.size();
			c += generation[i].fit;
		}
		//std::cout << j << ": Chose " << i << " with fit " << generation[i].fit << " and u " << u << std::endl;
		if (j % 2 == 0) {
			first = generation[i];
		} else {
			Individual second = generation[i];
			if (rdist(rng) < p_cross) {
				Individual child;
				child.fit = 0.0;
				child.variables.resize(variables.size());
				if (per_individual) {
					int var = ndist(rng);
					boost::uniform_int<> bdist(0, variables[var].bits);
					int bit = bdist(rng);
					for (int k = 0; k < variables.size(); k++) {
						if (k == var) {
							child.variables[k] = cross(first.variables[k], second.variables[k], k, bit);
						} else if (k < var) {
							child.variables[k] = first.variables[k];
						} else {
							child.variables[k] = second.variables[k];
						}
					}
				} else {
					for (int k = 0; k < variables.size(); k++) {
						boost::uniform_int<> bdist(1, variables[k].bits);
						int bit = bdist(rng);
						child.variables[k] = cross(first.variables[k], second.variables[k], k, bit);
					}
				}
				new_gen.push_back(child);
			} else {
				if (first.fit > second.fit) {
					new_gen.push_back(first);
				} else {
					new_gen.push_back(second);
				}
			}
			if (rdist(rng) < p_mutation) {
				int var = ndist(rng);
				boost::uniform_int<> bdist(0, variables[var].bits - 1);
				int bit = bdist(rng);
				new_gen.back().variables[var] = mutate(new_gen.back().variables[var], bit);
			}
		}
	}
	generation = new_gen;
	generations++;
}

std::vector<Individual>::iterator GAlgorithm::begin() {
	return generation.begin();
}

std::vector<Individual>::iterator GAlgorithm::end() {
	return generation.end();
}

int GAlgorithm::cross(int var_a, int var_b, int index, int bit) {
	int upper_mask = variables[index].ones << bit;
	int lower_mask = variables[index].ones >> (variables[index].bits - bit);
	var_a = var_a & upper_mask;
	var_b = var_b & lower_mask;
	return var_a | var_b;
}

int GAlgorithm::mutate(int var, int bit) {
	int mask = 1 << bit;
	return var ^ mask;
}

}
