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

#include "dribble.hpp"
#include <ctime>
#include <iostream>
#include <boost/random.hpp>
#include "Position.hpp"

namespace dribble {

bool setup = false;
boost::mt19937 rng(time(0));
boost::uniform_int<> xdist(0, 104);
boost::uniform_int<> ydist(0, 68);
Position positionToGo;

void onStart() {
	std::cout << "Starting dribble test" << std::endl;
}

void randomPosition() {
	double x = (double)xdist(rng) - 52.0;
	double y = (double)ydist(rng) - 34.0;
	positionToGo = Position(x, y);
	std::cout << "New random position: (" << x << ", " << y << ")" << std::endl;
}

void executeBeforeKickOff(WorldModel worldModel, std::vector<Message> messages, Commands* commands) {
	if (!setup) {
		double x = -1.0 * fabs((double)xdist(rng) - 52.0); //we need a negative coordinate in x
		double y = (double)ydist(rng) - 34.0;
		std::cout << "Moving to: (" << x << ", " << y << ")" << std::endl;
		commands->move(x, y);
		setup = true;
		randomPosition();
	}
}

void executePlayOn(WorldModel worldModel, std::vector<Message> messages, Commands* commands) {

}

void onFinish() {
	std::cout << "Finishing dribble test" << std::endl;
}

}
