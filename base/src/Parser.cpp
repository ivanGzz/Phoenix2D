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
#include <vector>
#include <unistd.h>
#include "Parser.hpp"
#include "Game.hpp"
#include "Self.hpp"
#include "Flag.hpp"
#include "Player.hpp"
#include "Server.hpp"
#include "Position.hpp"
#include "World.hpp"
#include "Ball.hpp"
#include "Vector2D.hpp"
#include "Configs.hpp"
#include "Message.hpp"
#include "Messages.hpp"
#include "Controller.hpp"
#include <fstream>

namespace Phoenix {

/*------------------------
 | Globals               |
 ------------------------*/

bool processing_body = false;
Self* self_ptr = 0;
Game* game_ptr = 0;
World* world_ptr = 0;
Messages* messages_ptr = 0;
static pthread_cond_t sense_body_cond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t sense_body_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t thread_timer = 0;
pthread_t thread_sense_body = 0;
pthread_t thread_fullstate = 0;
pthread_t thread_message = 0;
pthread_t thread_see = 0;
pthread_t thread_see_global = 0;
pthread_attr_t attr;
std::ofstream see_stream;
//std::ofstream hear_stream;
//std::ofstream fs_stream;
//std::ofstream body_stream;

/*------------------------
 | Timers and Control    |
 ------------------------*/

std::vector<Flag> flags;
static std::vector<Player> players;
static std::vector<Player> fs_players;
static Ball ball;
static Ball fs_ball;
std::vector<Message> messages;
std::vector<Message> out_of_cycle;
int time = 0;
bool new_cycle = true;

int wait = 0;

void *timer(void* arg) {
	usleep(1000 * wait);
	if (Controller::AGENT_TYPE == 'p' || Controller::AGENT_TYPE == 'g') {
		self_ptr->localize(flags);
	}
	world_ptr->updateWorld(players, ball, fs_players, fs_ball);
	messages_ptr->setMessages(messages);
	new_cycle = false;
	game_ptr->updateTime(time);
	return 0;
}

/*------------------------
 | Handlers              |
 ------------------------*/

/* sense_body handler */

std::string sense_body;

void *senseBodyHandler(void *arg) {
	if (pthread_mutex_lock(&sense_body_mutex) != 0) {
		std::cerr << "Parser::process_sense_body(void*) -> cannot lock sense body mutex" << std::endl;
		return 0;
	}
	self_ptr->processSenseBody(sense_body);
	processing_body = false;
	if (pthread_cond_signal(&sense_body_cond) != 0) {
		std::cerr << "Parser::process_see(void*) -> cannot signal to blocked threads" << std::endl;
	}
	if (pthread_mutex_unlock(&sense_body_mutex) != 0) {
		std::cerr << "Parser::process_sense_body(void*) -> cannot unlock sense body mutex" << std::endl;
		return 0;
	}
	return 0;
}

/* fullstate handler */

std::string fullstate;
boost::regex fullstate_ball("\\(\\(b\\)\\s+([\\d\\.\\-e]+)\\s+([\\d\\.\\-e]+)\\s+([\\d\\.\\-e]+)\\s+([\\d\\.\\-e]+)\\)");
boost::regex fullstate_player("\\(\\(p\\s+(l|r)\\s+(\\d+)\\s+(g|\\d+)\\)\\s+" //group 1 group 2 group 3
	                          "([\\d\\.\\-e]+)\\s+([\\d\\.\\-e]+)\\s+" //group 4 (x) group 5 (y)
	                          "([\\d\\.\\-e]+)\\s+([\\d\\.\\-e]+)\\s+" //group 6 (vx) group 7 (vy)
	                          "([\\d\\.\\-e]+)\\s+([\\d\\.\\-e]+)\\s+" //group 8 (body) group 9 (neck)
	                          "\\(stamina\\s+([\\d\\.\\-e]+)\\s+([\\d\\.\\-e]+)\\s+" //group 10 (stamina) group 11 (effort)
	                          "([\\d\\.\\-e]+)\\s+([\\d\\.\\-e]+)\\)\\)"); //group 12 (recovery) group 13 (capacity)

void *fullstateHandler(void* arg) {
	std::string::const_iterator start, end;
	start = fullstate.begin();
	end = fullstate.end();
	boost::match_results<std::string::const_iterator> match;
	boost::match_flag_type search_flags = boost::match_default;
	while (boost::regex_search(start, end, match, fullstate_player, search_flags)) {
		std::string side = std::string() + match[1];
		int unum = atoi((std::string() + match[2]).c_str());
		double x = atof((std::string() + match[4]).c_str());
		double y = atof((std::string() + match[5]).c_str());
		double vx = atof((std::string() + match[6]).c_str());
		double vy = atof((std::string() + match[7]).c_str());
		double b = atof((std::string() + match[8]).c_str());
		double n = atof((std::string() + match[9]).c_str());
		Player p;
		p.initForFullstate(side, unum, x, y, vx, vy, b, n);
		fs_players.push_back(p);
		start = match[0].second;
		search_flags |= boost::match_prev_avail;
		search_flags |= boost::match_not_bob;
	}
	start = fullstate.begin();
	end = fullstate.end();
	search_flags = boost::match_default;
	if (boost::regex_search(start, end, match, fullstate_ball, search_flags)) {
		double x = atof((std::string() + match[1]).c_str());
		double y = atof((std::string() + match[2]).c_str());
		double vx = atof((std::string() + match[3]).c_str());
		double vy = atof((std::string() + match[4]).c_str());
		fs_ball.initForFullstate(x, y, vx, vy);
	}
	return 0;
}

/* hear handler */

boost::regex hear_referee_regex("\\(hear\\s+(\\d+)\\s+referee\\s+([\\\"\\w\\s]*)\\)");
boost::regex hear_coach_regex("\\(hear\\s+(\\d+)\\s+(online_coach_left|online_coach_right)\\s+\"([\\w\\s]*)\"\\)"); //coach free form
//boost::regex hear_clang_regex(""); //for coach language, soon
boost::regex hear_trainer_regex("\\(hear\\s+(\\d+)\\s+coach\\s+([\\\"\\w\\s]*)\\)");
boost::regex hear_for_trainer("\\(hear\\s+(\\d+)\\s+\\(p\\s+\"([0-9a-zA-Z]+)\"\\s+(\\d+)\\)\\s+\"([\\w\\s]*)\"\\)");
boost::regex hear_player_regex("\\(hear\\s+(\\d+)\\s+([\\d\\.\\-e]+)\\s+our\\s+(\\d+)\\s+\"([\\w\\s]+)\"\\)");
boost::regex hear_opp_regex("\\(hear\\s+(\\d+)\\s+([\\d\\.\\-e]+)\\s+opp\\s+\"([\\w\\s]+)\"\\)");
std::vector<std::string> hears;

void *hearHandler(void* arg) {
	std::string hear = *((std::string *)arg);
	boost::cmatch match;
	if (boost::regex_match(hear.c_str(), match, hear_referee_regex)) { //from referee to player/trainer
		game_ptr->updatePlayMode(std::string() + match[2]);
	} 
	else if (boost::regex_match(hear.c_str(), match, hear_player_regex)) { //from player to player (same team)
		double direction = atof((std::string() + match[2]).c_str());
		int unum = atoi((std::string() + match[3]).c_str());
		std::string message = std::string() + match[4];
		Message new_message(direction, "our", unum, message);
		if (new_cycle) {
			messages.push_back(new_message);
		} else {
			out_of_cycle.push_back(new_message);
		}
	} 
	else if (boost::regex_match(hear.c_str(), match, hear_coach_regex)) { //from coach to player (free-form)
		std::string coach = std::string() + match[2];
		if (Self::SIDE[0] == coach[13]) {
			std::string msg = std::string() + match[3];
			Message new_message(0.0, "coach", msg);
			if (new_cycle) {
				messages.push_back(new_message);
			} else {
				out_of_cycle.push_back(new_message);
			}
		}
	} 
	else if (boost::regex_match(hear.c_str(), match, hear_trainer_regex)) { //from trainer to player

	}
	else if (boost::regex_match(hear.c_str(), match, hear_for_trainer)) { //from player to trainer
		std::string team = std::string() + match[2];
		int unum = atoi((std::string() + match[3]).c_str());
		std::string msg = std::string() + match[4];
		Message new_message(0.0, team, unum, msg);
		if (new_cycle) {
			messages.push_back(new_message);
		} else {
			out_of_cycle.push_back(new_message);
		}
	}
	else {
		std::cerr << Game::SIMULATION_TIME << ": message not supported " << hear << std::endl;
	}
	return 0;
}

/* see and see_global handlers */

boost::regex see_regex("\\(([^()]+)\\)\\s*([\\d\\.\\-etk\\s]*)");
std::string see;

void *seeHandler(void* arg) {
	if (pthread_mutex_lock(&sense_body_mutex) != 0) {
		std::cerr << "Parser::process_sense_body(void*) -> cannot lock sense body mutex" << std::endl;
		return 0;
	}
	while (processing_body) { //We wait for the sense_body handler to finish
		if (pthread_cond_wait(&sense_body_cond, &sense_body_mutex) != 0) {
			std::cerr << "Parser::process_sense_body(void*) -> cannot wait for condition" << std::endl;
			return 0;
		}
	}
	if (pthread_mutex_unlock(&sense_body_mutex) != 0) {
		std::cerr << "Parser::process_sense_body(void*) -> cannot unlock sense body mutex" << std::endl;
		return 0;
	}
	int simulation_time = Game::SIMULATION_TIME;
	Position player_position = Self::getPosition();
	Vector2D player_velocity = Self::getVelocity();
	std::string::const_iterator start, end;
	start = see.begin();
	end = see.end();
	boost::match_results<std::string::const_iterator> match;
	boost::match_flag_type search_flags = boost::match_default;
	while (boost::regex_search(start, end, match, see_regex, search_flags)) {
		std::string name = std::string() + match[1];
		std::string data = std::string() + match[2];
		switch (name[0]) {
		case 'g': {
			break;
		}
		case 'f': {
			flags.push_back(Flag(name, data, simulation_time));
			break;
		}
		case 'p': {
			Player p;
			p.initForPlayer(name, data, player_position, player_velocity);
			players.push_back(p);
			break;
		}
		case 'b': {
			ball.initForPlayer(data, player_position, player_velocity);
			break;
		}
		default: {
			break;
		}
		}
		start = match[0].second;
		search_flags |= boost::match_prev_avail;
		search_flags |= boost::match_not_bob;
	}
	if (Configs::SAVE_SEE) {
		see_stream << see << std::endl;
	}
	return 0;
}

std::string see_global;

void *seeGlobalHandler(void* arg) {
	int simulation_time = Game::SIMULATION_TIME;
	std::string::const_iterator start, end;
	start = see_global.begin();
	end = see_global.end();
	boost::match_results<std::string::const_iterator> match;
	boost::match_flag_type search_flags = boost::match_default;
	while (boost::regex_search(start, end, match, see_regex, search_flags)) {
		std::string name = std::string() + match[1];
		std::string data = std::string() + match[2];
		switch (name[0]) {
		case 'g': {
			break;
		}
		case 'p': {
			Player p;
			p.initForCoach(name, data);
			players.push_back(p);
			break;
		}
		case 'b': {
			ball.initForCoach(data);
			break;
		}
		default: {
			break;
		}
		}
		start = match[0].second;
		search_flags |= boost::match_prev_avail;
		search_flags |= boost::match_not_bob;
	}
//	world_ptr->updateObserverWorld(players, ball);
//	size_t found = see_global.find(" ", 12);
//	game_ptr->updateTime(atoi(see_global.substr(12, found - 12).c_str()));
	return 0;
}

/*------------------------
 | Class implementation  |
 ------------------------*/

Parser::Parser(Self* self, World* world, Messages* messages_p) {
	self_ptr = self;
	world_ptr = world;
	messages_ptr = messages_p;
	game_ptr = new Game();
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	wait = Configs::CYCLE_OFFSET;
	if (Server::SYNCH_SEE_OFFSET > wait) {
		wait = Server::SYNCH_SEE_OFFSET;
	}
	if (Configs::SAVE_SEE) {
		see_stream.open("see.log");
	}
}

Parser::~Parser() {
	pthread_attr_destroy(&attr);
	if (game_ptr) delete game_ptr;
	if (Configs::VERBOSE) std::cout << "Parser out" << std::endl;
	if (Configs::SAVE_SEE) {
		see_stream.close();
	}
}

void Parser::parseMessage(std::string message) {
	size_t found = message.find_first_of(" ");
	std::string message_type = message.substr(1, found - 1);
	if (message_type.compare("sense_body") == 0) {
		sense_body = message;
		flags.clear();
		players.clear();
		fs_players.clear();
		ball = Ball();
		fs_ball = Ball();
		messages.clear();
		for (std::vector<Message>::iterator it = out_of_cycle.begin(); it != out_of_cycle.end(); ++it) {
			messages.push_back(*it);
		}
		out_of_cycle.clear();
		new_cycle = true;
		found = message.find(" ", 12);
		time = atoi(message.substr(12, found - 12).c_str());
		if (pthread_create(&thread_timer, &attr, timer, 0) != 0) {
			std::cerr << "Parser::parseMessage(string) -> error creating timer thread" << std::endl;
		}
		if (pthread_create(&thread_sense_body, &attr, senseBodyHandler, 0) != 0) {
			std::cerr << "Parser::parseMessage(string) -> error creating sense_body thread" << std::endl;
		}
		return;
	}
	else if (message_type.compare("see_global") == 0) {
		see_global = message;
		players.clear();
		ball = Ball();
		messages.clear();
		for (std::vector<Message>::iterator it = out_of_cycle.begin(); it != out_of_cycle.end(); ++it) {
			messages.push_back(*it);
		}
		out_of_cycle.clear();
		new_cycle = true;
		found = message.find(" ", 12);
		time = atoi(message.substr(12, found - 12).c_str());
		if (pthread_create(&thread_timer, &attr, timer, 0) != 0) {
			std::cerr << "Parser::parseMessage(string) -> error creating timer thread" << std::endl;
		}
		if (pthread_create(&thread_see_global, &attr, seeGlobalHandler, 0) != 0) {
			std::cerr << "Parser::parseMessage(string) -> error creating see_global thread" << std::endl;
		}
		return;
	}
	else if (message_type.compare("hear") == 0) {
		hears.push_back(message);
		if (pthread_create(&thread_message, &attr, hearHandler, &hears.back()) != 0) {
			std::cerr << "Parser::parseMessage(string) -> error creating sense_body thread" << std::endl;
		}
		return;
	}
	else if (message_type.compare("change_player_type") == 0) {
		return;
	}
	else if (message_type.compare("ok") == 0) {
		if (Configs::VERBOSE) std::cout << Game::SIMULATION_TIME << ": " << message << std::endl;
		return;
	}
	else if (message_type.compare("warning") == 0) {
		if (Configs::VERBOSE) std::cout << Game::SIMULATION_TIME << ": " << message << std::endl;
		return;
	}
	else if (message_type.compare("error") == 0) {
		std::cerr << Game::SIMULATION_TIME << ": " << message << std::endl;
		return;
	}
	if (!new_cycle) return; //we do not accept this messages after the new cycle started
	if (message_type.compare("see") == 0) {
		see = message;
		if (pthread_create(&thread_see, &attr, seeHandler, 0) != 0) {
			std::cerr << "Parser::parseMessage(string) -> error creating sense_body thread" << std::endl;
		}
		return;
	}	
	else if (message_type.compare("fullstate") == 0) {
		fullstate = message;
		if (pthread_create(&thread_see, &attr, fullstateHandler, 0) != 0) {
			std::cerr << "Parser::parseMessage(string) -> error creating fullstate thread" << std::endl;
		}
		return;
	}
	else {
		std::cerr << "Parse::parseMessage(string) -> message " << message << " not recognized" << std::endl;
		return;
	}
}

}
