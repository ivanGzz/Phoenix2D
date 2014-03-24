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
#include "World.h"
#include "Game.h"
#include "Config.h"
#include "Self.h"
#include "Controller.h"
namespace Phoenix
{
std::list<Player> players;
Ball ball;

World::World() {

}

World::~World() {
	if (Config::VERBOSE) std::cout << "World out" << std::endl;
}

void World::updateWorld() {
	double vision_angle = 180.0 + 10.0;
	if (Self::VIEW_MODE_WIDTH.compare("narrow") == 0) {
		vision_angle = 60.0 + 10.0;
	} else if (Self::VIEW_MODE_WIDTH.compare("normal") == 0) {
		vision_angle = 120.0 + 10.0;
	}
	for (std::list<Player>::iterator it = players.begin(); it != players.end(); ++it) {
		if (std::abs(Self::getPosition().getDirectionTo(it->getPosition())) > vision_angle / 2.0) {
			it->toggleSightRange();
		} else if (!(it->isInSightRange())) {
			it->toggleSightRange();
		}
	}
}

void World::updateWorld(std::list<Player> new_players, Ball new_ball) {
	if (Config::PLAYER_HISTORY) {
		double vision_angle = 180.0 + 10.0;
		if (Self::VIEW_MODE_WIDTH.compare("narrow") == 0) {
			vision_angle = 60.0 + 10.0;
		} else if (Self::VIEW_MODE_WIDTH.compare("normal") == 0) {
			vision_angle = 120.0 + 10.0;
		}
		for (std::list<Player>::iterator it = players.begin(); it != players.end(); ++it) {
			if (std::abs(Self::getPosition().getDirectionTo(it->getPosition())) > vision_angle / 2.0) { //out the sight range
				new_players.push_back(*it);
			} else { //in the sight range
				double min_distance = 120.0;
				Player* nearest_player = 0;
				for (std::list<Player>::iterator it_new = new_players.begin(); it_new != new_players.end(); ++it_new) {
					double distance = it->getPosition().getDistanceTo(it_new->getPosition());
					if (distance < min_distance) {
						nearest_player = &(*it);
						min_distance = distance;
					}
				}
				if (nearest_player) {
					nearest_player->pretendToBound(&(*it));
				}
			}
		}
		for (std::list<Player>::iterator it = players.begin(); it != players.end(); ++it) {
			switch (it->getPretendersCount()) {
			case 0:
				//Nobody wants me :'(
				break;
			default: // > 0
				Player* pretender = it->getPretenderFront();
				pretender->boundTo(&(*it));
				break;
			}
		}
	}
	players.swap(new_players);
	ball = new_ball;
}

void World::updateObserverWorld(std::list<Player> new_players, Ball new_ball) {
	players = new_players;
	ball = new_ball;
}

WorldModel World::getWorldModel() {
	return WorldModel(players, ball);
}
}