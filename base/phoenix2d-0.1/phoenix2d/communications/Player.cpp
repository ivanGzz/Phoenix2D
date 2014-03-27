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
#include "Player.h"
#include "Self.h"
#include "Controller.h"
namespace Phoenix
{
Player::Player() {
	distance = 100.0;
	direction = 0.0;
	distChange = 0.0;
	dirChange = 0.0;
	bodyDirection = 0.0;
	x = 0.0;
	y = 0.0;
	vx = 0.0;
	vy = 0.0;
	theta = 0.0;
	headDirection = 0.0;
	pointDir = 0.0;
	team = "undefined";
	uniform_number = 0;
	body_b = false;
	head_b = false;
	pointing = false;
	kicking = false;
	tackling = false;
	goalie = false;
	simulation_time = -1;
	player_id = -1;
	is_in_sight_range = false;
	is_localized = false;
	is_bounded = false;
}

Player::Player(std::string name, std::string position, int simulation_time) {
	distance = 100.0;
	direction = 0.0;
	distChange = 0.0;
	dirChange = 0.0;
	bodyDirection = 0.0;
	x = 0.0;
	y = 0.0;
	vx = 0.0;
	vy = 0.0;
	theta = 0.0;
	headDirection = 0.0;
	pointDir = 0.0;
	team = "undefined";
	uniform_number = 0;
	body_b = true;
	head_b = true;
	pointing = false;
	kicking = false;
	tackling = false;
	goalie = false;
	std::vector<std::string> tokens;
	std::stringstream ss_name(name); // = std::stringstream(name);
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
	this->simulation_time = simulation_time;
	tokens.clear();
	std::stringstream ss_position(position); // = std::stringstream(position);
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
		theta = atof(tokens[4].c_str());
		headDirection = atof(tokens[5].c_str());
		break;
	case 7:
		x = atof(tokens[0].c_str());
		y = atof(tokens[1].c_str());
		vx = atof(tokens[2].c_str());
		vy = atof(tokens[3].c_str());
		theta = atof(tokens[4].c_str());
		headDirection = atof(tokens[5].c_str());
		pointDir = atof(tokens[6].c_str());
		pointing = true;
		break;
	default:
		break;
	}
	this->velocity = Vector2D::getVector2DWithXAndY(vx, vy);
	this->position = Position(x, y, theta, headDirection);
	player_id = -1;
	is_in_sight_range = true;
	is_localized = false;
	is_bounded = false;
}

Player::Player(std::string name, std::string position, int simulation_time, Position player_position, Vector2D player_velocity) {
	distance = 100.0;
	direction = 0.0;
	distChange = 0.0;
	dirChange = 0.0;
	bodyDirection = 0.0;
	headDirection = 0.0;
	pointDir = 0.0;
	x = 0.0;
	y = 0.0;
	vx = 0.0;
	vy = 0.0;
	theta = 0.0;
	team = "undefined";
	uniform_number = 0;
	body_b = false;
	head_b = false;
	pointing = false;
	kicking = false;
	tackling = false;
	goalie = false;
	bool vel = false;
	std::vector<std::string> tokens;
	std::stringstream ss_name(name); // = std::stringstream(name);
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
	std::stringstream ss_position(position); // = std::stringstream(position);
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
		body_b = true;
		head_b = true;
		break;
	case 7:
		distance = atof(tokens[0].c_str());
		direction = atof(tokens[1].c_str());
		distChange = atof(tokens[2].c_str());
		dirChange = atof(tokens[3].c_str());
		vel = true;
		bodyDirection = atof(tokens[4].c_str());
		headDirection = atof(tokens[5].c_str());
		body_b = true;
		head_b = true;
		pointDir = atof(tokens[6].c_str());
		pointing = true;
		break;
	default:
		break;
	}
	theta = bodyDirection + player_position.getBodyDirection() + player_position.getHeadDirection();
	if (theta > 180.0) {
		theta -= 360.0;
	} else if (theta <= -180.0) {
		theta += 360.0;
	}
	double source_direction = player_position.getBodyDirection() + player_position.getHeadDirection() + direction;
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
	if (body_b && head_b) {
		this->position = Position(x, y, theta, headDirection);
	} else {
		this->position = Position(x, y);
	}
	if (vel) {
		this->velocity = Vector2D::getVector2DWithXAndY(vx, vy);
	} else {
		this->velocity = Vector2D::getEmptyVector();
	}
	this->simulation_time = simulation_time;
	player_id = -1;
	is_in_sight_range = true;
	is_localized = false;
	is_bounded = false;
}

Player::~Player() {

}

Position Player::getPosition() {
	/*if (body_b && head_b) {
		return Position(x, y, theta, headDirection);
	} else {
		return Position(x, y);
	}*/
	return position;
}

std::string Player::getTeam() {
	return team;
}

int Player::getUniformNumber() {
	return uniform_number;
}

Vector2D Player::getVelocity() {
	//return Vector2D::getVector2DWithXAndY(vx, vy);
	return velocity;
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

void Player::boundTo(Player* player) {
	//bound = player;
	//double b_distance = player->distance;
	is_bounded = true;
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

void Player::pretendToBound(Player* player) {
	pretenders.push_back(player);
}

int Player::getPretendersCount() {
	return pretenders.size();
}

Player* Player::getPretenderFront() {
	return pretenders.front();
}

bool Player::localized() {
	return is_localized;
}

bool Player::bounded() {
	return is_bounded;
}

std::string Player::print() {
	return "";
}
}