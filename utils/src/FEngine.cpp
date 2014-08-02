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

#include "FEngine.hpp"
#include <iostream>

namespace Fuzzy {

FEngine::FEngine() {

}

FEngine::~FEngine() {
	for (std::map<std::string, FVariable*>::iterator it = variables.begin(); it != variables.end(); ++it) {
		delete it->second;
	}
}

void FEngine::addVariable(FVariable* variable) {
	variables[variable->getName()] = variable;
}

void FEngine::addRule(FRule rule) {
	rule.variables = &variables;
	rule.parse();
	outputs[rule.getOutputName()][rule.getOutputSet()] = 0.0;
	rules.push_back(rule);
}

FVariable* FEngine::getVariable(std::string name) {
	if (variables.count(name)) {
		return variables[name];
	} else {
		std::cerr << "Variable " << name << " does not exist" << std::endl;
		return 0;
	}
}

std::vector<FRule>::iterator FEngine::begin() {
	return rules.begin();
}

std::vector<FRule>::iterator FEngine::end() {
	return rules.end();
}

std::map<std::string, double> FEngine::evaluate(std::map<std::string, double> inputs) {
	std::map<std::string, double> outputs;
	for (std::vector<FRule>::iterator itr = rules.begin(); itr != rules.end(); ++itr) {
		// Evaluate the rule
		itr->evaluate(inputs[itr->firstVariable], inputs[itr->secondVariable]);
		// Check if the rule output is maximum
		if (itr->getOutput() > this->outputs[itr->getOutputName()][itr->getOutputSet()]) {
			this->outputs[itr->getOutputName()][itr->getOutputSet()] = itr->getOutput();
		}
	}
	for (std::map<std::string, std::map<std::string, double> >::iterator ito = this->outputs.begin(); ito != this->outputs.end(); ++ito) {
		outputs[ito->first] = variables[ito->first]->defuzzify(ito->second);
	}
	reload();
	return outputs;
}

void FEngine::reload() {
	for (std::map<std::string, std::map<std::string, double> >::iterator it = outputs.begin(); it != outputs.end(); ++it) {
		for (std::map<std::string, double>::iterator itf = it->second.begin(); itf != it->second.end(); ++itf) {
			itf->second = 0.0;
		}
	}
}

}
