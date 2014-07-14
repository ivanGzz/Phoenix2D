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
 * @file Controller.cpp
 *
 * @author Nelson Ivan Gonzalez
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

std::map<std::string, execute> player;
std::map<std::string, execute> goalie;
std::map<std::string, execute> coach;
std::string script = "";
control setup;
control finish;

static World* _world = 0;
static Commands* _commands = 0;
static Reader* _reader = 0;
static Parser* _parser = 0;
static Messages* _messages = 0;
static Self* _self = 0;
static Server* _server = 0;
static Connect* _connect = 0;
std::string team_name = "";

char Controller::AGENT_TYPE = 'p';

Controller::Controller(const char *teamName, char agentType, const char *hostname) {
	this->hostname = std::string(hostname);
	Controller::AGENT_TYPE = agentType;
	team_name = std::string(teamName);
	connected = false;
}

Controller::~Controller() {
	if (_world)    delete _world;
	if (_commands) delete _commands;
	if (_reader)   delete _reader;
	if (_parser)   delete _parser;
	if (_messages) delete _messages;
	if (_self)     delete _self;
	if (_server)   delete _server;
	if (_connect)  delete _connect;
}

void Controller::connect() {
	std::string message = "(init " + team_name + " (version 15.1)";
	int port = 6000;
	switch (Controller::AGENT_TYPE) {
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
	_connect = new Connect(hostname.c_str(), port);
	_connect->sendMessage(message);
	message = _connect->receiveMessage();
	if (boost::regex_match(message.c_str(), match, error)) {
		std::cerr << "Controller::connect() -> " << match[1] << std::endl; //Error
		return;
	} else {
		boost::regex player_response("\\(init\\s+(l|r)\\s+(\\d+)\\s+([\\w\\_]+)\\)"); //i.e (init l 1 before_kick_off)
		boost::regex coach_response("\\(init\\s+(l|r)\\s+ok\\)");
		std::string side;
		int unum = 0;
		switch (Controller::AGENT_TYPE) {
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
		message = _connect->receiveMessage(); //server_params
		_server = new Server(message);
		message = _connect->receiveMessage(); //player_params
		_self = new Self(message, team_name, unum, side);
		for (int i = 0; i < Self::PLAYER_TYPES; i++) {
			message = _connect->receiveMessage(); //player_type
			_self->addPlayerType(message);
		}
		switch (Controller::AGENT_TYPE) {
		case 'p':
			//A player use synchronized view as default
			_connect->sendMessage("(synch_see)");
			break;
		case 'g':
			_connect->sendMessage("(synch_see)");
			break;
		case 'c':
			//The coaches receive visual information every cycle
			_connect->sendMessage("(eye on)");
			break;
		default:
			_connect->sendMessage("(eye on)");
			_connect->sendMessage("(ear on)");
			break;
		}
		_world = new World();
		_messages = new Messages();
		_parser = new Parser(_self, _world, _messages);
		_reader = new Reader(_connect, _parser);
		_reader->start();
		connected = true;
	}
}

bool Controller::isConnected() {
	return connected;
}

void Controller::registerSetupFunction(control function) {
	setup = function;
}

void Controller::registerFinishFunction(control function) {
	finish = function;
}

void Controller::registerPlayerFunction(std::string play_mode, execute function) {
	player.insert(std::make_pair(play_mode, function));
}

void Controller::registerGoalieFunction(std::string play_mode, execute function) {
	goalie.insert(std::make_pair(play_mode, function));
}

void Controller::registerCoachFunction(std::string play_mode, execute function) {
	coach.insert(std::make_pair(play_mode, function));
}

void Controller::registerTrainerScript(std::string trainer) {
	script = trainer;
}

void Controller::run() {
	if (!connected) {
		std::cerr << "Controller::run() -> must connect before run" << std::endl;
		return;
	}
	_commands = new Commands(_connect);
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
				play_mode.onExecute(_world->getWorldModel(), _messages->getMessages(), it->second);
			} else {
				std::cerr << "Controller::run(): " << current_play_mode << " handler not found" << std::endl;
			}
			play_mode.onPostExecute();
		}
		play_mode.onEnd(finish);
	}
}

void Controller::reconnect() {

}

void Controller::disconnect() {
	if (isConnected()) {
		_reader->stop();
	}
	connected = false;
}

}
