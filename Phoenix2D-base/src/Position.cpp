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

#include "Position.h"
#include <cmath>
#include "Self.h"
#include <sstream>
#include <iostream>
#include <iomanip>
namespace Phoenix
{
Position::Position() {
	x = 0.0;
	y = 0.0;
	theta = 0.0;
	gamma = 0.0;
	type = EMPTY_P;
}

Position::Position(double x, double y) {
	this->x = x;
	this->y = y;
	theta = 0.0;
	gamma = 0.0;
	type = POINT_P;
}

Position::Position(double x, double y, double theta) {
	this->x = x;
	this->y = y;
	this->theta = theta;
	gamma = 0.0;
	type = OBJECT;
}

Position::Position(double x, double y, double theta, double gamma) {
	this->x = x;
	this->y = y;
	this->theta = theta;
	this->gamma = gamma;
	type = COMPLETE;
}

Position::~Position() {

}

double Position::getX() {
	return x;
}

double Position::getY() {
	return y;
}

double Position::getBodyDirection() {
	return theta;
}

double Position::getHeadDirection() {
	return gamma;
}

double Position::getDistanceTo(Position position) {
	double distance = sqrt(pow(position.getX() - x, 2.0) + pow(position.getY() - y, 2.0));
	return distance;
}

double Position::getDirectionTo(Position position) {
	double direction = 180.0 * (atan2(position.getY() - y, position.getX() - x)) / Self::PI - (theta + gamma);
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

POSITION_TYPE Position::getPositionType() {
	return type;
}

std::string Position::toString() {
	std::stringstream ss;
	//ss << "(" << std::setprecision(4) << x << ", " << y << ", " << theta << ")" << std::endl;
	ss << "(" << std::setprecision(4) << x << "," << y;
	switch (type) {
	case EMPTY_P:
		break;
	case POINT_P:
		break;
	case OBJECT:
		ss << "," << std::setprecision(4) << theta;
		break;
	case COMPLETE:
		ss << "," << std::setprecision(4) << theta << "," << gamma;
		break;
	default:
		break;
	}
	ss << ")" << std::endl;
	std::string stringPosition;
	std::getline(ss, stringPosition);
	return stringPosition;
}
}