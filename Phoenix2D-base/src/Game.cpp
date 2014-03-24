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
#include <pthread.h>
#include <boost/regex.hpp>
#include "Self.h"
#include "Game.h"
#include "Config.h"
namespace Phoenix
{
std::string play_modes = "before_kick_off corner_kick_l corner_kick_r free_kick_l free_kick_r goal_kick_l goal_kick_r kick_in_l kick_in_r kick_off_l kick_off_r play_on";
std::string events = "drop_ball goal_l goal_r offside_l offside_r";
boost::regex goal_regex("goal_(l|r)_(\\d+)");
static bool cycle_flag = false;
static bool on_game = true;
static pthread_cond_t cycle_cond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t cycle_mutex = PTHREAD_MUTEX_INITIALIZER;

unsigned int Game::GAME_TIME = 0;
unsigned int Game::SIMULATION_TIME = 0;
unsigned int Game::GOALS = 0;
unsigned int Game::GOALS_AGAINST = 0;
std::string Game::PLAY_MODE = "before_kick_off";

Game::Game() {

}

Game::~Game() {
	if (Config::VERBOSE) std::cout << "Game out" << std::endl;
}

void Game::updateTime(int game_time) {
	int success = pthread_mutex_lock(&cycle_mutex);
	if (success) {
		std::cerr << "Game::updateTimes(int) -> can not lock mutex" << std::endl;
		return;
	}
	Game::GAME_TIME = game_time;
	Game::SIMULATION_TIME++;
	cycle_flag = true;
	success = pthread_mutex_unlock(&cycle_mutex);
	if (success) {
		std::cerr << "Game::updateTimes(int) -> can not unlock mutex" << std::endl;
	}
	success = pthread_cond_signal(&cycle_cond);
	if (success) {
		std::cerr << "Game::updateTime(int) -> can not signal to blocked threads" << std::endl;
	}
}

void Game::updatePlayMode(std::string play_mode) {
	boost::cmatch match;
	if (boost::regex_match(play_mode.c_str(), match, goal_regex)) {
		int goals = atoi((std::string() + match[2]).c_str());
		if (Self::SIDE.compare(match[1])) {
			Game::GOALS = goals;
		} else {
			Game::GOALS_AGAINST = goals;
		}
		play_mode = std::string() + "goal_" + match[1];
	}
	if (play_modes.find(play_mode) != std::string::npos) {
		Game::PLAY_MODE = play_mode;
	} else if (play_mode.compare("time_over") == 0) {
		on_game = false;
	} else if (events.find(play_mode) != std::string::npos) {
		std::cout << Game::SIMULATION_TIME << ": " << play_mode << std::endl;
	} else {
		std::cerr << "Not recognized: " << play_mode;
	}
}

bool Game::nextCycle() {
	int success = pthread_mutex_lock(&cycle_mutex);
	if (success) {
		std::cerr << "Game::nextCycle() -> can not lock mutex" << std::endl;
		return false;
	}
	while (!cycle_flag) {
		success = pthread_cond_wait(&cycle_cond, &cycle_mutex);
		if (success) {
			std::cerr << "Game::nextCycle() -> can not wait for condition" << std::endl;
			return false;
		}
	}
	cycle_flag = false;
	success = pthread_mutex_unlock(&cycle_mutex);
	if (success) {
		std::cerr << "Game::nextCycle() -> can not unlock mutex" << std::endl;
	}
	return on_game;
}
}