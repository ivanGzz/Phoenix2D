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

#include <vector>
#include <stack>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "Trainer.h"
#include "Commands.h"
#include "Config.h"
#include "Game.h"
namespace Phoenix
{
std::vector<std::string> code;

enum COMMANDS {
	START,
	DO,
	CHANGE_TO,
	RECOVER,
	END_DO,
	SAY,
	END
};

struct execution_line {
	int address;
	COMMANDS command;
	int accum;
	std::string arg;
	int jump_to;
};

std::vector<execution_line> program;

bool loadCode() {
	std::ifstream file("trainer.phx", std::ifstream::in);
	if (file) {
		std::string line;
		while (std::getline(file, line)) {
			code.push_back(line);
		}
		file.close();
		return true;
	} else {
		std::cerr << "loadCode() -> file trainer.phx does not exist" << std::endl;
		file.close();
		return false;
	}
}

bool generateCode() {
	int address = 0;
	std::stack<int> jumps;
	for (std::vector<std::string>::iterator it = code.begin(); it != code.end(); ++it) {
		size_t found = it->find_first_of(" ");
		if (found != std::string::npos) {
			std::string type = it->substr(0, found);
			std::string args = it->substr(found + 1);
			if (type.compare("do") == 0) {
				execution_line line = {address, DO, atoi(args.c_str()), "", address + 1};
				jumps.push(address + 1);
				program.push_back(line);
				address++;
			} else if (type.compare("wait") == 0) {
				int wait = atoi(args.c_str());
				if (wait > 0) {
					execution_line first_line = {address, DO, wait - 1, "", address + 1};
					program.push_back(first_line);
					address++;
					execution_line second_line = {address, END_DO, 1, "", address};
					program.push_back(second_line);
					address++;
				}
			} else if (type.compare("change_to") == 0) {
				execution_line line = {address, CHANGE_TO, 1, args, address + 1};
				program.push_back(line);
				address++;
			} else if (type.compare("say") == 0) {
				execution_line line = {address, SAY, 1, args, address + 1};
				program.push_back(line);
				address++;
			}
		} else {
			if ((*it).compare("recover") == 0) {
				execution_line line = {address, RECOVER, 1, "", address + 1};
				program.push_back(line);
				address++;
			} else if ((*it).compare("end_do") == 0) {
				execution_line line = {address, END_DO, 1, "", jumps.top()};
				jumps.pop();
				program.push_back(line);
				address++;
			}
		}
	}
	if (jumps.size() > 0) {
		std::cerr << "generateCode() -> " << jumps.size() << " loops unclosed" << std::endl;
		return false;
	}
	execution_line line = {address, END, 1, "time_over", address + 1};
	program.push_back(line);
	return true;
}

int current_line = 0;
std::stack<int> accums;

Trainer::Trainer(Commands *commands) {
	this->commands = commands;
	if (loadCode()) {
		newExecution = true;
		if (!generateCode()) {
			newExecution = false;
		}
	} else {
		newExecution = false;
	}
}

Trainer::~Trainer() {

}

void Trainer::execute(WorldModel world) {
	if (Config::TRAINER_LOGGING && Game::PLAY_MODE.compare("play_on") == 0) {
		std::list<Player*> players = world.getPlayers();
		std::clog << Game::GAME_TIME;
		for (std::list<Player*>::iterator it = players.begin(); it != players.end(); ++it) {
			std::clog << " - " << (*it)->getTeam() << "(" << (*it)->getUniformNumber() << "): [" << ((*it)->getPosition()).toString() << "," << ((*it)->getVelocity()).toString() << "]";
		}
		std::clog << std::endl;
		std::clog.flush();
	}
	execution_line line = program.at(current_line);
	switch (line.command) {
	case START:
		break;
	case DO:
		accums.push(line.accum);
		current_line = line.jump_to;
		break;
	case CHANGE_TO:
		commands->changeMode(line.arg);
		Game::PLAY_MODE = line.arg;
		current_line = line.jump_to;
		break;
	case RECOVER:
		commands->recover();
		current_line = line.jump_to;
		break;
	case END_DO:
		accums.top()--;
		if (accums.top() > 0) {
			current_line = line.jump_to;
		} else {
			accums.pop();
			current_line++;
		}
		break;
	case SAY:
		commands->say(line.arg);
		current_line = line.jump_to;
		break;
	case END:
		commands->changeMode(line.arg);
		newExecution = false;
		break;
	}
	commands->sendCommands();
}

bool Trainer::continueExecution() {
	return newExecution;
}
}