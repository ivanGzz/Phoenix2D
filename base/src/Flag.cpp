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
 * @file Flag.cpp
 *
 * @author Nelson Ivan Gonzalez
 */

#include <sstream>
#include <cstdlib>
#include <cmath>
#include <map>
#include "Flag.hpp"
#include "Self.hpp"
#include "Server.hpp"

namespace Phoenix {

struct _coordinate {
	double x;
	double y;
};

static std::map<std::string, _coordinate> FIELD;

_coordinate makeCoordinate(double x, double y) {
	if (Self::SIDE.compare("r") == 0) {
		x *= -1.0;
		y *= -1.0;
	}
	_coordinate c = {x , y};
	return c;
}

Flag::Flag(std::string name, std::string position, int simulation_time) {
	_name = name;
	_simulation_time = simulation_time;
	std::stringstream ss(position);
	std::string token;
	std::getline(ss, token, ' ');
	_distance = atof(token.c_str());
	if (_distance > 0.1) {
		max_distance = _distance;
		min_distance = exp(log(_distance - 0.1) - Server::QUANTIZE_STEP_L);
	} else {
		min_distance = _distance;
		max_distance = _distance;
	}
	_distance_error = (max_distance - min_distance) / 2.0;
	if (_distance_error == 0.0) {
		_distance_error = 0.1;
	}
	std::getline(ss, token, ' ');
	_direction = atof(token.c_str());
	max_direction = _direction;
	min_direction = _direction;
	if (_direction > 0.1) {
		min_direction = exp(log(_direction - 0.1) - Server::QUANTIZE_STEP_L);
		if (min_direction > 180.0) {
			min_direction -= 360.0;
		} else if (min_direction < -180.0){
			min_direction += 360.0;
		}
	} else if (_direction < -0.1) {
		max_direction = -1.0 * exp(log(-1.0 * _direction - 0.1) - Server::QUANTIZE_STEP_L);
		if (max_direction > 180.0) {
			max_direction -= 360.0;
		} else if (max_direction < -180.0) {
			maxDirection += 360.0;
		}
	}
	_direction_error = (max_direction - min_direction) / 2.0;
	if (_direction_error == 0.0) {
		_direction_error = 0.1;
	}
	_x = FIELD[name].x;
	_y = FIELD[name].y;
}

Flag::~Flag() {

}

void initField() {
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f t 0"   , makeCoordinate(  0.0, -39.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f t r 10", makeCoordinate( 10.0, -39.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f t r 20", makeCoordinate( 20.0, -39.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f t r 30", makeCoordinate( 30.0, -39.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f t r 40", makeCoordinate( 40.0, -39.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f t r 50", makeCoordinate( 50.0, -39.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f r t 30", makeCoordinate( 57.5, -30.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f r t 20", makeCoordinate( 57.5, -20.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f r t 10", makeCoordinate( 57.5, -10.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f r 0"   , makeCoordinate( 57.5,   0.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f r b 10", makeCoordinate( 57.5,  10.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f r b 20", makeCoordinate( 57.5,  20.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f r b 30", makeCoordinate( 57.5,  30.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f b r 50", makeCoordinate( 50.0,  39.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f b r 40", makeCoordinate( 40.0,  39.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f b r 30", makeCoordinate( 30.0,  39.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f b r 20", makeCoordinate( 20.0,  39.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f b r 10", makeCoordinate( 10.0,  39.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f b 0"   , makeCoordinate(  0.0,  39.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f b l 10", makeCoordinate(-10.0,  39.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f b l 20", makeCoordinate(-20.0,  39.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f b l 30", makeCoordinate(-30.0,  39.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f b l 40", makeCoordinate(-40.0,  39.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f b l 50", makeCoordinate(-50.0,  39.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f l b 30", makeCoordinate(-57.5,  30.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f l b 20", makeCoordinate(-57.5,  20.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f l b 10", makeCoordinate(-57.5,  10.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f l 0"   , makeCoordinate(-57.5,   0.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f l t 10", makeCoordinate(-57.5, -10.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f l t 20", makeCoordinate(-57.5, -20.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f l t 30", makeCoordinate(-57.5, -30.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f t l 50", makeCoordinate(-50.0, -39.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f t l 40", makeCoordinate(-40.0, -39.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f t l 30", makeCoordinate(-30.0, -39.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f t l 20", makeCoordinate(-20.0, -39.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f t l 10", makeCoordinate(-10.0, -39.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f c"     , makeCoordinate(  0.0,   0.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f c t"   , makeCoordinate(  0.0, -34.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f r t"   , makeCoordinate( 52.5, -34.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f r b"   , makeCoordinate( 52.5,  34.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f c b"   , makeCoordinate(  0.0,  34.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f l b"   , makeCoordinate(-52.5,  34.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f l t"   , makeCoordinate(-52.5, -34.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("g l"     , makeCoordinate(-52.5,   0.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f g l t" , makeCoordinate(-52.5,  -7.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f p l t" , makeCoordinate(-36.0, -20.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f p l c" , makeCoordinate(-36.0,   0.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f p l b" , makeCoordinate(-36.0,  20.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f g l b" , makeCoordinate(-52.5,   7.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("g r"     , makeCoordinate( 52.5,   0.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f g r t" , makeCoordinate( 52.5,  -7.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f p r t" , makeCoordinate( 36.0, -20.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f p r c" , makeCoordinate( 36.0,   0.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f p r b" , makeCoordinate( 36.0,  20.0)));
	FIELD.insert(std::map<std::string, _coordinate>::value_type("f g r b" , makeCoordinate( 52.5,   7.0)));
}

std::string Flag::name() {
	return _name;
}

double Flag::distance() {
	return _distance;
}

double Flag::direction() {
	return _direction;
}

double Flag::distanceError() {
	return _distance_error;
}

double Flag::directionError() {
	return _direction_error;
}

}
