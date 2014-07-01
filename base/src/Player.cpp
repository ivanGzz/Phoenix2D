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

#include <sstream>
#include <cstdlib>
#include <cmath>
#include "Player.hpp"
#include "Self.hpp"
#include "Controller.hpp"
#include "constants.hpp"

namespace Phoenix {

Player::Player() {
	distance = 100.0;
	direction = 0.0;
	distChange = 0.0;
	dirChange = 0.0;
	bodyDirection = 0.0;
	headDirection = 0.0;
	pointDir = 0.0;
	x = 0.0;
	y = 0.0;
	body = 0.0;
	head = 0.0;
	vx = 0.0;
	vy = 0.0;
	has_body = false;
	has_head = false;
	pointing = false;
	kicking = false;
	tackling = false;
	team = "undefined";
	uniform_number = 0;
	goalie = false;
	player_id = -1;
	is_in_sight_range = false;
	is_localized = false;
}

Player::~Player() {

}

void Player::initForCoach(std::string name, std::string position) {
	std::vector<std::string> tokens;
	std::stringstream ss_name(name);
	std::string token;
	while (std::getline(ss_name, token, ' ')) {
		tokens.push_back(token);
	}
	std::string team_t = tokens[1].substr(1, tokens[1].length() - 2);
	if (Controller::AGENT_TYPE == 't') {
		team = team_t;
	} else if (team_t.compare(Self::TEAM_NAME) == 0) {
		team = "our";
	} else {
		team = "opp";
	}
	if (tokens.size() > 3) {
		goalie = true;
	}
	uniform_number = atoi(tokens[2].c_str());
	tokens.clear();
	std::stringstream ss_position(position);
	while (std::getline(ss_position, token, ' ')) {
		if (token.compare("k") == 0) {
			kicking = true;
		} else if (token.compare("t") == 0) {
			tackling = true;
		} else {
			tokens.push_back(token);
		}
	}
	switch (tokens.size()) {
	case 6:
		x = atof(tokens[0].c_str());
		y = atof(tokens[1].c_str());
		vx = atof(tokens[2].c_str());
		vy = atof(tokens[3].c_str());
		body = atof(tokens[4].c_str());
		head = atof(tokens[5].c_str());
		break;
	case 7:
		x = atof(tokens[0].c_str());
		y = atof(tokens[1].c_str());
		vx = atof(tokens[2].c_str());
		vy = atof(tokens[3].c_str());
		body = atof(tokens[4].c_str());
		head = atof(tokens[5].c_str());
		pointDir = atof(tokens[6].c_str());
		pointing = true;
		break;
	default:
		break;
	}
	velocity = Geometry::Vector2D(vx, vy); //Vector2D::getVector2DWithXAndY(vx, vy);
	this->position = Position(x, y, body, head);
	player_id = -1;
	is_in_sight_range = true;
	is_localized = true;
}

void Player::initForPlayer(std::string name, std::string position, const Position* player_position, const Geometry::Vector2D* player_velocity) {
	std::vector<std::string> tokens;
	std::stringstream ss_name(name);
	std::string token;
	while (std::getline(ss_name, token, ' ')) {
		tokens.push_back(token);
	}
	std::string team_t;
	switch (tokens.size()) {
	case 1:
		break;
	case 2:
		team_t = tokens[1].substr(1, tokens[1].length() - 2);
		if (team_t.compare(Self::TEAM_NAME) == 0) {
			team = "our";
		} else {
			team = "opp";
		}
		break;
	case 3:
		team_t = tokens[1].substr(1, tokens[1].length() - 2);
		if (team_t.compare(Self::TEAM_NAME) == 0) {
			team = "our";
		} else {
			team = "opp";
		}
		uniform_number = atoi(tokens[2].c_str());
		break;
	case 4: //goalie
		team_t = tokens[1].substr(1, tokens[1].length() - 2);
		if (team_t.compare(Self::TEAM_NAME) == 0) {
			team = "our";
		} else {
			team = "opp";
		}
		uniform_number = atoi(tokens[2].c_str());
		goalie = true;
		break;
	default:
		break;
	}
	tokens.clear();
	std::stringstream ss_position(position);
	while (std::getline(ss_position, token, ' ')) {
		if (token.compare("k") == 0) {
			kicking = true;
		} else if (token.compare("t") == 0) {
			tackling = true;
		} else {
			tokens.push_back(token);
		}
	}
	bool vel = false;
	switch (tokens.size()) {
	case 1:
		direction = atof(tokens[0].c_str());
		break;
	case 2:
		distance = atof(tokens[0].c_str());
		direction = atof(tokens[1].c_str());
		break;
	case 3:
		distance = atof(tokens[0].c_str());
		direction = atof(tokens[1].c_str());
		pointDir = atof(tokens[2].c_str());
		pointing = true;
		break;
	case 4:
		distance = atof(tokens[0].c_str());
		direction = atof(tokens[1].c_str());
		distChange = atof(tokens[2].c_str());
		dirChange = atof(tokens[3].c_str());
		vel = true;
		break;
	case 5:
		distance = atof(tokens[0].c_str());
		direction = atof(tokens[1].c_str());
		distChange = atof(tokens[2].c_str());
		dirChange = atof(tokens[3].c_str());
		vel = true;
		pointDir = atof(tokens[4].c_str());
		pointing = true;
		break;
	case 6:
		distance = atof(tokens[0].c_str());
		direction = atof(tokens[1].c_str());
		distChange = atof(tokens[2].c_str());
		dirChange = atof(tokens[3].c_str());
		vel = true;
		bodyDirection = atof(tokens[4].c_str());
		headDirection = atof(tokens[5].c_str());
		has_body = true;
		has_head = true;
		break;
	case 7:
		distance = atof(tokens[0].c_str());
		direction = atof(tokens[1].c_str());
		distChange = atof(tokens[2].c_str());
		dirChange = atof(tokens[3].c_str());
		vel = true;
		bodyDirection = atof(tokens[4].c_str());
		headDirection = atof(tokens[5].c_str());
		has_body = true;
		has_head = true;
		pointDir = atof(tokens[6].c_str());
		pointing = true;
		break;
	default:
		break;
	}
	double source_direction = player_position->body + player_position->neck + direction;
	if (source_direction > 180.0) {
		source_direction -= 360.0;
	} else if (source_direction <= 180.0) {
		source_direction += 360.0;
	}
	double erx = cos(Math::PI * source_direction / 180.0);
	double ery = sin(Math::PI * source_direction / 180.0);
	x = player_position->x + erx * distance;
	y = player_position->y + ery * distance;
	if (has_body && has_head) {
		body = bodyDirection + player_position->body + player_position->neck;
		if (body > 180.0) {
			body -= 360.0;
		} else if (body <= -180.0) {
			body += 360.0;
		}
		this->position = Position(x, y, body, head);
	} else {
		this->position = Position(x, y);
	}
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
	player_id = -1;
	is_in_sight_range = true;
	is_localized = true;
}

void Player::initForFullstate(std::string team, int unum, double x, double y, double vx, double vy, double b, double n) {
	if (Self::SIDE[0] == team[0]) {
		this->team = "our";
	} else {
		this->team = "opp";
	}
	uniform_number = unum;
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	body = b;
	head = n;
	position = Position(this->x, this->y, body, head);
	velocity = Geometry::Vector2D(vx, vy); //Vector2D::getVector2DWithXAndY(vx, vy);
	is_localized = true;
}

Position* Player::getPosition() {
	return &position;
}

std::string Player::getTeam() {
	return team;
}

int Player::getUniformNumber() {
	return uniform_number;
}

Geometry::Vector2D* Player::getVelocity() {
	return &velocity;
}

bool Player::isGoalie() {
	return goalie;
}

bool Player::isPointing() {
	return pointing;
}

double Player::getPointingDirection() {
	return pointDir;
}

bool Player::isKicking() {
	return kicking;
}

bool Player::isTackling() {
	return tackling;
}

void Player::setPlayerId(int player_id) {
	this->player_id = player_id;
}

int Player::getPlayerId() {
	return player_id;
}

void Player::toggleSightRange() {
	is_in_sight_range = !is_in_sight_range;
}

bool Player::isInSightRange() {
	return is_in_sight_range;
}

bool Player::isLocalized() {
	return is_localized;
}

}
