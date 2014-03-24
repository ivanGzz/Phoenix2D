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

#include "Actions.h"
#include "Self.h"
#include "Commands.h"
//#include <iostream>
#include "Game.h"
#include <cmath>
namespace Phoenix
{
Actions::Actions(Commands *commands) {
	this->commands = commands;
}

Actions::~Actions() {

}

bool Actions::goTo(Position position) {
	Position myPosition = Self::getPosition();
	if (myPosition.getDistanceTo(position) > 1.0) {
		double moment = myPosition.getDirectionTo(position);
		//std::cout << moment << std::endl;
		if (std::abs(moment) > 5.0) {
			double angle = moment * (1.0 + Self::INERTIA_MOMENT * Self::AMOUNT_OF_SPEED);
			commands->turn(angle);
		} else {
			commands->dash(50.0, 0.0);
		}
	} else {
		return true;
	}
	return false;
}

void Actions::dribbleTo(Position position) {

}

void Actions::holdPosition(Position position) {

}

void Actions::passToSection(Position position) {

}

void Actions::attackSection(Position position) {

}
}