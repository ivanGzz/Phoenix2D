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
 * @file Trainer.cpp
 *
 * @author Nelson Ivan Gonzalez
 */

#include <vector>
#include <stack>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "Trainer.hpp"
#include "Commands.hpp"
#include "Game.hpp"

namespace Phoenix {

std::vector<std::string> code;

enum COMMANDS {
	START,
	DO,
	WAIT_FOR,
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
	bool wait;
};

std::vector<execution_line> program;

bool loadCode(std::string trainer) {
	std::ifstream file(trainer.c_str(), std::ifstream::in);
	if (file) {
		std::string line;
		while (std::getline(file, line)) {
			code.push_back(line);
		}
		file.close();
		return true;
	} else {
		std::cerr << "loadCode() -> file " << trainer << " does not exist" << std::endl;
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
				execution_line line = {address, DO, atoi(args.c_str()), "", address + 1, false};
				jumps.push(address + 1);
				program.push_back(line);
				address++;
			} else if (type.compare("wait") == 0) {
				int wait = atoi(args.c_str());
				if (wait > 0) {
					execution_line first_line = {address, DO, wait, "", address + 1, false};
					program.push_back(first_line);
					address++;
					execution_line second_line = {address, END_DO, 1, "", address, true};
					program.push_back(second_line);
					address++;
				}
			} else if (type.compare("change_to") == 0) {
				execution_line line = {address, CHANGE_TO, 1, args, address + 1, true};
				program.push_back(line);
				address++;
			} else if (type.compare("say") == 0) {
				execution_line line = {address, SAY, 1, args, address + 1, true};
				program.push_back(line);
				address++;
			} else if (type.compare("wait_for_msg") == 0) {
				execution_line line = {address, WAIT_FOR, 1, args, address + 1, true};
				program.push_back(line);
				address++;
			}
		} else {
			if ((*it).compare("recover") == 0) {
				execution_line line = {address, RECOVER, 1, "", address + 1, true};
				program.push_back(line);
				address++;
			} else if ((*it).compare("end_do") == 0) {
				execution_line line = {address, END_DO, 1, "", jumps.top(), false};
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
	execution_line line = {address, END, 1, "time_over", address + 1, true};
	program.push_back(line);
	return true;
}

int current_line = 0;
std::stack<int> accums;

Trainer::Trainer(Commands *commands) {
	this->commands = commands;
	newExecution = false;
}

Trainer::~Trainer() {

}

bool Trainer::load(std::string trainer) {
	if (loadCode(trainer)) {
		newExecution = true;
		if (!generateCode()) {
			newExecution = false;
			return false;
		}
	} else {
		newExecution = false;
		return false;
	}
	return true;
}

void Trainer::execute(WorldModel world, std::vector<Message> messages) {
	bool continuation = true;
	while (continuation) {
		execution_line line = program.at(current_line);
		continuation = !line.wait;
		switch (line.command) {
		case START:
			break;
		case DO:
			accums.push(line.accum);
			current_line = line.jump_to;
			break;
		case CHANGE_TO:
			std::cout << "Changing to: " << line.arg << std::endl;
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
		case WAIT_FOR:
			continuation = false;
			for (std::vector<Message>::iterator it = messages.begin(); it != messages.end(); ++it) {
				if (it->getMessage().compare(line.arg) == 0) {
					continuation = true;
					current_line = line.jump_to;
				}
			}
			break;
		}
	};
	commands->sendCommands();
}

bool Trainer::continueExecution() {
	return newExecution;
}

}
