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

#ifndef FENGINE_HPP_
#define FENGINE_HPP_

#include <boost/noncopyable.hpp>
#include "FVariable.hpp"
#include "FRule.hpp"
#include <vector>
#include <map>
#include <string>

namespace Fuzzy {

/*!
 * Example:
 *
 * #include "fuzzy.hpp"
 * #include <string>
 * #include <map>
 * #include "functions.hpp"
 * #include <iostream>
 *
 * int main() {
 * 		FEngine engine;
 * 		FVariable* v = new FVariable("speed", 0.0, 1.0);
 * 		v->addMembershipFunction("slow", new Math::RampDesc(0.2, 0.4));
 * 		v->addMembershipFunction("medium", new Math::Trapezoidal(0.3, 0.5, 0.6, 0.8));
 * 		v->addMembershipFunction("fast", new Math::RampAsc(0.6, 0.7));
 *		engine.addVariable(v);
 *		v = new FVariable("stamina", 0.0, 8000.0);
 *		v->addMembershipFunction("low", new Math::RampDesc(4000.0, 6000.0));
 *		v->addMembershipFunction("high", new Math::RampAsc(4000.0, 6000.0));
 *		engine.addVariable(v);
 *		v = new FVariable("dash", 0.0, 100.0);
 *		v->addMembershipFunction("low", new Math::RampDesc(30.0, 50.0));
 *		v->addMembershipFunction("medium", new Math::Trapezoidal(20.0, 40.0, 60.0, 80.0));
 *		v->addMembershipFunction("high", new Math::RampAsc(60.0, 80.0));
 *		engine.addVariable(v);
 *		engine.addRule(FRule("speed = slow   & stamina = low  -> dash = low"));
 *		engine.addRule(FRule("speed = slow   & stamina = high -> dash = high"));
 *		engine.addRule(FRule("speed = medium & stamina = low  -> dash = low"));
 *		engine.addRule(FRule("speed = medium & stamina = high -> dash = high"));
 *		engine.addRule(FRule("speed = fast   & stamina = low  -> dash = low"));
 *		engine.addRule(FRule("speed = fast   & stamina = high -> dash = medium"));
 *		for (std::vector<FRule>::iterator it = engine.begin(); it != engine.end(); ++it) {
 *			it->evaluate(0.0, 8000.0);
 *			std::cout << it->getOutputName() << " is " << it->getOutputSet() << " with " << it->getOutput() << std::endl;
 *		}
 *		for (std::vector<FRule>::iterator it = engine.begin(); it != engine.end(); ++it) {
 *			it->evaluate(0.4, 7000.0);
 *			std::cout << it->getOutputName() << " is " << it->getOutputSet() << " with " << it->getOutput() << std::endl;
 *		}
 *		for (std::vector<FRule>::iterator it = engine.begin(); it != engine.end(); ++it) {
 *			it->evaluate(0.7, 3000.0);
 *			std::cout << it->getOutputName() << " is " << it->getOutputSet() << " with " << it->getOutput() << std::endl;
 *		}
 *		std::map<std::string, double> inputs;
 *		inputs["speed"] = 0.0;
 *		inputs["stamina"] = 8000.0;
 *		std::map<std::string, double> outputs = engine.evaluate(inputs);
 *		for (std::map<std::string, double>::iterator it = outputs.begin(); it != outputs.end(); ++it) {
 *			std::cout << it->first << " " << it->second << std::endl;
 *		}
 *		std::cout << std::endl;
 *		inputs["speed"] = 0.4;
 *		inputs["stamina"] = 7000.0;
 *		outputs = engine.evaluate(inputs);
 *		for (std::map<std::string, double>::iterator it = outputs.begin(); it != outputs.end(); ++it) {
 *			std::cout << it->first << " " << it->second << std::endl;
 *		}
 *		std::cout << std::endl;
 *		inputs["speed"] = 0.7;
 *		inputs["stamina"] = 3000.0;
 *		outputs = engine.evaluate(inputs);
 *		for (std::map<std::string, double>::iterator it = outputs.begin(); it != outputs.end(); ++it) {
 *			std::cout << it->first << " " << it->second << std::endl;
 *		}
 *		return 0;
 * }
 */
class FEngine : private boost::noncopyable {
public:
	FEngine();
	~FEngine();
	void addVariable(FVariable* variable);
	void addRule(FRule rule);
	FVariable* getVariable(std::string name);
	std::vector<FRule>::iterator begin();
	std::vector<FRule>::iterator end();
	std::map<std::string, double> evaluate(std::map<std::string, double> inputs);
private:
	std::map<std::string, FVariable*> variables;
	std::vector<FRule> rules;
	std::map<std::string, std::map<std::string, double> > outputs;
	void reload();
};

}

#endif /* FENGINE_HPP_ */
