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
 * @file Player.cpp
 *
 * @author Nelson I. Gonzalez
 */

#include <sstream>
#include <cstdlib>
#include <cmath>
#include "Player.hpp"
#include "Self.hpp"
#include "Controller.hpp"
#include "constants.hpp"
#include "Server.hpp"

namespace Phoenix {

static std::string pos_chars  = ")*+-./0123456789<>?ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz";

Player::Player() {
	distance = 100.0;
	direction = 0.0;
	dist_change = 0.0;
	dir_change = 0.0;
	body_direction = 0.0;
	head_direction = 0.0;
	point_dir = 0.0;
	has_body = false;
	has_head = false;
	_is_pointing = false;
	_is_kicking = false;
	_is_tackling = false;
	_is_goalie = false;
	_team = "undefined";
	_uniform_number = 0;
	_player_id = -1;
	_error = 0.0;
	ttl = 0;
	tracked = false;
	match = -1.0;
	_real_uniform_number = 0;
	_real_team = "undefined";
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
		_team = team_t;
	} else if (team_t.compare(Self::TEAM_NAME) == 0) {
		_team = "our";
	} else {
		_team = "opp";
	}
	if (tokens.size() > 3) {
		_is_goalie = true;
	}
	_uniform_number = atoi(tokens[2].c_str());
	tokens.clear();
	std::stringstream ss_position(position);
	while (std::getline(ss_position, token, ' ')) {
		if (token.compare("k") == 0) {
			_is_kicking = true;
		} else if (token.compare("t") == 0) {
			_is_tackling = true;
		} else {
			tokens.push_back(token);
		}
	}
	switch (tokens.size()) {
	case 6:
		_x = atof(tokens[0].c_str());
		_y = atof(tokens[1].c_str());
		_vx = atof(tokens[2].c_str());
		_vy = atof(tokens[3].c_str());
		_body = atof(tokens[4].c_str());
		_head = atof(tokens[5].c_str());
		break;
	case 7:
		_x = atof(tokens[0].c_str());
		_y = atof(tokens[1].c_str());
		_vx = atof(tokens[2].c_str());
		_vy = atof(tokens[3].c_str());
		_body = atof(tokens[4].c_str());
		_head = atof(tokens[5].c_str());
		point_dir = atof(tokens[6].c_str());
		_is_pointing = true;
		break;
	default:
		break;
	}
	_status = LOCALIZED;
}

void Player::setDataForPlayer(std::string name, std::string position) {
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
			_team = "our";
		} else {
			_team = "opp";
		}
		break;
	case 3:
		team_t = tokens[1].substr(1, tokens[1].length() - 2);
		if (team_t.compare(Self::TEAM_NAME) == 0) {
			_team = "our";
		} else {
			_team = "opp";
		}
		_uniform_number = atoi(tokens[2].c_str());
		break;
	case 4: //goalie
		team_t = tokens[1].substr(1, tokens[1].length() - 2);
		if (team_t.compare(Self::TEAM_NAME) == 0) {
			_team = "our";
		} else {
			_team = "opp";
		}
		_uniform_number = atoi(tokens[2].c_str());
		_is_goalie = true;
		break;
	default:
		break;
	}
	tokens.clear();
	std::stringstream ss_position(position);
	while (std::getline(ss_position, token, ' ')) {
		if (token.compare("k") == 0) {
			_is_kicking = true;
		} else if (token.compare("t") == 0) {
			_is_tackling = true;
		} else {
			tokens.push_back(token);
		}
	}
	_status = POSITION;
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
		point_dir = atof(tokens[2].c_str());
		_is_pointing = true;
		break;
	case 4:
		distance = atof(tokens[0].c_str());
		direction = atof(tokens[1].c_str());
		dist_change = atof(tokens[2].c_str());
		dir_change = atof(tokens[3].c_str());
		_status = LOCALIZED;
		break;
	case 5:
		distance = atof(tokens[0].c_str());
		direction = atof(tokens[1].c_str());
		dist_change = atof(tokens[2].c_str());
		dir_change = atof(tokens[3].c_str());
		point_dir = atof(tokens[4].c_str());
		_is_pointing = true;
		_status = LOCALIZED;
		break;
	case 6:
		distance = atof(tokens[0].c_str());
		direction = atof(tokens[1].c_str());
		dist_change = atof(tokens[2].c_str());
		dir_change = atof(tokens[3].c_str());
		body_direction = atof(tokens[4].c_str());
		head_direction = atof(tokens[5].c_str());
		has_body = true;
		has_head = true;
		_status = LOCALIZED;
		break;
	case 7:
		distance = atof(tokens[0].c_str());
		direction = atof(tokens[1].c_str());
		dist_change = atof(tokens[2].c_str());
		dir_change = atof(tokens[3].c_str());
		body_direction = atof(tokens[4].c_str());
		head_direction = atof(tokens[5].c_str());
		has_body = true;
		has_head = true;
		point_dir = atof(tokens[6].c_str());
		_is_pointing = true;
		_status = LOCALIZED;
		break;
	default:
		break;
	}
	_real_team = _team;
	_real_uniform_number = _uniform_number;
}

