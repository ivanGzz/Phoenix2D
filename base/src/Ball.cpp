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
 * @file Ball.cpp
 *
 * @author Nelson I. Gonzalez
 */

#include "Ball.hpp"
#include <vector>
#include <sstream>
#include <cstdlib>
#include "Self.hpp"
#include <cmath>
#include "constants.hpp"

namespace Phoenix {

Ball::Ball() {
	distance = 100.0;
	direction = 0.0;
	dist_change = 0.0;
	dir_change = 0.0;
}

Ball::~Ball() {

}

void Ball::initForCoach(std::string position) {
	std::vector<std::string> tokens;
	std::stringstream ss_position(position);
	std::string token;
	while (std::getline(ss_position, token, ' ')) {
		tokens.push_back(token);
	}
	switch (tokens.size()) {
	case 4:
		_x = atof(tokens[0].c_str());
		_y = atof(tokens[1].c_str());
		_vx = atof(tokens[2].c_str());
		_vy = atof(tokens[3].c_str());
		break;
	default:
		break;
	}
	_status = LOCALIZED;
}

void Ball::initForPlayer(std::string position, Position player_position, Geometry::Vector2D player_velocity) {
	std::vector<std::string> tokens;
	std::stringstream ss_position(position);
	std::string token;
	while (std::getline(ss_position, token, ' ')) {
		tokens.push_back(token);
	}
	_status = POSITION;
	switch (tokens.size()) {
	case 4:
		distance = atof(tokens[0].c_str());
		direction = atof(tokens[1].c_str());
		dist_change = atof(tokens[2].c_str());
		dir_change = atof(tokens[3].c_str());
		_status = LOCALIZED;
		break;
	case 3:
		break;
	case 2:
		distance = atof(tokens[0].c_str());
		direction = atof(tokens[1].c_str());
		break;
	case 1:
		direction = atof(tokens[0].c_str());
		break;
	default:
		break;
	}
	double source_direction = player_position.body() + player_position.neck() + direction;
	if (source_direction > 180.0) {
		source_direction -= 360.0;
	} else if (source_direction <= 180.0) {
		source_direction += 360.0;
	}
	double erx = cos(Math::PI * source_direction / 180.0);
	double ery = sin(Math::PI * source_direction / 180.0);
	_x = player_position.x() + erx * distance;
	_y = player_position.y() + ery * distance;
	if (_status == LOCALIZED) {
		double erxm = (180.0 * erx) / (Math::PI * distance);
		double erym = (180.0 * ery) / (Math::PI * distance);
		double vry = (dist_change * erym + dir_change * erx) / (ery * erym + erx * erxm);
		double vrx = (dist_change - ery * vry) / erx;
		_vx = player_velocity.dx + vrx;
		_vy = player_velocity.dy + vry;
	}
}

void Ball::initForFullstate(double x, double y, double vx, double vy) {
	_x = x;
	_y = y;
	_vx = vx;
	_vy = vy;
	_status = LOCALIZED;
}

void Ball::initForPosition(Position position) {
	_x = position.x();
	_y = position.y();
}

}