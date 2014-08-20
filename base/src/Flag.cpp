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
	this->name = name;
	this->simulation_time = simulation_time;
	std::stringstream ss(position);
	std::string token;
	std::getline(ss, token, ' ');
	distance = atof(token.c_str());
	if (distance > 0.1) {
		maxDistance = distance;
		minDistance = exp(log(distance - 0.1) - Server::QUANTIZE_STEP_L);
	} else {
		minDistance = distance;
		maxDistance = distance;
	}
	error = (maxDistance - minDistance) / 2.0;
	if (error == 0.0) {
		error = 0.1;
	}
	std::getline(ss, token, ' ');
	direction = atof(token.c_str());
	maxDirection = direction;
	minDirection = direction;
	if (direction > 0.1) {
		minDirection = exp(log(direction - 0.1) - Server::QUANTIZE_STEP_L);
		if (minDirection > 180.0) {
			minDirection -= 360.0;
		} else if (minDirection < -180.0){
			minDirection += 360.0;
		}
	} else if (direction < -0.1) {
		maxDirection = -1.0 * exp(log(-1.0 * direction - 0.1) - Server::QUANTIZE_STEP_L);
		if (maxDirection > 180.0) {
			maxDirection -= 360.0;
		} else if (maxDirection < -180.0) {
			maxDirection += 360.0;
		}
	}
	derror = (maxDirection - minDirection) / 2.0;
	if (derror == 0.0) {
		derror = 0.1;
	}
	x = FIELD[name].x;
	y = FIELD[name].y;
}

Flag::~Flag() {

}

void Flag::initializeField() {
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

std::string Flag::getName() {
	return name;
}

double Flag::getDistance() {
	return distance;
}

double Flag::getDirection() {
	return direction;
}

double Flag::getX() {
	return x;
}

double Flag::getY() {
	return y;
}

double Flag::getMinDistance() {
	return minDistance;
}

double Flag::getMaxDistance() {
	return maxDistance;
}

double Flag::getDistanceError() {
	return error;
}

double Flag::getMinDirection() {
	return minDirection;
}

double Flag::getMaxDirection() {
	return maxDirection;
}

double Flag::getDirectionError() {
	return derror;
}

}
