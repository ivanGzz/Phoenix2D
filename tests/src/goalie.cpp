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

#include "goalie.hpp"
#include "Controller.hpp"
#include "Ball.hpp"
#include "Position.hpp"
#include "Self.hpp"
#include "Server.hpp"
#include <iostream>

namespace goal {

bool setup = false;
Position positionToGo(53.0, 0.0);

void onStart() {

}

void executeBeforeKickOff(WorldModel worldModel, std::vector<Message> messages, Commands* commands) {
	if (!setup) {
		if (Controller::AGENT_TYPE == 'g') {
			commands->changeView("wide");
			commands->move(-50.0, 0.0);
		} else {
			commands->changeView("narrow");
			commands->move(-10.0, 0.0);
		}
		setup = true;
	} else {
		Ball* b = worldModel.getBall();
		const Position* p = Self::getPosition();
		if (b->isInSightRange()) {
			double dir = p->getDirectionTo(b->getPosition());
			if (fabs(dir) > 10.0) {
				commands->turn(dir);
			}
		} else {
			commands->turn(60.0);
		}
	}
}

void executeKickOffL(WorldModel worldModel, std::vector<Message> messages, Commands* commands) {
	if (Self::SIDE[0] == 'l') {
		Ball* b = worldModel.getBall();
		const Position* p = Self::getPosition();
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
}

void executeKickOffR(WorldModel worldModel, std::vector<Message> messages, Commands* commands) {
	if (Self::SIDE[0] == 'r') {
		Ball* b = worldModel.getBall();
		const Position* p = Self::getPosition();
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
}

void executePlayOn(WorldModel worldModel, std::vector<Message> messages, Commands* commands) {
	Ball* b = worldModel.getBall();
	const Position* p = Self::getPosition();
	double ed = p->getDistanceTo(b->getPosition()) - Server::PLAYER_SIZE - Server::BALL_SIZE;
	if (Controller::AGENT_TYPE == 'p') {		
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
	} else if (Controller::AGENT_TYPE == 'g') {
		if (ed < 30.0) {
			
		}
	}
}

void onFinish() {

}

}
