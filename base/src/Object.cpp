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
 * @file Object.hpp
 *
 * @author Nelson I. Gonzalez
 */

#include "Object.hpp"

namespace Phoenix {

Object::Object() {
	_vx = 0.0;
	_vy = 0.0;
	status = LOST;
}

Position Object::position() {
	return Position(_x, _y, _body, _head);
}

Geometry::Vector2D Object::velocity() {
	return Geometry::Vector2D(_vx, _vy);
}

Position Object::positionAtTime(int time) {
	double x = _x + _vx * time;
	double y = _y + _vy * time;
	return Position(x, y, _body, _head);
}

OBJECT_STATUS Object::status() {
	return _status;
}

void Object::setStatus(OBJECT_STATUS status) {
	_status = status;
}

}