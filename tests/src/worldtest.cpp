/*
 * Phoenix2D (RoboCup Soccer Simulation 2D League)
 * Copyright (c) 2013 - 2015 Nelson I. Gonzalez
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
 * @file worldtest.cpp
 *
 * @author Nelson I. Gonzalez
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
int r_matches = 0;
int m_matches = 0;
int c_matches = 0;
int r_accum_matches = 0;
int m_accum_matches = 0;
int c_accum_matches = 0;
int iteration = -1;
int cycles = 0;

void onStart() {
	std::cout << "Starting world test" << std::endl;
	if (Server::FULLSTATE_L != 0 && Server::FULLSTATE_R != 0) {
		fullstate = true;
	}
	else {
		std::cerr << "world test needs the fullstate sensor active for the left team" << std::endl;
	}
}

void randomPosition() {
	double x = (double)xdist(rng) - 52.0;
	double y = (double)ydist(rng) - 34.0;
	positionToGo = Position(x, y);
}

void executeBeforeKickOff(WorldModel worldModel, std::vector<Message> messages) {
	if (!setup) {
		if (iteration > -1) {
			if (Configs::LOGGING) {
				int dr = r_matches - r_accum_matches;
				int dm = m_matches - m_accum_matches;
				int dc = c_matches - c_accum_matches;
//				std::clog << Configs::TRACKING_THRESHOLD << ": " << dr << ", " << dm << ", " << dc << ", " << cycles << std::endl;
				std::clog << dr << "," << dm << "," << dc << std::endl;
				std::cout << "Iteration " << iteration << std::endl;
				std::cout << "Matches percentage: " << ((double)dc / (double)dm) << std::endl;
				std::cout << "Total percentage:   " << ((double)dc / (double)dr) << std::endl;
			}
			cycles = 0;
		}
		double x = -1.0 * fabs((double)xdist(rng) - 52.0); //we need a negative coordinate in x
		double y = (double)ydist(rng) - 34.0;
		Commands::move(x, y);
		setup = true;
		randomPosition();
		Commands::changeView("narrow");
		iteration++;
//		Configs::TRACKING_THRESHOLD = (double)Self::UNIFORM_NUMBER + ((Self::SIDE[0] == 'l') ? -1.0 : 4.0) + 0.1 * (iteration / 10);
	} else {
		Position p = Self::getPosition();
		Position zero(0.0, 0.0);
		if (fabs(p.directionTo(&zero)) > 5.0) {
			Commands::turn(p.directionTo(&zero));
		}
	}
	r_accum_matches = worldModel.real_matches;
	m_accum_matches = worldModel.method_matches;
	c_accum_matches = worldModel.correct_matches;
}

void executePlayOn(WorldModel worldModel, std::vector<Message> messages) {
	Position p = Self::getPosition();
	double d = p.distanceTo(&positionToGo);
	if (d > 1.0) {
		double dir = p.directionTo(&positionToGo);
		if (fabs(dir) > 10.0) {
			Commands::turn(dir);
		} else {
			Commands::dash(50.0, 0.0);
		}
	} else {
		randomPosition();
	}
	int total = -1;
	int size = worldModel.players().size();
	if (fullstate) {
		total = worldModel.exactPlayers().size();
	}
	if (total > -1 && size > total - 1) {
		std::cout << Game::GAME_TIME << " bad: " << size << " out " << (total - 1) << std::endl;
		fails++;
	}
	r_matches = worldModel.real_matches;
	m_matches = worldModel.method_matches;
	c_matches = worldModel.correct_matches;
	cycles++;
	setup = false;
}

void onFinish() {
	if (Self::SIDE[0] == 'l') {
		std::cout << "Fails: " << fails << std::endl;
		std::cout << "Finishing localization test" << std::endl;
	}
}

}
