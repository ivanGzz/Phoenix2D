/*
 * Phoenix2D (RoboCup Soccer Simulation 2D League)
 * Copyright (c) 2013, 2014 Nelson Ivan Gonzalez
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
 *
 * @file Message.cpp
 *
 * @author Nelson Ivan Gonzalez
 */

#include "Message.hpp"

namespace Phoenix {

Message::Message(double d, std::string team, std::string message) {
	direction = d;
	this->team = team;
	unum = 0;
	this->message = message;
}

Message::Message(double d, std::string team, int unum, std::string message) {
	direction = d;
	this->team = team;
	this->unum = unum;
	this->message = message;
}

Message::~Message() {

}

std::string Message::getMessage() {
	return message;
}

std::string Message::getTeam() {
	return team;
}

int Message::getUniformNumber() {
	return unum;
}

double Message::getDirection() {
	return direction;
}

}
