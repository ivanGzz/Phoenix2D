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

#include "WorldModel.h"
namespace Phoenix
{

Position positionToCompare;

bool compareDistances(Player* player0, Player* player1) {
	double distance0 = player0->getPosition().getDistanceTo(positionToCompare);
	double distance1 = player1->getPosition().getDistanceTo(positionToCompare);
	return (distance0 < distance1);
}

WorldModel::WorldModel(std::list<Player> players, Ball ball) {
	this->players = players;
	this->ball = ball;
}

WorldModel::~WorldModel() {

}

std::list<Player*> WorldModel::getPlayers() {
	std::list<Player*> all_players;
	for (std::list<Player>::iterator it = players.begin(); it != players.end(); ++it) {
		all_players.push_back(&(*it));
	}
	return all_players;
}

std::list<Player*> WorldModel::getPlayersOrderedByDistanceTo(Position position) {
	std::list<Player*> all_players;
	positionToCompare = position;
	for (std::list<Player>::iterator it = players.begin(); it != players.end(); ++it) {
		all_players.push_back(&(*it));
	}
	all_players.sort(compareDistances);
	return all_players;
}

std::list<Player*> WorldModel::getOurPlayers() {
	std::list<Player*> our_players;
	for (std::list<Player>::iterator it = players.begin(); it != players.end(); ++it) {
		if (it->getTeam().compare("our") == 0) {
			our_players.push_back(&(*it));
		}
	}
	return our_players;
}

std::list<Player*> WorldModel::getOurPlayersOrderedByDistanceTo(Position position) {
	std::list<Player*> our_players;
	positionToCompare = position;
	for (std::list<Player>::iterator it = players.begin(); it != players.end(); ++it) {
		if (it->getTeam().compare("our") == 0) {
			our_players.push_back(&(*it));
		}
	}
	our_players.sort(compareDistances);
	return our_players;
}

std::list<Player*> WorldModel::getOppPlayers() {
	std::list<Player*> opp_players;
	for (std::list<Player>::iterator it = players.begin(); it != players.end(); ++it) {
		if (it->getTeam().compare("opp") == 0) {
			opp_players.push_back(&(*it));
		}
	}
	return opp_players;
}

std::list<Player*> WorldModel::getOppPlayersOrderedByDistanceTo(Position position) {
	std::list<Player*> opp_players;
	positionToCompare = position;
	for (std::list<Player>::iterator it = players.begin(); it != players.end(); ++it) {
		if (it->getTeam().compare("opp") == 0) {
			opp_players.push_back(&(*it));
		}
	}
	opp_players.sort(compareDistances);
	return opp_players;
}

std::list<Player*> WorldModel::getUndPlayers() {
	std::list<Player*> und_players;
	for (std::list<Player>::iterator it = players.begin(); it != players.end(); ++it) {
		if (it->getTeam().compare("undefined") == 0) {
			und_players.push_back(&(*it));
		}
	}
	return und_players;
}

std::list<Player*> WorldModel::getUndPlayersOrderedByDistanceTo(Position position) {
	std::list<Player*> und_players;
	positionToCompare = position;
	for (std::list<Player>::iterator it = players.begin(); it != players.end(); ++it) {
		if (it->getTeam().compare("undefined") == 0) {
			und_players.push_back(&(*it));
		}
	}
	und_players.sort(compareDistances);
	return und_players;
}

Ball* WorldModel::getBall() {
	return &ball;
}
}