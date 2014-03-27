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
#include <sstream>
#include <iomanip>
#include <list>
#include "Commands.h"
#include "Command.h"
#include "Connect.h"
#include "Self.h"
#include "Server.h"
#include "Config.h"
#include "Game.h"
namespace Phoenix
{
Connect* commands_connect_ptr = 0;
std::list<Command> commands_history;
std::list<Command*> commands_to_send;

Commands::Commands(Connect *connect) {
	commands_connect_ptr = connect;
}

Commands::~Commands() {
	if (Config::VERBOSE) std::cout << "Commands out" << std::endl;
}

void Commands::flush() {
	while (commands_history.size() > 0 && Game::SIMULATION_TIME - commands_history.front().createdAt() > Config::COMMANDS_MAX_HISTORY) {
		commands_history.pop_front();
	}
}

void Commands::move(double x, double y) {
	std::stringstream ss;
	ss << "(move " << std::setprecision(4) << x << " " << y << ")" << std::endl;
	std::string command;
	std::getline(ss, command);
	commands_history.push_back(Command(command, 1, MOVE));
	commands_history.back().setArgs((void *)&x, (void *)&y);
	commands_to_send.push_back(&commands_history.back());
}

void Commands::turn(double moment) {
	if (moment < Server::MINMOMENT) {
		moment = Server::MINMOMENT;
	} else if (moment > Server::MAXMOMENT) {
		moment = Server::MAXMOMENT;
	}
	std::stringstream ss;
	ss << "(turn " << std::setprecision(4) << moment << ")" << std::endl;
	std::string command;
	std::getline(ss, command);
	commands_history.push_back(Command(command, 1, TURN));
	commands_history.back().setArgs((void *)&moment);
	commands_to_send.push_back(&commands_history.back());
}

void Commands::turnNeck(double moment) {
	if (moment < Server::MINMOMENT) {
		moment = Server::MINMOMENT;
	} else if (moment > Server::MAXMOMENT) {
		moment = Server::MAXMOMENT;
	}
	std::stringstream ss;
	ss << "(turn_neck " << std::setprecision(4) << moment << ")" << std::endl;
	std::string command;
	std::getline(ss, command);
	commands_history.push_back(Command(command, 1, TURN_NECK));
	commands_history.back().setArgs((void *)&moment);
	commands_to_send.push_back(&commands_history.back());
}

void Commands::dash(double power, double direction) {
	if (power > Server::MAXPOWER) {
		power = Server::MAXPOWER;
	} else if (power < Server::MINPOWER) {
		power = Server::MINPOWER;
	}
	if (direction > Server::MAXMOMENT) {
		direction = Server::MAXMOMENT;
	} else if (direction < Server::MINMOMENT) {
		direction = Server::MINMOMENT;
	}
	std::stringstream ss;
	ss << "(dash " << std::setprecision(4) << power << " " << direction << ")" << std::endl;
	std::string command;
	std::getline(ss, command);
	commands_history.push_back(Command(command, 1, DASH));
	commands_history.back().setArgs((void *)&power, (void *)&direction);
	commands_to_send.push_back(&commands_history.back());
}

void Commands::say(std::string message) {
	std::string command = "(say " + message + ")";
	commands_history.push_back(Command(command, 1, SAY));
	commands_history.back().setArgs((void *)&message);
	commands_to_send.push_back(&commands_history.back());
}

void Commands::catchBall(double direction) {
	std::stringstream ss;
	ss << "(catch " << std::setprecision(4) << direction << ")" << std::endl;
	std::string command;
	std::getline(ss, command);
	commands_history.push_back(Command(command, 1, CATCH));
	commands_history.back().setArgs((void *)&direction);
	commands_to_send.push_back(&commands_history.back());
}

void Commands::kick(double power, double direction) {
	std::stringstream ss;
	ss << "(kick " << std::setprecision(4) << power << " " << direction << ")" << std::endl;
	std::string command;
	std::getline(ss, command);
	commands_history.push_back(Command(command, 1, KICK));
	commands_history.back().setArgs((void *)&power, (void *)&direction);
	commands_to_send.push_back(&commands_history.back());
}

void Commands::tackle(double power, bool willToFoul) {
	std::stringstream ss;
	ss << "(tackle " << std::setprecision(4) << power << (willToFoul ? " true" : " false") << std::endl;
	std::string command;
	std::getline(ss, command);
	commands_history.push_back(Command(command, 1, TACKLE));
	commands_history.back().setArgs((void *)&power, (void *)&willToFoul);
	commands_to_send.push_back(&commands_history.back());
}

void Commands::pointTo(double distance, double direction) {
	std::stringstream ss;
	ss << "(pointto " << std::setprecision(4) << distance << " " << direction << ")" << std::endl;
	std::string command;
	std::getline(ss, command);
	commands_history.push_back(Command(command, 1, POINT));
	commands_history.back().setArgs((void *)&distance, (void *)&direction);
	commands_to_send.push_back(&commands_history.back());
}

void Commands::changeView(std::string width) {
	std::string command = "(change_view " + width + ")";
	commands_history.push_back(Command(command, 1, CHANGE_VIEW));
	commands_history.back().setArgs((void *)&width);
	commands_to_send.push_back(&commands_history.back());
}

void Commands::moveObject(std::string object, double x, double y) {
	std::stringstream ss;
	ss << "(move " << object << " " << std::setprecision(4) << x << " " << y << ")" << std::endl;
	std::string command;
	std::getline(ss, command);
	commands_history.push_back(Command(command, 1, MOVE_OBJECT));
	commands_to_send.push_back(&commands_history.back());
}

void Commands::changeMode(std::string mode) {
	std::string command = "(change_mode " + mode + ")";
	commands_history.push_back(Command(command, 1, CHANGE_MODE));
	commands_history.back().setArgs((void *)&mode);
	commands_to_send.push_back(&commands_history.back());
}

void Commands::start() {
	std::string command = "(start)";
	commands_history.push_back(Command(command, 1, START));
	commands_to_send.push_back(&commands_history.back());
}

void Commands::recover() {
	std::string command = "(recover)";
	commands_history.push_back(Command(command, 1, RECOVER));
	commands_to_send.push_back(&commands_history.back());
}

int Commands::sendCommands() {
	int commands_sent_counter = 0;
	std::list<Command*> commands_sent;
	if (commands_to_send.size() > 0) {
		std::string message = "";
		int weight = 0;
		do {
			Command* command_to_send = commands_to_send.front();
			weight += command_to_send->getWeight();
			if (weight < 2) {
				command_to_send->changeStatusTo(SENT);
				message += command_to_send->getCommand();
				commands_sent.push_back(command_to_send);
				commands_to_send.pop_front();
				commands_sent_counter++;
			}
		} while (weight < 2 && commands_to_send.size() > 0);
		commands_connect_ptr->sendMessage(message);
	}
	commands_to_send.clear(); //we clear the commands to send queue
	Self::setLastCommandsSet(commands_sent);
	return commands_sent_counter;
}
}