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
 * @file WorldModel.cpp
 *
 * @author Nelson Ivan Gonzalez
 */

#include "WorldModel.hpp"
#include <list>
#include <iostream>
#include "Controller.hpp"

namespace Phoenix {

Position positionToCompare;

bool compareDistances(Player* player0, Player* player1) {
	double distance0 = player0->getPosition()->getDistanceTo(&positionToCompare);
	double distance1 = player1->getPosition()->getDistanceTo(&positionToCompare);
	return (distance0 < distance1);
}

WorldModel::WorldModel(std::vector<Player> players, Ball ball) {
	this->players = players;
	this->ball = ball;
}

WorldModel::WorldModel(std::vector<Player> players, Ball ball, std::vector<Player> fs_players, Ball fs_ball) {
	this->players = players;
	this->ball = ball;
	if (Controller::AGENT_TYPE == 'p' || Controller::AGENT_TYPE == 'g') {
		for (int i = 0; i < 12; ++i) {
			ours[i] = Player();
			opps[i] = Player();
		}
		for (std::vector<Player>::iterator it = fs_players.begin(); it != fs_players.end(); ++it) {
			if (it->getTeam().compare("our") == 0) {
				ours[it->getUniformNumber()] = *it;
			} else {
				opps[it->getUniformNumber()] = *it;
			}
		}
		this->fs_ball = fs_ball;
	}
}

WorldModel::~WorldModel() {

}

std::vector<Player*> WorldModel::getPlayers() {
	std::vector<Player*> all_players;
	for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it) {
		all_players.push_back(&(*it));
	}
	return all_players;
}

std::vector<Player*> WorldModel::getPlayersOrderedByDistanceTo(Position position) {
	std::list<Player*> all_players;
	positionToCompare = position;
	for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it) {
		all_players.push_back(&(*it));
	}
	all_players.sort(compareDistances);
	std::vector<Player*> ps(all_players.begin(), all_players.end());
	return ps;
}

std::vector<Player*> WorldModel::getOurPlayers() {
	std::vector<Player*> our_players;
	for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it) {
		if (it->getTeam().compare("our") == 0) {
			our_players.push_back(&(*it));
		}
	}
	return our_players;
}

std::vector<Player*> WorldModel::getOurPlayersOrderedByDistanceTo(Position position) {
	std::list<Player*> our_players;
	positionToCompare = position;
	for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it) {
		if (it->getTeam().compare("our") == 0) {
			our_players.push_back(&(*it));
		}
	}
	our_players.sort(compareDistances);
	std::vector<Player*> ps(our_players.begin(), our_players.end());
	return ps;
}

std::vector<Player*> WorldModel::getOppPlayers() {
	std::vector<Player*> opp_players;
	for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it) {
		if (it->getTeam().compare("opp") == 0) {
			opp_players.push_back(&(*it));
		}
	}
	return opp_players;
}

std::vector<Player*> WorldModel::getOppPlayersOrderedByDistanceTo(Position position) {
	std::list<Player*> opp_players;
	positionToCompare = position;
	for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it) {
		if (it->getTeam().compare("opp") == 0) {
			opp_players.push_back(&(*it));
		}
	}
	opp_players.sort(compareDistances);
	std::vector<Player*> ps(opp_players.begin(), opp_players.end());
	return ps;
}

std::vector<Player*> WorldModel::getUndPlayers() {
	std::vector<Player*> und_players;
	for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it) {
		if (it->getTeam().compare("undefined") == 0) {
			und_players.push_back(&(*it));
		}
	}
	return und_players;
}

std::vector<Player*> WorldModel::getUndPlayersOrderedByDistanceTo(Position position) {
	std::list<Player*> und_players;
	positionToCompare = position;
	for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it) {
		if (it->getTeam().compare("undefined") == 0) {
			und_players.push_back(&(*it));
		}
	}
	und_players.sort(compareDistances);
	std::vector<Player*> ps(und_players.begin(), und_players.end());
	return ps;
}

Player* WorldModel::getOurExactPlayer(int unum) {
	return &ours[unum];
}

Player* WorldModel::getOppExactPlayer(int unum) {
	return &opps[unum];
}

Ball* WorldModel::getBall() {
	return &ball;
}

Ball* WorldModel::getExactBall() {
	return &fs_ball;
}

}