void Player::initForPlayer(Position player_position, Geometry::Vector2D player_velocity) {
	double source_direction = player_position.body() + player_position.neck() + direction;
	if (source_direction > 180.0) {
		source_direction -= 360.0;
	} else if (source_direction <= 180.0) {
		source_direction += 360.0;
	}
	double erx = cos(Math::PI * source_direction / 180.0);
	double ery = sin(Math::PI * source_direction / 180.0);
	x = player_position.x() + erx * distance;
	y = player_position.y() + ery * distance;
	if (distance > 0.1) {
		_error = (distance - exp(log(distance - 0.1) - Server::QUANTIZE_STEP)) / 2.0;
	}
	if (has_body && has_head) {
		_body = body_direction + player_position.body() + player_position.neck();
		if (_body > 180.0) {
			_body -= 360.0;
		} else if (_body <= -180.0) {
			_body += 360.0;
		}
	}
	if (_status == LOCALIZED) {
		double erxm = (180.0 * erx) / (Math::PI * distance);
		double erym = (180.0 * ery) / (Math::PI * distance);
		double vry = (dist_change * erym + dir_change * erx) / (ery * erym + erx * erxm);
		double vrx = (dist_change - ery * vry) / erx;
		_vx = player_velocity.dx + vrx;
		_vy = player_velocity.dy + vry;
		double m = sqrt(vx * vx + vy * vy);
		if (m > Self::PLAYER_SPEED_MAX) {
			_vx = _vx * Self::PLAYER_SPEED_MAX / m;
			_vy = _vy * Self::PLAYER_SPEED_MAX / m;
		}
	}	
}

void Player::initForFullstate(std::string team, int unum, double x, double y, double vx, double vy, double b, double n) {
	if (Self::SIDE[0] == team[0]) {
		_team = "our";
	} else {
		_team = "opp";
	}
	_uniform_number = unum;
	_x = x;
	_y = y;
	_vx = vx;
	_vy = vy;
	_body = b;
	_head = n;
}

void Player::decode(Position from, char position, bool our) {
	size_t pos = pos_chars.find(position);
	int dist_index = pos / 9;
	int dir_index = pos % 9;
	distance = 5.0 + 5.0 * dist_index;
	dirrection = -24.0 + 6.0 * dir_index;
	_x = from.x() + distance * cos(from.body() + direction);
	_y = from.y() + distance * sin(from.body() + direction);
	if (our) {
		_team = "our";
	} else {
		_team = "opp";
	}
}

char Player::encode() {
	double dist = distance;
	if (dist > 39.0) {
		return FAR;
	}
	double dir = direction;
	if (dir > 24.0) {
		dir = 24.0;
	} else if (dir < -24.0) {
		dir = -24.0;
	}
	int dist_index = (int)dist / 5;
	int dir_index = 4 + (int)dir / 6;
	return pos_chars[9 * dist_index + dir_index];
}

std::string Player::team() {
	return _team;
}

std::string Player::realTeam() {
	return _real_team;
}

int Player::uniformNumber() {
	return _uniform_number;
}

int Player::realUniformNumber() {
	return _real_uniform_number;
}

bool Player::goalie() {
	return _is_goalie;
}

bool Player::pointing() {
	return _is_pointing;
}

double Player::pointingDirection() {
	return point_dir;
}

bool Player::kicking() {
	return _is_kicking;
}

bool Player::tackling() {
	return _is_tackling;
}

int Player::playerId() {
	return _player_id;
}

double Player::distanceError() {
	return _error;
}

}
