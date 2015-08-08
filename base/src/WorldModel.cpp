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
 * @file WorldModel.cpp
 *
 * @author Nelson I. Gonzalez
 */

#include "WorldModel.hpp"
#include <list>
#include <iostream>
#include "Controller.hpp"

namespace Phoenix {

Position positionToCompare;

bool compareDistances(Player* player0, Player* player1) {
	double distance0 = player0->distanceTo(&positionToCompare);
	double distance1 = player1->distanceTo(&positionToCompare);
	return (distance0 < distance1);
}

WorldModel::WorldModel(std::list<Player> players, Ball ball, std::list<Player> fs_players, Ball fs_ball, bool current) {
	_players = players;
	_ball = ball;
	for (std::vector<Player>::iterator it = _players.begin(); it != _players.end(); ++it) {
		_all_players.push_back(&(*it));
		if (it->team().compare("our") == 0) {
			_ours.push_back(&(*it));
		} else if (it->team().compare("opp") == 0) {
			_opps.push_back(&(*it));
		} else {
			_unds.push_back(&(*it));
		}
	}
	if (Controller::AGENT_TYPE == 'p' || Controller::AGENT_TYPE == 'g') {
		for (int i = 0; i < 12; ++i) {
			_ours[i] = Player();
			_opps[i] = Player();
		}
		_fs_players = fs_players;
		for (std::vector<Player>::iterator it = _fs_players.begin(); it != _fs_players.end(); ++it) {
			if (it->getTeam().compare("our") == 0) {
				_ours[it->uniformNumber()] = *it;
			} else {
				_opps[it->uniformNumber()] = *it;
			}
		}
		_fs_ball = fs_ball;
	}
	_current = current;
}

WorldModel::~WorldModel() {

}

std::list<Player*> WorldModel::players() {
	std::list<Player*> all_players(_all_player.begin(), _all_players.end());
	return all_players;
}

std::list<Player*> WorldModel::playersOrderedByDistanceTo(Position position) {
	std::list<Player*> all_players(_all_players.begin(). _all_players.end());
	positionToCompare = position;
	all_players.sort(compareDistances);
	return all_players;
}

std::list<Player*> WorldModel::ourPlayers() {
	std::vector<Player*> our_players(_ours.begin(), _ours.end());
	return our_players;
}

std::list<Player*> WorldModel::ourPlayersOrderedByDistanceTo(Position position) {
	std::list<Player*> our_players(_ours.begin(), _ours.end());
	positionToCompare = position;
	our_players.sort(compareDistances);
	return our_players;
}

std::list<Player*> WorldModel::oppPlayers() {
	std::list<Player*> opp_players(_opps.begin(), _opps.end());
	return opp_players;
}

std::list<Player*> WorldModel::oppPlayersOrderedByDistanceTo(Position position) {
	std::list<Player*> opp_players(_opps.begin(), _opps.end());
	positionToCompare = position;
	opp_players.sort(compareDistances);
	return opp_players;
}

std::list<Player*> WorldModel::undPlayers() {
	std::vector<Player*> und_players(_unds.begin(), _unds.end());
	return und_players;
}

std::list<Player*> WorldModel::undPlayersOrderedByDistanceTo(Position position) {
	std::list<Player*> und_players(_unds.begin(), _unds.end());
	positionToCompare = position;
	und_players.sort(compareDistances);
	return und_players;
}

std::list<Player*> WorldModel::exactPlayers() {
	std::list<Player*> e_players;
	for (std::list<Player>::iterator it = fs_players.begin(); it != fs_players.end(); ++it) {
		e_players.push_back(&(*it));
	}
	return e_players;
}

Player* WorldModel::ourExactPlayer(int unum) {
	return &ours[unum];
}

Player* WorldModel::oppExactPlayer(int unum) {
	return &opps[unum];
}

Ball* WorldModel::getBall() {
	return &ball;
}

Ball* WorldModel::getExactBall() {
	return &fs_ball;
}

}
