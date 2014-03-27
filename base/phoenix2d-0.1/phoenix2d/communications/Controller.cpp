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

#include "Controller.h"
#include <boost/regex.hpp>
#include <iostream>
#include <cstdlib>
#include "Connect.h"
#include "Self.h"
#include "Reader.h"
#include "Server.h"
#include "Parser.h"
#include "Commands.h"
#include "World.h"
namespace Phoenix
{
char Controller::AGENT_TYPE = 'p';

Controller::Controller(const char *teamName, char agentType, const char *hostname) {
	this->hostname = std::string(hostname);
	Controller::AGENT_TYPE = agentType;
	team_name = std::string(teamName);
	connected = false;
	c = 0;
	reader = 0;
	server = 0;
	commands = 0;
	world = 0;
	self = 0;
	parser = 0;
}

Controller::~Controller() {
	if (world) delete world;
	if (commands) delete commands;
	if (reader) delete reader;
	if (parser) delete parser;
	if (self) delete self;
	if (server) delete server;
	if (c) delete c;
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
	c = new Connect(hostname.c_str(), port);
	c->sendMessage(message);
	message = c->receiveMessage();
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
		case 'c': //Especial case, we need to consider the regex for this case
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
		message = c->receiveMessage(); //server_params
		server = new Server(message);
		message = c->receiveMessage(); //player_params
		self = new Self(message, team_name, unum, side);
		for (int i = 0; i < Self::PLAYER_TYPES; i++) {
			message = c->receiveMessage(); //player_type
			self->addPlayerType(message);
		}
		switch (Controller::AGENT_TYPE) {
		case 'p':
			c->sendMessage("(synch_see)");
			break;
		case 'g':
			c->sendMessage("(synch_see)");
			break;
		case 'c':
			c->sendMessage("(eye on)");
			break;
		default:
			c->sendMessage("(eye on)");
			break;
		}
		world = new World();
		parser = new Parser(self, world);
		reader = new Reader(c, parser);
		reader->start();
		connected = true;
	}
}

bool Controller::isConnected() {
	return connected;
}

void Controller::reconnect() {

}

void Controller::disconnect() {
	if (isConnected()) {
		reader->stop();
	}
	connected = false;
}

Commands* Controller::getCommands() {
	if (!commands) {
		commands = new Commands(c);
	}
	return commands;
}

World* Controller::getWorld() {
	return world;
}

Self* Controller::getSelf() {
	return self;
}
}