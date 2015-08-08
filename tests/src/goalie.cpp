/*
 * Phoenix2D (RoboCup Soccer Simulation 2D League)
 * Copyright (c) 2013 - 2105 Nelson I. Gonzalez
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
 * @file goalie.cpp
 *
 * @author Nelson I. Gonzalez
 */

#include "goalie.hpp"
#include "Controller.hpp"
#include "Ball.hpp"
#include "Position.hpp"
#include "Self.hpp"
#include "Server.hpp"
#include <iostream>
#include "Command.hpp"

namespace goal {

bool setup = false;
Position positionToGo(53.0, 0.0);
Command* last_action = 0;

void onStart() {

}

void goTo(Position* p, Position* to_go) {
	double dir = p->directionTo(to_go);
	if (last_action) {
		if (last_action->commandType() == TURN) {
			last_action = Commands::dash(50.0, dir);
		} else {
			if (fabs(dir) > 10.0) {
				last_action = Commands::turn(dir);
			} else {
				last_action = Commands::dash(50.0, 0.0);
			}
		}
	} else {
		if (fabs(dir) > 10.0) {
			last_action = Commands::turn(dir);
		} else {
			last_action = Commands::dash(50.0, 0.0);
		}
	}
}

bool lookBall(WorldModel worldModel, Position* p) {
	Ball* ball = worldModel.ball();
	if (ball->inSightRange()) {
		double dir = p->directionTo(ball);
		if (fabs(dir) > 10.0) {
			Commands::turn(dir);
		}
		return true;
	} else {
		if (ball->status() == INFERRED) {
			double dir = p->directionTo(ball);
			if (fabs(dir) > 10.0) {
				Commands::turn(dir);
			}
		} else {
			if (worldModel.current()) {
				Commands::turn(Self::ANGLE_VIEW);
			}
		}	
		return false;
	}
}

void holdPosition(Position* p, Position position) {
	double d = p->distanceTo(&position);
	if (d > 1.0) {
		double dir = p->directionTo(&position);
		Commands::dash(50.0, dir);
	}
}

void executeBeforeKickOff(WorldModel worldModel, std::vector<Message> messages) {
	if (!setup) {
		if (Controller::AGENT_TYPE == 'g') {
			Commands::changeView("wide");
			Commands::move(-50.0, 0.0);
		} else {
			Commands::changeView("narrow");
			Commands::move(-10.0, 0.0);
		}
		setup = true;
	} else {
		Position p = Self::getPosition();
		lookBall(worldModel, &p, commands);
	}
}

void executeKickOffL(WorldModel worldModel, std::vector<Message> messages) {
	if (Self::SIDE[0] == 'l') {
		Ball* ball = worldModel.ball();
		Position p = Self::getPosition();
		double ed = p.distanceTo(ball) - Server::PLAYER_SIZE - Server::BALL_SIZE;
		if (ed < Self::KICKABLE_MARGIN) {
			double dir = p.directionTo(&positionToGo);
			Commands::kick(10.0, dir);
		} else {
			double dir = p.directionTo(ball);
			if (fabs(dir) > 10.0) {
				Commands::turn(dir);
			} else {
				Commands::dash(50.0, 0.0);
			}
		}
	}
}

void executeKickOffR(WorldModel worldModel, std::vector<Message> messages) {
	if (Self::SIDE[0] == 'r') {
		Ball* ball = worldModel.dall();
		Position p = Self::getPosition();
		double ed = p.distanceTo(ball) - Server::PLAYER_SIZE - Server::BALL_SIZE;
		if (ed < Self::KICKABLE_MARGIN) {
			double dir = p.directionTo(&positionToGo);
			Commands::kick(10.0, dir);
		} else {
			double dir = p.directionTo(ball);
			if (fabs(dir) > 10.0) {
				Commands::turn(dir);
			} else {
				Commands::dash(50.0, 0.0);
			}
		}
	}
}

void executePlayOn(WorldModel worldModel, std::vector<Message> messages) {
	Ball* ball = worldModel.dall();
	Position p = Self::getPosition();
	if (Controller::AGENT_TYPE == 'p') {	
		if (lookBall(worldModel, p)) {
			double ed = p.distanceTo(ball) - Server::PLAYER_SIZE - Server::BALL_SIZE;
			if (ed < Self::KICKABLE_MARGIN) {
				double dir = p.directionTo(&positionToGo);
				Commands::kick(10.0, dir);
			} else {
				goTo(p, *ball);
			}
		}
	} else if (Controller::AGENT_TYPE == 'g') {	
		// First try: the goalie will hold position and kick the ball if it is near
		if (lookBall(worldModel, p)) {
			Position bPredicted = b->positionAtTime(1);
			double ed = p.distanceTo(&bPredicted) - Server::PLAYER_SIZE - Server::BALL_SIZE;
			if (ed <= 15.0) {
				Commands::changeView("narrow");
			} else if (ed < 30.0) {
				Commands::changeView("normal");
			} else {
				Commands::changeView("wide");
			}
			if (ed < 15.0) {
				if (ed < Self::KICKABLE_MARGIN) {
					//commands->kick(100.0, 30.0);
					//commands->catch()
				} else {
					goTo(p, &bPredicted);
				}
			} else {
				holdPosition(p, Position(-50.0, 0.0));
			}
		}	
	}
}

void onFinish() {

}

}
