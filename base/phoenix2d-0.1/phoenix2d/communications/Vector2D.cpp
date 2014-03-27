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

#include "Vector2D.h"
#include <cmath>
#include "Self.h"
#include <sstream>
#include <iostream>
#include <iomanip>
namespace Phoenix
{
Vector2D::Vector2D() {
	dx = 0.0;
	dy = 0.0;
	magnitude = 0.0;
	direction = 0.0;
	type = EMPTY_V;
}

Vector2D::Vector2D(double x, double y) {
	dx = x;
	dy = y;
	magnitude = sqrt(pow(dx, 2.0) + pow(dy, 2.0));
	direction = 180.0 * atan2(dy, dx) / Self::PI;
	type = V2D;
}

Vector2D::~Vector2D() {

}

Vector2D Vector2D::getEmptyVector() {
	return Vector2D();
}

Vector2D Vector2D::getVector2DWithMagnitudeAndDirection(double magnitude, double direction) {
	double x = magnitude * cos(Self::PI * direction / 180.0);
	double y = magnitude * sin(Self::PI * direction / 180.0);
	return Vector2D(x, y);
}

Vector2D Vector2D::getVector2DWithXAndY(double x, double y) {
	return Vector2D(x, y);
}

double Vector2D::getXComponent() {
	return dx;
}

double Vector2D::getYComponent() {
	return dy;
}

double Vector2D::getMagnitude() {
	return magnitude;
}

double Vector2D::getDirection() {
	return direction;
}

Vector2D Vector2D::operator +(Vector2D vector) {
	double x = dx + vector.dx;
	double y = dy + vector.dy;
	return Vector2D(x, y);
}

Vector2D Vector2D::operator *(double scalar) {
	double x = scalar * magnitude * cos(Self::PI * direction / 180.0);
	double y = scalar * magnitude * sin(Self::PI * direction / 180.0);
	return Vector2D(x, y);
}

std::string Vector2D::toString() {
	std::stringstream ss;
	if (type == EMPTY_V) {
		ss << "(0.0)" << std::endl;
	} else {
		ss << "(" << std::setprecision(4) << dx << "," << dy << ")" << std::endl;
	}
	std::string stringVelocity;
	std::getline(ss, stringVelocity);
	return stringVelocity;
}

VECTOR_TYPE Vector2D::getType() {
	return type;
}
}