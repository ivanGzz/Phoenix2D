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

#include <sstream>
#include <cstdlib>
#include "Line.h"
namespace Phoenix
{
Line::Line(std::string name, std::string position, int simulation_time) {
	this->name = name;
	this->simulation_time = simulation_time;
	std::stringstream ss(position);
	std::string token;
	std::getline(ss, token, ' ');
	distance = atof(token.c_str());
	std::getline(ss, token, ' ');
	direction = atof(token.c_str());
}

Line::~Line() {

}

std::string Line::getName() {
	return name;
}

double Line::getDistance() {
	return distance;
}

double Line::getDirection() {
	return direction;
}
}