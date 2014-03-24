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
#include <cstdlib>
#include <boost/regex.hpp>
#include <pthread.h>
#include <list>
#include <unistd.h>
#include "Parser.h"
#include "Game.h"
#include "Self.h"
#include "Flag.h"
#include "Player.h"
#include "Server.h"
#include "Position.h"
#include "World.h"
#include "Ball.h"
#include "PlayMode.h"
#include "Vector2D.h"
#include "Trainer.h"
#include "Config.h"
#include "Logger.h"
namespace Phoenix
{
static std::string sense_body_message = "";
static std::string see_message = "";
static bool see_received = false;
static bool processing_body = false;
static bool processing_see = false;
static Self* self_ptr = 0;
static Game* game_ptr = 0;
static World* world_ptr = 0;
static PlayMode* play_mode_ptr = 0;
static Trainer* trainer_ptr = 0;
static boost::regex see_regex("\\(([^()]+)\\)\\s*([\\d\\.\\-etk\\s]*)");
boost::regex hear_referee_regex("\\(hear\\s+(\\d+)\\s+referee\\s+([\\\"\\w\\s]*)\\)");
boost::regex hear_coach_regex("\\(hear\\s+(\\d+)\\s+(online_coach_left|online_coach_right)\\s+([\\\"\\w\\s]*)\\)");
boost::regex hear_trainer_regex("\\(hear\\s+(\\d+)\\s+coach\\s+([\\\"\\w\\s]*)\\)");
boost::regex hear_player_regex("\\(hear\\s+(\\d+)\\s+([\\d\\.\\-e]+)\\s+our\\s+(\\d+)\\s+([\\\"\\w\\s]+)\\)");
static pthread_cond_t see_cond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t see_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t sense_body_cond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t sense_body_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t thread_sense_body = 0;
pthread_t thread_see = 0;
pthread_attr_t attr;

bool compareFlags(Flag f0, Flag f1) {
	return f0.getDistance() > f1.getDistance(); // decreasing order
}

void *process_sense_body(void *arg) {
	int success = pthread_mutex_lock(&sense_body_mutex);
	if (success) {
		std::cerr << "Parser::process_sense_body(void*) -> cannot lock sense body mutex" << std::endl;
		return 0;
	}
	self_ptr->processSenseBody(sense_body_message);
	processing_body = false;
	success = pthread_cond_signal(&sense_body_cond);
	if (success) {
		std::cerr << "Parser::process_see(void*) -> cannot signal to blocked threads" << std::endl;
	}
	success = pthread_mutex_unlock(&sense_body_mutex);
	if (success) {
		std::cerr << "Parser::process_sense_body(void*) -> cannot unlock sense body mutex" << std::endl;
		return 0;
	}
	usleep(1000 * Server::SYNCH_SEE_OFFSET);
	success = pthread_mutex_lock(&see_mutex);
	if (success) {
		std::cerr << "Parser::process_sense_body(void*) -> cannot lock mutex" << std::endl;
		return 0;
	}
	while (processing_see) {
		success = pthread_cond_wait(&see_cond, &see_mutex);
		if (success) {
			std::cerr << "Parser::process_sense_body(void*) -> cannot wait for condition" << std::endl;
			return 0;
		}
	}
	success = pthread_mutex_unlock(&see_mutex);
	if (success) {
		std::cerr << "Parser::process_sense_body(void*) -> cannot unlock mutex" << std::endl;
	}
	if (!see_received) {
		self_ptr->localize();
		world_ptr->updateWorld();
	}
	size_t found = sense_body_message.find(" ", 12);
	game_ptr->updateTime(atoi(sense_body_message.substr(12, found - 12).c_str()));
	return 0;
}

void *process_see(void *arg) {
	int success = pthread_mutex_lock(&sense_body_mutex);
	if (success) {
		std::cerr << "Parser::process_sense_body(void*) -> cannot lock sense body mutex" << std::endl;
		return 0;
	}
	while (processing_body) {
		success = pthread_cond_wait(&sense_body_cond, &sense_body_mutex);
		if (success) {
			std::cerr << "Parser::process_sense_body(void*) -> cannot wait for condition" << std::endl;
			return 0;
		}
	}
	success = pthread_mutex_unlock(&sense_body_mutex);
	if (success) {
		std::cerr << "Parser::process_sense_body(void*) -> cannot unlock sense body mutex" << std::endl;
		return 0;
	}
	success = pthread_mutex_lock(&see_mutex);
	if (success) {
		std::cerr << "Parser::process_see(void*) -> cannot lock mutex" << std::endl;
		return 0;
	}
	int simulation_time = Game::SIMULATION_TIME;
	Position player_position = Self::getPosition();
	Vector2D player_velocity = Self::getVelocity();
	std::vector<Flag> flags;
	std::list<Player> players;
	Ball ball(Game::SIMULATION_TIME);
	std::string::const_iterator start, end;
	start = see_message.begin();
	end = see_message.end();
	boost::match_results<std::string::const_iterator> match;
	boost::match_flag_type search_flags = boost::match_default;
	while (boost::regex_search(start, end, match, see_regex, search_flags)) {
		std::string name = std::string() + match[1];
		std::string data = std::string() + match[2];
		switch (name[0]) {
		case 'g':
			break;
		case 'f':
			flags.push_back(Flag(name, data, simulation_time));
			break;
		case 'p':
			players.push_back(Player(name, data, simulation_time, player_position, player_velocity));
			break;
		case 'b':
			ball = Ball(data, simulation_time, player_position, player_velocity);
			break;
		default:
			break;
		}
		start = match[0].second;
		search_flags |= boost::match_prev_avail;
		search_flags |= boost::match_not_bob;
	}
	self_ptr->localize(flags);
	world_ptr->updateWorld(players, ball);
	processing_see = false;
	success = pthread_cond_signal(&see_cond);
	if (success) {
		std::cerr << "Parser::process_see(void*) -> cannot signal to blocked threads" << std::endl;
	}
	success = pthread_mutex_unlock(&see_mutex);
	if (success) {
		std::cerr << "Parser::process_see(void*) -> cannot unlock mutex" << std::endl;
	}
	return 0;
}

Parser::Parser(Self *self, World *world) {
	self_ptr = self;
	world_ptr = world;
	game_ptr = new Game();
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
}

Parser::~Parser() {
	pthread_attr_destroy(&attr);
	if (game_ptr) delete game_ptr;
	if (Config::VERBOSE) std::cout << "Parser out" << std::endl;
}

void Parser::parseMessage(std::string message) {
	size_t found = message.find_first_of(" ");
	std::string message_type = message.substr(1, found - 1);
	if (message_type.compare("sense_body") == 0 && !processing_body) {
		processing_body = true;
		see_received = false; //we restart this variable here because the sense_body means a new cycle
		sense_body_message = message;
		int success = pthread_create(&thread_sense_body, &attr, process_sense_body, 0);
		if (success) {
			std::cerr << "Parser::parseMessage(string) -> error creating sense_body thread" << std::endl;
		}
	} else if (message_type.compare("see") == 0 && !processing_see) {
		processing_see = true;
		see_received = true;
		see_message = message;
		int success = pthread_create(&thread_see, &attr, process_see, 0);
		if (success) {
			std::cerr << "Parser::parseMessage(string) -> error creating see thread" << std::endl;
		}
	} else if (message_type.compare("hear") == 0) {
		boost::cmatch match;
		if (boost::regex_match(message.c_str(), match, hear_referee_regex)) { //referee
			game_ptr->updatePlayMode(std::string() + match[2]);
		} else if (boost::regex_match(message.c_str(), match, hear_player_regex)) { //player
			int unum = atoi((std::string() + match[3]).c_str());
			std::string message = std::string() + match[4];
			play_mode_ptr->onMessageReceived(message, unum);
		} else if (boost::regex_match(message.c_str(), match, hear_coach_regex)) { //coach
			std::string coach = std::string() + match[2];
			if (Self::SIDE[0] == coach[13]) {

			}
		} else if (boost::regex_match(message.c_str(), match, hear_trainer_regex)) { //trainer

		} else {
			std::cerr << Game::SIMULATION_TIME << ": message not supported " << message << std::endl;
		}
	} else if (message_type.compare("change_player_type") == 0) {

	} else if (message_type.compare("see_global") == 0){
		int simulation_time = Game::SIMULATION_TIME;
		std::list<Player> players;
		Ball ball;
		std::string::const_iterator start, end;
		start = message.begin();
		end = message.end();
		boost::match_results<std::string::const_iterator> match;
		boost::match_flag_type search_flags = boost::match_default;
		while (boost::regex_search(start, end, match, see_regex, search_flags)) {
			std::string name = std::string() + match[1];
			std::string data = std::string() + match[2];
			switch (name[0]) {
			case 'g':
				break;
			case 'p':
				players.push_back(Player(name, data, simulation_time));
				break;
			case 'b':
				ball = Ball(data, simulation_time);
				break;
			default:
				break;
			}
			start = match[0].second;
			search_flags |= boost::match_prev_avail;
			search_flags |= boost::match_not_bob;
		}
		world_ptr->updateObserverWorld(players, ball);
		size_t found = message.find(" ", 12);
		game_ptr->updateTime(atoi(message.substr(12, found - 12).c_str()));
	} else if (message_type.compare("ok") == 0) {
		if (Config::VERBOSE) std::cout << Game::SIMULATION_TIME << ": " << message << std::endl;
	} else if (message_type.compare("error") == 0) {
		std::cerr << Game::SIMULATION_TIME << ": " << message << std::endl;
	} else {
		std::cerr << "Parse::parseMessage(string) -> message " << message << " not recognized" << std::endl;
	}
}

void Parser::registerPlayMode(PlayMode* play_mode) {
	play_mode_ptr = play_mode;
}

void Parser::registerTrainer(Trainer* trainer) {
	trainer_ptr = trainer;
}
}