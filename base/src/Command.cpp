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
 * @file Command.cpp
 *
 * @author Nelson I. Gonzalez
 */

#include "Command.hpp"
#include "Game.hpp"
#include <iostream>

namespace Phoenix {

Command::Command() {
	_command = "(error)";
	_weight = 1;
	_type = EMPTY;
	_double_arg_0 = 0.0;
	_double_arg_1 = 0.0;
	_string_arg_0 = "";
	_string_arg_1 = "";
	_bool_arg_0 = "";
	_bool_arg_1 = "";
	_status = ERROR;
	_simulation_time = 0;
}

Command::Command(std::string command, int weight, COMMAND_TYPE type) {
	_command = command;
	_weight = weight;
	_type = type;
	_double_arg_0 = 0.0;
	_double_arg_1 = 0.0;
	_string_arg_0 = "";
	_string_arg_1 = "";
	_bool_arg_0 = false;
	_bool_arg_1 = false;
	_status = CREATED;
	_simulation_time = Game::SIMULATION_TIME;
}

Command::Command(std::string command, int weight, COMMAND_TYPE type, double arg0) {
	_command = command;
	_weight = weight;
	_type = type;
	_double_arg_0 = arg0;
	_double_arg_1 = 0.0;
	_string_arg_0 = "";
	_string_arg_1 = "";
	_bool_arg_0 = false;
	_bool_arg_1 = false;
	_status = CREATED;
	_simulation_time = Game::SIMULATION_TIME;
}

Command::Command(std::string command, int weight, COMMAND_TYPE type, double arg0, double arg1) {
	_command = command;
	_weight = weight;
	_type = type;
	_double_arg_0 = arg0;
	_double_arg_1 = arg1;
	_string_arg_0 = "";
	_string_arg_1 = "";
	_bool_arg_0 = false;
	_bool_arg_1 = false;
	_status = CREATED;
	_simulation_time = Game::SIMULATION_TIME;
}

Command::Command(std::string command, int weight, COMMAND_TYPE type, std::string arg0) {
	_command = command;
	_weight = weight;
	_type = type;
	_double_arg_0 = 0.0;
	_double_arg_1 = 0.0;
	_string_arg_0 = arg0;
	_string_arg_1 = "";
	_bool_arg_0 = false;
	_bool_arg_1 = false;
	_status = CREATED;
	_simulation_time = Game::SIMULATION_TIME;
}

Command::Command(std::string command, int weight, COMMAND_TYPE type, std::string arg0) {
	_command = command;
	_weight = weight;
	_type = type;
	_double_arg_0 = 0.0;
	_double_arg_1 = 0.0;
	_string_arg_0 = arg0;
	_string_arg_1 = "";
	_bool_arg_0 = false;
	_bool_arg_1 = false;
	_status = CREATED;
	_simulation_time = Game::SIMULATION_TIME;
}

Command::Command(std::string command, int weight, COMMAND_TYPE type, double arg0, bool arg1) {
	_command = command;
	_weight = weight;
	_type = type;
	_double_arg_0 = arg0;
	_double_arg_1 = 0.0;
	_string_arg_0 = "";
	_string_arg_1 = "";
	_bool_arg_0 = arg1;
	_bool_arg_1 = false;
	_status = CREATED;
	_simulation_time = Game::SIMULATION_TIME;
}

Command::~Command() {

}

std::string Command::command() {
	return _command;
}

int Command::weight() {
	return _weight;
}

COMMAND_TYPE Command::commandType() {
	return _type;
}

double Command::dashPower() {
	return _double_arg_0;
}

double Command::dashDirection() {
	return _double_arg_1;
}

double Command::turnMoment() {
	return _double_arg_0;
}

double Command::moveX() {
	return _double_arg_0;
}

double Command::moveY() {
	return _double_arg_1;
}

std::string Command::sayMessage() {
	return _string_arg_0;
}

double Command::catchDirection() {
	return _double_arg_0;
}

double Command::kickPower() {
	return _double_arg_0;
}

double Command::kickDirection() {
	return _double_arg_1;
}

double Command::tacklePower() {
	return _double_arg_0;
}

bool Command::tackleWillToFoul() {
	return _bool_arg_1;
}

double Command::turnNeckMoment() {
	return _double_arg_0;
}

double Command::pointDistance() {
	return _double_arg_0;
}

double Command::pointDirection() {
	return _double_arg_1;
}

std::string Command::changeViewWidth() {
	return _string_arg_0;
}

void Command::setStatus(COMMAND_STATUS status) {
	_status = status;
}

COMMAND_STATUS Command::status() {
	return _status;
}

int Command::createdAt() {
	return _simulation_time;
}

}
