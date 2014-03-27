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

#include <cmath>
#include "Normal.h"
namespace Phoenix
{
Normal::Normal(double mean, double deviation) {
	this->mean = mean;
	this->deviation = deviation;
}

Normal::Normal(std::list<double> data, bool circular) {
	mean = 0.0;
	deviation = 0.0;
	if (data.size() > 1) {
		double sum = 0.0;
		for (std::list<double>::iterator it = data.begin(); it != data.end(); ++it) {
			sum += *it;
		}
		mean = sum / data.size();
		sum = 0.0;
		for (std::list<double>::iterator it = data.begin(); it != data.end(); ++it) {
			sum += pow(*it - mean, 2.0);
		}
		deviation = sqrt(sum / (data.size() - 1));
	} else if (data.size() == 1) {
		mean = data.front();
	}
}

Normal::Normal(std::list<double> data, std::list<int> multipliers, bool circular) {
	mean = 0.0;
	deviation = 0.0;
	if (data.size() == multipliers.size() && data.size() > 1) {
		double sum = 0.0;
		int weight = 0;
		std::list<double>::iterator data_it = data.begin();
		std::list<int>::iterator multiplier_it = multipliers.begin();
		do {
			sum += *multiplier_it * *data_it;
			weight += *multiplier_it;
			++data_it;
			++multiplier_it;
		} while (data_it != data.end());
		mean = sum / weight;
		sum = 0.0;
		data_it = data.begin();
		multiplier_it = multipliers.begin();
		do {
			sum += *multiplier_it * pow(*data_it - mean, 2.0);
			++data_it;
			++multiplier_it;
		} while (data_it != data.end());
		deviation = sqrt(sum / (weight - 1));
	} else if (data.size() == 1) {
		mean = data.front();
	}
}

Normal::~Normal() {

}

double Normal::getLower5() {
	return mean - 1.68 * deviation;
}

double Normal::getUpper5() {
	return mean + 1.68 * deviation;
}

double Normal::getMean() {
	return mean;
}

double Normal::getStdDeviation() {
	return deviation;
}
}