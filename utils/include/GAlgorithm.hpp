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

#ifndef GALGORITHM_HPP_
#define GALGORITHM_HPP_

#include <vector>

namespace Genetics {

struct Variable {
	int bits;
	int ones;
};

struct Individual {
	std::vector<int> variables;
	double fit;
};

/*!
 * Example:
 * Bin packing problem: http://people.sc.fsu.edu/~jburkardt/datasets/bin_packing/bin_packing.html dataset P02
 *
 * #include "GAlgorithm.hpp"
 * #include <map>
 * #include <iostream>
 *
 * int objects[] = {99, 94, 79, 64, 50, 46, 43, 37, 32, 19, 18, 7, 6, 3};
 * int max_size = 100;
 *
 * int main() {
 *		GAlgorithm ga(0.8, 0.2);
 *		for (int i = 0; i < 14; ++i) {
 *			ga.addVariable(3);
 *		}
 *		ga.generatePopulation(50);
 *		for (int j = 0; j < 100; ++j) {
 *			std::cout << "Generation " << j << std::endl;
 *			for (std::vector<Individual>::iterator it = ga.begin(); it != ga.end(); ++it) {
 *				int init_fit = 0;
 *				std::map<int, int> bins;
 *				for (std::vector<int>::iterator itvar = it->variables.begin(); itvar != it->variables.end(); ++itvar) {
 *					bins[*itvar] = 0;
 *					std::cout << *itvar << " ";
 *				}
 *				int i = 0;
 *				for (std::vector<int>::iterator itvar = it->variables.begin(); itvar != it->variables.end(); ++itvar) {
 *					bins[*itvar] += objects[i];
 *					i++;
 *				}
 *				for (std::map<int, int>::iterator itbin = bins.begin(); itbin != bins.end(); ++itbin) {
 *					if (itbin->second > max_size) {
 *						init_fit = init_fit + 5 * (itbin->second - max_size);
 *					} else {
 *						init_fit = init_fit + (max_size - itbin->second);
 *					}
 *				}
 *				init_fit += 5 * bins.size();
 *				double fit = 1.0 / init_fit;
 *				std::cout << " bins: " << bins.size() << " fit : " << fit << std::endl;
 *				it->fit = fit;
 *			}
 *			ga.runGeneration(true);
 *		}
 *		return 0;
 * }
 *
 */
class GAlgorithm {
public:
	GAlgorithm(double p_cross, double p_mutation);
	~GAlgorithm();
	void addVariable(int bits);
	void generatePopulation(int size);
	void runGeneration(bool per_individual = false);
	std::vector<Individual>::iterator begin();
	std::vector<Individual>::iterator end();
private:
	int max_var_size;
	double p_cross;
	double p_mutation;
	std::vector<Variable> variables;
	std::vector<Individual> generation;
	int generations;
	int cross(int ind_a, int ind_b, int index, int bit);
	int mutate(int ind, int bit);
};

}

#endif /* GALGORITHM_HPP_ */
