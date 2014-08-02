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

#ifndef FRULE_HPP_
#define FRULE_HPP_

#include "FVariable.hpp"
#include <map>
#include <string>

namespace Fuzzy {

class FRule {
friend class FEngine;
public:
	FRule(std::string rule);
	~FRule();
	void parse();
	std::string getOutputName();
	std::string getOutputSet();
	double getOutput();
	void evaluate(double first, double second);
private:
	std::string rule;
	std::map<std::string, FVariable*>* variables;
	std::string firstVariable;
	std::string firstSet;
	std::string secondVariable;
	std::string secondSet;
	std::string outputVariable;
	std::string outputSet;
	double output;
	bool parsed;
};

}

#endif /* FRULE_HPP_ */
