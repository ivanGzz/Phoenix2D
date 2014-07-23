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

#include "worldtest.hpp"
#include "Self.hpp"
#include "Server.hpp"
#include "Position.hpp"
#include "Game.hpp"
#include "Configs.hpp"
#include <ctime>
#include <iostream>
#include <boost/random.hpp>
#include <cmath>

using namespace Phoenix;

namespace worldtest {

bool setup = false;
bool fullstate = false;
boost::mt19937 rng(time(0));
boost::uniform_int<> xdist(0, 104);
boost::uniform_int<> ydist(0, 68);
Position positionToGo;
int fails = 0;

void onStart() {
	if (Self::SIDE[0] == 'l') std::cout << "Starting world test" << std::endl;
	if (Self::SIDE[0] == 'l') {
		if (Server::FULLSTATE_L != 0) {
			fullstate = true;
		}
		else {
			std::cerr << "world test needs the fullstate sensor active for the left team" << std::endl;
		}
	}
}

void randomPosition() {
	double x = (double)xdist(rng) - 52.0;
	double y = (double)ydist(rng) - 34.0;
	positionToGo = Position(x, y);
}

void executeBeforeKickOff(WorldModel worldModel, std::vector<Message> messages, Commands* commands) {
	if (!setup) {
		double x = -1.0 * fabs((double)xdist(rng) - 52.0); //we need a negative coordinate in x
		double y = (double)ydist(rng) - 34.0;
		commands->move(x, y);
		setup = true;
		randomPosition();
		if (Self::SIDE[0] == 'l') {
			commands->changeView("narrow");
		}
	} else {
		const Position* p = Self::getPosition();
		Position zero(0.0, 0.0);
		if (fabs(p->getDirectionTo(&zero)) > 5.0) {
			commands->turn(p->getDirectionTo(&zero));
		}
	}
}

void executePlayOn(WorldModel worldModel, std::vector<Message> messages, Commands* commands) {
	const Position* p = Self::getPosition();
	double d = p->getDistanceTo(&positionToGo);
	if (d > 1.0) {
		double dir = p->getDirectionTo(&positionToGo);
		if (fabs(dir) > 10.0) {
			commands->turn(dir);
		} else {
			commands->dash(50.0, 0.0);
		}
	} else {
		randomPosition();
	}
	if (Self::SIDE[0] == 'l') {
		int total = -1;
		int size = worldModel.getPlayers().size();
		if (fullstate) {
			total = worldModel.getAllExactPlayers().size();
		}
		if (total > -1 && size > total - 1) {
			std::cout << Game::GAME_TIME << " bad: " << size << " out " << (total - 1) << std::endl;
			fails++;
		}
		if (Configs::LOGGING) {
			std::vector<Player*> players = worldModel.getPlayers();
			std::clog << Game::GAME_TIME << ": (" << p->getX() << ", " << p->getY() << ", " << p->getDirection() << ") "<< (total - 1) << " ";
			for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); ++it) {
				Position* pp = (*it)->getPosition();
				std::clog << "(" << pp->getX() << ", " << pp->getY() << ", " << (*it)->getPlayerId() << ", " << (*it)->getMatchValue() << ", "
						<< ((*it)->isInSightRange() ? "v" : "u") << ") ";
			}
			std::clog << std::endl;
		}
	}
}

void onFinish() {
	if (Self::SIDE[0] == 'l') {
		std::cout << "Fails: " << fails << std::endl;
		std::cout << "Finishing localization test" << std::endl;
	}
}

}
