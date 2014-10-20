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

#include "dribble.hpp"
#include <ctime>
#include <iostream>
#include <boost/random.hpp>
#include <cmath>
#include "Position.hpp"
#include "Ball.hpp"
#include "Self.hpp"
#include "Server.hpp"
#include "Game.hpp"

namespace dribble {

bool setup = false;
bool fullstate = false;
boost::mt19937 rng(time(0));
boost::uniform_int<> xdist(0, 104);
boost::uniform_int<> ydist(0, 68);
Position positionToGo;

void onStart() {
	std::cout << "Starting dribble test" << std::endl;
	if (Self::SIDE[0] == 'l') {
		if (Server::FULLSTATE_L != 0) {
			fullstate = true;
		}
		else {
			std::cerr << "localization test needs the fullstate sensor active for the left team" << std::endl;
		}
	}
	else {
		if (Server::FULLSTATE_R != 0) {
			fullstate = true;
		}
		else {
			std::cerr << "localization test needs the fullstate sensor active for the right team" << std::endl;
		}
	}
}

void randomPosition() {
	double x = (double)xdist(rng) - 52.0;
	double y = (double)ydist(rng) - 34.0;
	positionToGo = Position(x, y);
	std::cout << "New random position: (" << x << ", " << y << ")" << std::endl;
}

void executeBeforeKickOff(WorldModel worldModel, std::vector<Message> messages, Commands* commands) {
	if (!setup) {
		double x = -1.0 * fabs((double)xdist(rng) - 52.0); //we need a negative coordinate in x
		double y = (double)ydist(rng) - 34.0;
		std::cout << "Moving to: (" << x << ", " << y << ")" << std::endl;
		commands->move(x, y);
		commands->changeView("narrow");
		setup = true;
		randomPosition();
	} else {
		const Position* p = Self::getPosition();
		Ball* ball = worldModel.getBall();
		if (ball->isInSightRange()) {
			double dir = p->getDirectionTo(ball->getPosition());
			if (fabs(dir) > 20.0) {
				commands->turn(dir);
			}
		} else {
			commands->turn(60.0);
		}
	}
}

void executePlayOn(WorldModel worldModel, std::vector<Message> messages, Commands* commands) {
	Ball* b = worldModel.getBall();
	const Position* p = Self::getPosition();
	if (b->getPosition()->getDistanceTo(&positionToGo) <= 2.0) {
		randomPosition();
	}
	double ed = p->getDistanceTo(b->getPosition()) - Server::PLAYER_SIZE - Server::BALL_SIZE;
	if (ed < Self::KICKABLE_MARGIN) {
		double dir = p->getDirectionTo(&positionToGo);
		commands->kick(10.0, dir);
	} else {
		double dir = p->getDirectionTo(b->getPosition());
		if (fabs(dir) > 10.0) {
			commands->turn(dir);
		} else {
			commands->dash(50.0, 0.0);
		}
	}
}

void onFinish() {
	std::cout << "Finishing dribble test" << std::endl;
}

}
