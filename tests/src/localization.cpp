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
 * @file localization.cpp
 *
 * @author Nelson I. Gonzalez
 */

#include "localization.hpp"
#include <ctime>
#include <iostream>
#include <boost/random.hpp>
#include <cmath>
#include "Position.hpp"
#include "Self.hpp"
#include "Server.hpp"
#include "Game.hpp"
#include "Configs.hpp"

namespace localization {

bool setup = false;
bool fullstate = false;
boost::mt19937 rng(time(0));
boost::uniform_int<> xdist(0, 104);
boost::uniform_int<> ydist(0, 68);
Position positionToGo;
std::vector<double> error_means;
std::vector<double> dir_means;
double error_accum = 0.0;
double dir_accum = 0.0;
int iteration = -1;
int cycles = 0;

void onStart() {
	std::cout << "Starting localization test" << std::endl;
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

void executeBeforeKickOff(WorldModel worldModel, std::vector<Message> messages) {
	if (!setup) {
		if (iteration > -1) {
			double mean = error_accum / cycles;
			std::cout << "Iteration: " << iteration << ", error mean: " << mean << ", direction error mean: ";
			std::clog << mean << ",";
			error_means.push_back(mean);
			mean = dir_accum / cycles;
			std::cout << mean << std::endl;
			std::clog << mean << std::endl;
			dir_means.push_back(mean);
		}
		double x = -1.0 * fabs((double)xdist(rng) - 52.0); //we need a negative coordinate in x
		double y = (double)ydist(rng) - 34.0;
		std::cout << "Moving to: (" << x << ", " << y << ")" << std::endl;
		Commands::changeView("narrow");
		Commands::move(x, y);
		setup = true;
		randomPosition();
		error_accum = 0.0;
		dir_accum = 0.0;
		cycles = 0;
		iteration++;
	}
}

void executePlayOn(WorldModel worldModel, std::vector<Message> messages) {
	Position p = Self::getPosition();
	if (fullstate) {
		Player* pl = worldModel.ourExactPlayer(Self::UNIFORM_NUMBER);
//		std::cout << Game::GAME_TIME << ": (" << p->x << ", " << p->y << ", " << p->body << ")"
//				                     << ", (" << e_p->x << ", " << e_p->y << ", " << e_p->body << ")"
//				                     << std::endl;
		error_accum += sqrt(pow(p.x() - pl->x(), 2.0) + pow(p.y() - pl->y(), 2.0));
		double min_arc = p.body() - pl->body();
		if (min_arc > 180.0) {
			min_arc -= 360.0;
		} else if (min_arc < -180.0) {
			min_arc += 360.0;
		}
		dir_accum += fabs(min_arc);
	}
	double d = p->distanceTo(&positionToGo);
	if (d > 1.0) {
		double dir = p->directionTo(&positionToGo);
		if (fabs(dir) > 10.0) {
			Commands::turn(dir);
		} else {
			Commands::dash(50.0, 0.0);
		}
	} else {
		std::cout << p.x() << " " << p.y() << " " << p.body() << std::endl;
		randomPosition();
	}
	cycles++;
	if (setup) {
		setup = false;
	}
}

void onFinish() {
	std::cout << "Finishing localization test" << std::endl;
}

}
