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

#include "Ball.h"
#include <vector>
#include <sstream>
#include <cstdlib>
#include "Self.h"
#include <cmath>
namespace Phoenix
{
Ball::Ball() {
	distance = 100.0;
	direction = 0.0;
	distChange = 0.0;
	dirChange = 0.0;
	x = 0.0;
	y = 0.0;
	vx = 0.0;
	vy = 0.0;
	simulation_time = 0;
	in_sight_range = false;
	bound = 0;
}

Ball::Ball(int simulation_time) {
	distance = 100.0;
	direction = 0.0;
	distChange = 0.0;
	dirChange = 0.0;
	x = 0.0;
	y = 0.0;
	vx = 0.0;
	vy = 0.0;
	this->simulation_time = simulation_time;
	in_sight_range = false;
	bound = 0;
}

Ball::Ball(std::string position, int simulation_time) {
	distance = 100.0;
	direction = 0.0;
	distChange = 0.0;
	dirChange = 0.0;
	x = 0.0;
	y = 0.0;
	vx = 0.0;
	vy = 0.0;
	std::vector<std::string> tokens;
	std::stringstream ss_position(position); // = std::stringstream(name);
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
	this->simulation_time = simulation_time;
	in_sight_range = true;
	bound = 0;
}

Ball::Ball(std::string position, int simulation_time, Position player_position, Vector2D player_velocity) {
	distance = 100.0;
	direction = 0.0;
	distChange = 0.0;
	dirChange = 0.0;
	x = 0.0;
	y = 0.0;
	vx = 0.0;
	vy = 0.0;
	std::vector<std::string> tokens;
	std::stringstream ss_position(position); // = std::stringstream(name);
	std::string token;
	while (std::getline(ss_position, token, ' ')) {
		tokens.push_back(token);
	}
	switch (tokens.size()) {
	case 4:
		distance = atof(tokens[0].c_str());
		direction = atof(tokens[1].c_str());
		distChange = atof(tokens[2].c_str());
		dirChange = atof(tokens[3].c_str());
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
	double source_direction = player_position.getBodyDirection() + player_position.getHeadDirection() - direction;
	if (source_direction > 180.0) {
		source_direction -= 360.0;
	} else if (source_direction <= 180.0) {
		source_direction += 360.0;
	}
	double erx = cos(Self::PI * source_direction / 180.0);
	double ery = sin(Self::PI * source_direction / 180.0);
	x = player_position.getX() + erx * distance;
	y = player_position.getY() + ery * distance;
	double erxm = (180.0 * erx) / (Self::PI * distance);
	double erym = (180.0 * ery) / (Self::PI * distance);
	double vry = (distChange * erym + dirChange * erx) / (ery * erym + erx * erxm);
	double vrx = (distChange - ery * vry) / erx;
	vx = player_velocity.getXComponent() + vrx;
	vy = player_velocity.getYComponent() + vry;
	this->simulation_time = simulation_time;
	in_sight_range = true;
	bound = 0;
}

Ball::~Ball() {

}

Position Ball::getPosition() {
	return Position(x, y);
}

Vector2D Ball::getVelocity() {
	return Vector2D::getVector2DWithXAndY(vx, vy);
}

bool Ball::isInSightRange() {
	return in_sight_range;
}

void Ball::boundTo(Ball* ball) {
	bound = ball;
}

Ball* Ball::getBound() {
	return bound;
}
}