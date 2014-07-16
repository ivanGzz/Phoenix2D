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
 * @file Position.cpp
 *
 * @author Nelson Ivan Gonzalez
 */

#include "Position.hpp"
#include <cmath>
#include "Self.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>
#include "constants.hpp"

namespace Phoenix {

Position::Position(double x, double y, double body, double neck) {
	this->x = x;
	this->y = y;
	this->body = body;
	this->neck = neck;
}

Position::Position(Geometry::Point point) {
	x = point.x;
	y = point.y;
	body = 0;
	neck = 0;
}

Position::~Position() {

}

double Position::getDistanceTo(Position* position) const {
	double distance = sqrt(pow(position->x - x, 2.0) + pow(position->y - y, 2.0));
	return distance;
}

double Position::getDirectionTo(Position* position) const {
	double direction = 180.0 * (atan2(position->y - y, position->x - x)) / Math::PI - body;
	if (direction >= 180.0) {
		direction -= 360.0;
	} else if (direction < -180.0) {
		direction += 360.0;
	}
	return direction;
}

void Position::mirror() {
	if (x != 0.0) x *= -1.0;
	if (y != 0.0) y *= -1.0;
}

Geometry::Point Position::getPoint() {
	return Geometry::Point(x, y);
}

double Position::getX() {
	return x;
}

double Position::getY() {
	return y;
}

double Position::getDirection() {
	return body;
}

}
