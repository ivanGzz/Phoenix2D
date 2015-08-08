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
 * @file PFields.hpp
 *
 * @author Nelson I. Gonzalez
 */

#ifndef PFIELDS_HPP_
#define PFIELDS_HPP_

#include "geometry.hpp"
#include <vector>

namespace Geometry {

/*!
 *
 */
template <class U, class V>
class PFields {
public:
	/*!
	 *
	 */
	PFields(U u, V v);
	/*!
	 *
	 */
	~PFields();
	/*!
	 *
	 */
	Vector2D computePotential(Point position, std::vector<Point> obstacles, Point goal);
private:
	U u;	///<
	V v;	///<
};

template <class U, class V>
PFields<U, V>::PFields(U u, V v) {
	this->u = u;
	this->v = v;
}

template <class U, class V>
PFields<U, V>::~PFields() {

}

template <class U, class V>
Vector2D PFields<U, V>::computePotential(Point position, std::vector<Point> obstacles, Point goal) {
	Vector2D potential;
	for (std::vector<Point>::iterator it = obstacles.begin(); it != obstacles.end(); ++it) {
		double d = sqrt(pow(position.x - it->x, 2.0) + pow(position.y - it->y, 2.0));
		double a = atan2(position.y - it->y, position.x - it->x);
		double p = u.evaluate(d);
		if (p > 0) {
			potential.dx += p * cos(a);
			potential.dy += p * sin(a);
		}
	}
	double d = sqrt(pow(position.x - goal.x, 2.0) + pow(position.y - goal.y, 2.0));
	double a = atan2(position.y - goal.y, position.x - goal.x);
	double p = v.evaluate(d);
	potential.dx += p * cos(a);
	potential.dy += p * sin(a);
	return potential;
}

}

#endif /* PFIELDS_HPP_ */
