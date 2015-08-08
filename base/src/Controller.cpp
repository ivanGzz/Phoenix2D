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
 * @file Controller.cpp
 *
 * @author Nelson I. Gonzalez
 */

#include "Controller.hpp"
#include <boost/regex.hpp>
#include <iostream>
#include <cstdlib>
#include "Connect.hpp"
#include "Self.hpp"
#include "Reader.hpp"
#include "Server.hpp"
#include "Parser.hpp"
#include "Commands.hpp"
#include "PlayMode.hpp"
#include "World.hpp"
#include "Messages.hpp"
#include "Message.hpp"
#include "Game.hpp"
#include <map>
#include "Configs.hpp"
#include "Logger.hpp"
#include "Trainer.cpp"

namespace Phoenix {

namespace Controller {

std::map<std::string, execute> player;
std::map<std::string, execute> goalie;
std::map<std::string, execute> coach;
std::string script = "";
control setup;
control finish;

void connect(std::string tema_name, std::string hostname) {
	std::string message = "(init " + team_name + " (version 15.1)";
	int port = 6000;
	switch (AGENT_TYPE) {
	case 'g':
		message = message + " (goalie))";
		break;
	case 't':
		message = "(init (version 15.1))";
		port = 6001;
		break;
	case 'c':
		message = message + ")";
		port = 6002;
		break;
	default:
		message = message + ")";
		break;
	}
	boost::regex error("\\(error\\s+([\\w\\_]+)\\)"); //i.e (error no_more_team_or_player_or_goalie)
	boost::cmatch match;
	Connect::connect(hostname, port);
	Connect::sendMessage(message);
	message = Connect::receiveMessage();
	if (boost::regex_match(message.c_str(), match, error)) {
		std::cerr << "Controller::connect() -> " << match[1] << std::endl; //Error
		return;
	} else {
		boost::regex player_response("\\(init\\s+(l|r)\\s+(\\d+)\\s+([\\w\\_]+)\\)"); //i.e (init l 1 before_kick_off)
		boost::regex coach_response("\\(init\\s+(l|r)\\s+ok\\)");
		std::string side;
		int unum = 0;
		switch (AGENT_TYPE) {
		case 't':
			side = "trainer";
			break;
		case 'c':
			unum = 0;
			if (boost::regex_match(message.c_str(), match, coach_response)) {
				side = match[1];
			} else {
				side = "undefined";
				std::cerr << "Controller::connect() -> Does not match response for coach" << std::endl;
			}
			break;
		default:
			if (boost::regex_match(message.c_str(), match, player_response)) {
				side = match[1];
				unum = atoi((std::string() + match[2]).c_str()); //C++11: use std::stoi()
			} else {
				side = "undefined";
				unum = 0;
				std::cerr << "Controller::connect() -> Does not match response for player" << std::endl;
			}
			break;
		}
		message = Connect::receiveMessage(); //server_params
		Server::parseServerParams(message);
		Self::TEAM_NAME = team_name;
		Self::UNIFORM_NUMBER = unum;
		Self::SIDE = side;
		message = Connect::receiveMessage(); //player_params
		Self::parsePlayerParams(message);
		// We need to load the team configs before all the objects are created, and after the Self object is
		// created since it needs the Self object
		/*if (Controller::AGENT_TYPE == 'p' || Controller::AGENT_TYPE == 'g') {
			Configs::loadTeam("");
		}*/
		for (int i = 0; i < Self::PLAYER_TYPES; i++) {
			message = Connect::receiveMessage(); //player_type
			Self::addPlayerType(message);
		}
		switch (Controller::AGENT_TYPE) {
		case 'p':
			//A player use synchronized view as default
			Connect::sendMessage("(synch_see)");
			break;
		case 'g':
			Connect::sendMessage("(synch_see)");
			break;
		case 'c':
			//The coaches receive visual information every cycle
			Connect::sendMessage("(eye on)");
			break;
		default:
			Connect::sendMessage("(eye on)");
			Connect::sendMessage("(ear on)");
			break;
		}
		Parser::init();
		Reader::start();
		connected = true;
	}
}

bool isConnected() {
	return connected;
}

void registerSetupFunction(control function) {
	setup = function;
}

void registerFinishFunction(control function) {
	finish = function;
}

void registerPlayerFunction(std::string play_mode, execute function) {
	player.insert(std::make_pair(play_mode, function));
}

void registerGoalieFunction(std::string play_mode, execute function) {
	goalie.insert(std::make_pair(play_mode, function));
}

void registerCoachFunction(std::string play_mode, execute function) {
	coach.insert(std::make_pair(play_mode, function));
}

void registerTrainerScript(std::string trainer) {
	script = trainer;
}

void run() {
	if (!connected) {
		std::cerr << "Controller::run() -> must connect before run" << std::endl;
		return;
	}
	if (AGENT_TYPE == 't') {
		Trainer trainer(_commands);
		if (trainer.load(script)) {
			while (Game::nextCycle() && trainer.continueExecution()) {
				trainer.execute(_world->getWorldModel(), _messages->getMessages());
			}
		}
	} else {
		Logger log;
		if (Configs::LOGGING) log.log();
		PlayMode play_mode(_commands);
		std::string current_play_mode = "launching";
		std::map<std::string, execute>* ai;
		switch (Controller::AGENT_TYPE) {
		case 'p':
			ai = &player;
			break;
		case 'g':
			ai = &goalie;
			break;
		case 'c':
			ai = &coach;
			break;
		default:
			ai = &player;
			break;
		}
		play_mode.onStart(setup);
		while (Game::nextCycle()) {
			if (current_play_mode.compare(Game::PLAY_MODE) != 0) {
				current_play_mode = Game::PLAY_MODE;
			}
			play_mode.onPreExecute();
			std::map<std::string, execute>::iterator it = ai->find(current_play_mode);
			if (it != ai->end()) {
				play_mode.onExecute(World::getWorldModel(), Messages::getMessages(), it->second);
			} else {
				std::cerr << "Controller::run(): " << current_play_mode << " handler not found" << std::endl;
			}
			play_mode.onPostExecute();
		}
		play_mode.onEnd(finish);
	}
}

void reconnect() {

}

void disconnect() {
	if (isConnected()) {
		Reader::stop();
	}
	connected = false;
}

}

}
