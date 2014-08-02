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

#include "FRule.hpp"
#include <boost/regex.hpp>

namespace Fuzzy {

boost::regex rule_regex("(\\w+)\\s*=\\s*(\\w+)\\s*&\\s*(\\w+)\\s*=\\s*(\\w+)\\s*\\->\\s*(\\w+)\\s*=\\s*(\\w+)");

FRule::FRule(std::string rule) {
	variables = 0;
	firstVariable = "";
	firstSet = "";
	secondVariable = "";
	secondSet = "";
	outputVariable = "";
	outputSet = "";
	output = 0.0;;
	parsed = false;
	this->rule = rule;
}

FRule::~FRule() {

}

void FRule::parse() {
	boost::cmatch match;
	if (boost::regex_match(rule.c_str(), match, rule_regex)) {
		firstVariable  = std::string() + match[1];
		std::map<std::string, FVariable*>::iterator it = variables->find(firstVariable);
		if (it == variables->end()) {
			std::cerr << "Variable " << firstVariable << " does not exist" << std::endl;
			return;
		}
		firstSet       = std::string() + match[2];
		if (it->second->mfuncs.count(firstSet) == 0) {
			std::cerr << "Variable " << firstVariable << " does not contains set " << firstSet << std::endl;
			return;
		}
		secondVariable = std::string() + match[3];
		it = variables->find(secondVariable);
		if (it == variables->end()) {
			std::cerr << "Variable " << secondVariable << " does not exist" << std::endl;
			return;
		}
		secondSet      = std::string() + match[4];
		if (it->second->mfuncs.count(secondSet) == 0) {
			std::cerr << "Variable " << secondVariable << " does not contains set " << secondSet << std::endl;
			return;
		}
		outputVariable = std::string() + match[5];
		it = variables->find(outputVariable);
		if (it == variables->end()) {
			std::cerr << "Variable " << outputVariable << " does not exist" << std::endl;
			return;
		}
		outputSet      = std::string() + match[6];
		if (it->second->mfuncs.count(outputSet) == 0) {
			std::cerr << "Variable " << outputVariable << " does not contains set " << outputSet << std::endl;
			return;
		}
		parsed = true;
	} else {
		std::cerr << "Match failed" << std::endl;
	}
}

std::string FRule::getOutputSet() {
	return outputSet;
}

std::string FRule::getOutputName() {
	return outputVariable;
}

double FRule::getOutput() {
	return output;
}

void FRule::evaluate(double first, double second) {
	if (parsed) {
		double mfirst = (*variables)[firstVariable]->getMembershipFor(firstSet, first);
		double msecond = (*variables)[secondVariable]->getMembershipFor(secondSet, second);
		output =  (mfirst > msecond) ? msecond : mfirst;
	} else {
		output = -1.0;
	}
}

}
