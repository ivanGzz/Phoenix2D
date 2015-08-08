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
 * @file geometry.hpp
 *
 * @author Nelson I. Gonzalez
 */

#ifndef GEOMETRY_HPP_
#define GEOMETRY_HPP_

#include <cmath>
#include "constants.hpp"

/*!
 * Disclaimer: all this primitives use radians instead of sexagesimal degrees
 *  unless stated otherwise
 */
namespace Geometry {

/*!
 *
 */
struct Vector2D {
	double dx;
	double dy;
	Vector2D() : dx(0.0), dy(0.0) {};
	Vector2D(double arg0, double arg1, bool polar = false) {
		if (polar) {
			dx = arg0 * cos(arg1);
			dy = arg0 * sin(arg1);
		} else {
			dx = arg0;
			dy = arg1;
		}
	};
	double getDirection() {
		if (dx == 0.0 && dy == 0.0) {
			return 0.0;
		} else {
			return atan2(dy, dx);
		}
	};
	double getMagnitude() {
		return sqrt(dx * dx + dy * dy);
	}
	void scale(double s) {
		dx *= s;
		dy *= s;
	}
	Vector2D operator +(Vector2D vector) {
		double x = dx + vector.dx;
		double y = dy + vector.dy;
		return Vector2D(x, y);
	}
	//Performs dot multiplication
	double operator *(Vector2D vector) {
		return (dx * vector.dx + dy * vector.dy);
	}
	Vector2D getUnitVector() {
		double m = sqrt(dx * dx + dy * dy);
		if (m > 0.0) {
			return Vector2D(dx / m, dy / m);
		} else {
			return Vector2D();
		}
	}
};

/*!
 *
 */
struct Point {
	double x;
	double y;
	Point() : x(0.0), y (0.0) {};
	Point(double x, double y) : x(x), y(y) {};
	Vector2D operator -(Point point) {
		return Vector2D(x - point.x, y - point.y);
	}
	Point operator +(Vector2D vector) {
		return Point(x + vector.dx, y + vector.dy);
	}
};

/*!
 *
 */
inline double toDegrees(double radians) {
	double degrees = (180.0 * radians / Math::PI);
	if (degrees > 180.0) {
		degrees -= 360.0;
	} else if (degrees < -180.0) {
		degrees += 360.0;
	}
	return degrees;
}

/*!
 *
 */
inline double toRadians(double degrees) {
	double radians = (Math::PI * degrees / 180.0);
	double factor = 2.0 * Math::PI;
	if (radians > factor) {
		radians -= factor;
	} else if (radians < factor) {
		radians += factor;
	}
	return radians;
}

}

#endif /* GEOMETRY_HPP_ */
