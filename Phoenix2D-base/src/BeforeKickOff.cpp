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

#include <iostream>
#include <cmath>
#include "BeforeKickOff.h"
#include "Game.h"
#include "Commands.h"
#include "Config.h"
#include "Self.h"
namespace Phoenix
{
BeforeKickOff::BeforeKickOff(Commands *commands) : PlayMode(commands) {

}

BeforeKickOff::~BeforeKickOff() {

}

void BeforeKickOff::setup(WorldModel world) {
	Position initPosition = Config::POSITION;
	commands->move(initPosition.getX(), initPosition.getY());
}

void BeforeKickOff::onPlayerExecute(WorldModel world) {
	Position myPosition = Self::getPosition();
	if (std::abs(myPosition.getBodyDirection()) > 1.0) {
		commands->turn(-1.0 * myPosition.getBodyDirection());
	}
}

void BeforeKickOff::onGoalieExecute(WorldModel world) {

}

void BeforeKickOff::onCoachExecute(WorldModel world) {

}

void BeforeKickOff::onMessageReceived(std::string message, int sender) {

}
}