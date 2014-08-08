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

#include "FVariable.hpp"

namespace Fuzzy {

FVariable::FVariable(std::string name, double min, double max) {
	this->name = name;
	this->min = min;
	this->max = max;
}

FVariable::~FVariable() {
	for (std::map<std::string, Math::Function*>::iterator it = mfuncs.begin(); it != mfuncs.end(); ++it) {
		delete it->second;
	}
}

void FVariable::addMembershipFunction(std::string set, Math::Function* f) {
	if (mfuncs.count(set) > 0) {
		delete mfuncs[set];
	}
	mfuncs[set] = f;
}

double FVariable::getMembershipFor(std::string set, double value) {
	return mfuncs[set]->evaluate(value);
}

std::string FVariable::getName() {
	return name;
}

double FVariable::defuzzify(std::map<std::string, double> memberships) {
	double step = (max - min) / STEPS;
	double sm = 0.0;
	double M = 0.0;
	for (int i = 0; i < STEPS; ++i) {
		double x = min + step * i;
		double y = 0.0;
		for (std::map<std::string, Math::Function*>::iterator it = mfuncs.begin(); it != mfuncs.end(); ++it) {
			double ym = it->second->evaluate(x);
			if (ym > memberships[it->first]) {
				ym = memberships[it->first];
			}
			if (ym > y) {
				y = ym;
			}
		}
		M += step * y;
		sm += step * y * x;
	}
	if (M > 0.0) {
		return sm / M;
	} else {
		return min;
	}
}

}
