/*
 * Phoenix2D (RoboCup Soccer Simulation 2D League)
 * Copyright (c) 2013 - 2015 Nelson I. Gonzalez
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
 * @author Nelson I. Gonzalez
 */

#include "Position.hpp"
#include <cmath>
#include "Self.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>
#include "constants.hpp"

namespace Phoenix {

Position::Position() {
	_x = 0.0;
	_y = 0.0;
	_body = 0.0;
	_head = 0.0;
}

Position::Position(double x, double y, double body, double head) {
	_x = x;
	_y = y;
	_body = body;
	_head = neck;
}

Position::Position(Geometry::Point point) {
	_x = point.x;
	_y = point.y;
	_body = 0;
	_head = 0;
}

Position::~Position() {

}

double Position::distanceTo(Position* position) {
	double distance = sqrt(pow(position->_x - _x, 2.0) + pow(position->_y - _y, 2.0));
	return distance;
}

double Position::directionTo(Position* position) {
	double direction = 180.0 * (atan2(position->_y - _y, position->_x - _x)) / Math::PI - body;
	if (direction >= 180.0) {
		direction -= 360.0;
	} else if (direction < -180.0) {
		direction += 360.0;
	}
	return direction;
}

Geometry::Point Position::point() {
	return Geometry::Point(_x, _y);
}

double Position::x() {
	return _x;
}

void Position::setX(double x) {
	_x = x;
}

double Position::y() {
	return _y;
}

void Position::setY(double y) {
	_y = y;
}

double Position::body() {
	return _body;
}

void Position::setBody(double body) {
	_body = body;
}

double Position::head() {
	return _head;
}

void Position::setHead(double head) {
	_head = head;
}

}
