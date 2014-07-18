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
 * @file World.cpp
 *
 * @author Nelson Ivan Gonzalez
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

/*
 * This methods test the hypothesis that the past player is near the current player.
 * If it is near than the distance error for the current player then it is not copied
 * in the new World Model.  The sum of the distance errors of both players is
 * used as the standard deviation assuming the errors behave as a normal distribution
 */
bool testHypothesisFor(Player* past, Player* current) {
	Position* pp = past->getPosition();
	Position* cp = current->getPosition();
	double stdv = current->getDistanceError() + past->getDistanceError();
	double x = cp->getDistanceTo(pp) / stdv;
	// Using a 90% confidence interval
	if (x < 1.64) {
		return true;
	} else {
		return false;
	}
}

void World::updateWorld(std::vector<Player> new_players, Ball new_ball, std::vector<Player> new_fs_players, Ball new_fs_ball) {
	if (Controller::AGENT_TYPE == 'p' || Controller::AGENT_TYPE == 'g') {
		fs_players = new_fs_players;
		fs_ball = new_fs_ball;
		if (Configs::PLAYER_HISTORY) {
			double vision_angle = 180.0 + 10.0;
			if (Self::VIEW_MODE_WIDTH.compare("narrow") == 0) {
				vision_angle = 60.0 + 10.0;
			}
			else if (Self::VIEW_MODE_WIDTH.compare("normal") == 0) {
				vision_angle = 120.0 + 10.0;
			}
			// TODO: We must check first the possible next position using the generated track for each player
			for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it) {
				// If the player is out of the sight range, we could add the last position of the object
				if (fabs(Self::getPosition()->getDirectionTo(it->getPosition())) > vision_angle / 2.0) {
					// But first we must check if the object is a "resonance" of another player
					bool add = true;
					for (std::vector<Player>::iterator it_c = new_players.begin(); it_c != new_players.end(); ++it_c) {
						if (testHypothesisFor(&(*it), &(*it_c))) {
							// If the hypothesis is true then it is probable that the past player is the same current player
							add = false;
							break;
						}
					}
					if (add && it->ttl < Configs::PLAYER_MAX_HISTORY) {
						if (it->isInSightRange()) {
							it->toggleSightRange();
						}
						it->ttl++;
						new_players.push_back(*it);
					}
				}
			}
		}
	}
	// If the agent is trainer or coach then it is just needed to copy the players vector and ball
	players = new_players;
	ball = new_ball;
}

WorldModel World::getWorldModel() {
	return WorldModel(players, ball, fs_players, fs_ball);
}

}
