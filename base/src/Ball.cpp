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

#include "Ball.hpp"
#include <vector>
#include <sstream>
#include <cstdlib>
#include "Self.hpp"
#include <cmath>
#include "Constants.hpp"

namespace Phoenix {

Ball::Ball() {
	distance = 100.0;
	direction = 0.0;
	distChange = 0.0;
	dirChange = 0.0;
	x = 0.0;
	y = 0.0;
	vx = 0.0;
	vy = 0.0;
	in_sight_range = false;
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
		x = atof(tokens[0].c_str());
		y = atof(tokens[1].c_str());
		vx = atof(tokens[2].c_str());
		vy = atof(tokens[3].c_str());
		break;
	default:
		break;
	}
	this->position = Position(x, y);
	velocity = Geometry::Vector2D(vx, vy); //Vector2D::getVector2DWithXAndY(vx, vy);
	in_sight_range = true;
}

void Ball::initForPlayer(std::string position, const Position* player_position, const Geometry::Vector2D* player_velocity) {
	std::vector<std::string> tokens;
	std::stringstream ss_position(position);
	std::string token;
	while (std::getline(ss_position, token, ' ')) {
		tokens.push_back(token);
	}
	bool vel = false;
	switch (tokens.size()) {
	case 4:
		distance = atof(tokens[0].c_str());
		direction = atof(tokens[1].c_str());
		distChange = atof(tokens[2].c_str());
		dirChange = atof(tokens[3].c_str());
		vel = true;
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
	double source_direction = player_position->body + player_position->neck - direction;
	if (source_direction > 180.0) {
		source_direction -= 360.0;
	} else if (source_direction <= 180.0) {
		source_direction += 360.0;
	}
	double erx = cos(Math::PI * source_direction / 180.0);
	double ery = sin(Math::PI * source_direction / 180.0);
	x = player_position->x + erx * distance;
	y = player_position->y + ery * distance;
	this->position = Position(x, y);
	if (vel) {
		double erxm = (180.0 * erx) / (Math::PI * distance);
		double erym = (180.0 * ery) / (Math::PI * distance);
		double vry = (distChange * erym + dirChange * erx) / (ery * erym + erx * erxm);
		double vrx = (distChange - ery * vry) / erx;
		vx = player_velocity->dx + vrx;
		vy = player_velocity->dy + vry;
		velocity = Geometry::Vector2D(vx, vy); //Vector2D::getVector2DWithXAndY(vx, vy);
	} else {
		velocity = Geometry::Vector2D(0.0, 0.0); //Vector2D::getEmptyVector();
	}
	in_sight_range = true;
}

void Ball::initForFullstate(double x, double y, double vx, double vy) {
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
}

Ball::~Ball() {

}

Position* Ball::getPosition() {
	return &position;
}

Geometry::Vector2D* Ball::getVelocity() {
	return &velocity;
}

bool Ball::isInSightRange() {
	return in_sight_range;
}

}
