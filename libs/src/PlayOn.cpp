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

#include <iostream>
#include <vector>
#include <boost/circular_buffer.hpp>
#include "PlayOn.h"
#include "Commands.h"
#include "Game.h"
#include "Self.h"
#include "Actions.h"
#include "Player.h"
#include "Config.h"
namespace Phoenix
{
boost::circular_buffer<Position> positions(4);
bool move = false;

PlayOn::PlayOn(Commands* commands, Actions* actions) : PlayMode(commands) {
	this->actions = actions;
}

PlayOn::~PlayOn() {

}

void PlayOn::setup(WorldModel world) {
	if (Config::LOGGING) {
		std::list<Player*> players = world.getPlayers();
		std::clog << Game::GAME_TIME  << Self::getPosition().toString() << " [" << players.size() << "]";
		for (std::list<Player*>::iterator it = players.begin(); it != players.end(); ++it) {
			std::clog << " - " << (*it)->getTeam() << "(" << (*it)->getUniformNumber() << "): [" << ((*it)->getPosition()).toString() << "," << ((*it)->getVelocity()).toString() << "]";
		}
		std::clog << std::endl;
		std::clog.flush();
	} else {
		switch (Self::UNIFORM_NUMBER) {
		case 1:
			if (Self::TEAM_NAME.compare("Nemesis") == 0) {
				positions.push_back(Position(0.0, 0.0));
			}
			move = true;
			break;
		case 2:
			if (Self::TEAM_NAME.compare("Nemesis") == 0) {
				positions.push_back(Position(-30.0, -20.0));
			} else {
				positions.push_back(Position(40.0, 0.0));
				positions.push_back(Position(40.0, 20.0));
			}
			move = true;
			break;
		case 3:
			if (Self::TEAM_NAME.compare("Nemesis") == 0) {
				positions.push_back(Position(-20.0, 15.0));
			} else {
				positions.push_back(Position(50.0, -30.0));
			}
			move = true;
			break;
		default:
			break;
		}
	}
	commands->changeView("narrow");
}

void PlayOn::onPlayerExecute(WorldModel world) {
	if (move) {
		if (actions->goTo(positions.front())) {
			if (positions.size() > 1) {
				positions.rotate(positions.begin() + 1);
			}
		}
	}
	if (Config::LOGGING) {
		std::list<Player*> players = world.getPlayers();
		std::clog << Game::GAME_TIME  << Self::getPosition().toString() << " [" << players.size() << "]";
		for (std::list<Player*>::iterator it = players.begin(); it != players.end(); ++it) {
			std::clog << " - " << (*it)->getTeam() << "(" << (*it)->getUniformNumber() << "): [" << ((*it)->getPosition()).toString() << "," << ((*it)->getVelocity()).toString() << "]";
		}
		std::clog << std::endl;
		std::clog.flush();
	}
}

void PlayOn::onGoalieExecute(WorldModel world) {

}

void PlayOn::onCoachExecute(WorldModel world) {

}

void PlayOn::onMessageReceived(std::string message, int sender) {

}
}