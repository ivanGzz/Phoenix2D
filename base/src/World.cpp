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

#include <cmath>
#include <iostream>
#include "World.hpp"
#include "Game.hpp"
#include "Configs.hpp"
#include "Self.hpp"
#include "Controller.hpp"

namespace Phoenix {

static std::vector<Player> players;
static Ball ball;
static std::vector<Player> fs_players;
static Ball fs_ball;

World::World() {

}

World::~World() {
	if (Configs::VERBOSE) std::cout << "World out" << std::endl;
}

void World::updateWorld() {
	double vision_angle = 180.0 + 10.0;
	if (Self::VIEW_MODE_WIDTH.compare("narrow") == 0) {
		vision_angle = 60.0 + 10.0;
	} else if (Self::VIEW_MODE_WIDTH.compare("normal") == 0) {
		vision_angle = 120.0 + 10.0;
	}
	for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it) {
		if (std::abs(Self::getPosition().getDirectionTo(*it->getPosition())) > vision_angle / 2.0) {
			it->toggleSightRange();
		} else if (!(it->isInSightRange())) {
			it->toggleSightRange();
		}
	}
}

void World::updateWorld(std::vector<Player> new_players, Ball new_ball) {
	if (Configs::PLAYER_HISTORY) {
		double vision_angle = 180.0 + 10.0;
		if (Self::VIEW_MODE_WIDTH.compare("narrow") == 0) {
			vision_angle = 60.0 + 10.0;
		} else if (Self::VIEW_MODE_WIDTH.compare("normal") == 0) {
			vision_angle = 120.0 + 10.0;
		}
		for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it) {
			//If the player is out of the sight range, we add the last position of the object
			if (std::abs(Self::getPosition().getDirectionTo(*it->getPosition())) > vision_angle / 2.0) {
				new_players.push_back(*it);
			}
		}
	}
	//In C++11 we will be able to do players.swap(new_players);
	players = new_players;
	ball = new_ball;
}

void World::updateWorld(std::vector<Player> new_players, Ball new_ball, std::vector<Player> new_fs_players, Ball new_fs_ball) {
	fs_players = new_fs_players;
	fs_ball = new_fs_ball;
	if (Configs::PLAYER_HISTORY) {
		double vision_angle = 180.0 + 10.0;
		if (Self::VIEW_MODE_WIDTH.compare("narrow") == 0) {
			vision_angle = 60.0 + 10.0;
		} else if (Self::VIEW_MODE_WIDTH.compare("normal") == 0) {
			vision_angle = 120.0 + 10.0;
		}
		for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it) {
			//If the player is out of the sight range, we add the last position of the object
			if (std::abs(Self::getPosition().getDirectionTo(*it->getPosition())) > vision_angle / 2.0) {
				new_players.push_back(*it);
			}
		}
	}
	//In C++11 we will be able to do players.swap(new_players);
	players = new_players;
	ball = new_ball;
}

void World::updateObserverWorld(std::vector<Player> new_players, Ball new_ball) {
	players = new_players;
	ball = new_ball;
}

WorldModel World::getWorldModel() {
	return WorldModel(players, ball);
}

}
