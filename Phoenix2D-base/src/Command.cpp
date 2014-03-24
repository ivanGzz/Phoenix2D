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

#include "Command.h"
#include "Game.h"
#include <iostream>
namespace Phoenix
{
Command::Command() {
	command = "(error)";
	weight = 1;
	type = EMPTY;
	double_arg_0 = 0.0;
	double_arg_1 = 0.0;
	string_arg_0 = "";
	string_arg_1 = "";
	bool_arg_0 = "";
	bool_arg_1 = "";
	status = ERROR;
	simulation_time = 0;
}

Command::Command(std::string command, int weight, COMMAND_TYPE type) { //, void* ... args) {
	this->command = command;
	this->weight = weight;
	this->type = type;
	double_arg_0 = 0.0;
	double_arg_1 = 0.0;
	string_arg_0 = "";
	string_arg_1 = "";
	bool_arg_0 = false;
	bool_arg_1 = false;
	status = CREATED;
	simulation_time = Game::SIMULATION_TIME;
}

Command::~Command() {

}

void Command::setArgs(void* arg0, void* arg1, void* arg2) {
	switch(type) {
	case MOVE:
	case DASH:
	case KICK:
	case POINT:
		if (arg0) double_arg_0 = *((double *)arg0);
		if (arg1) double_arg_1 = *((double *)arg1);
		break;
	case TURN:
	case CATCH:
	case TURN_NECK:
		if (arg0) double_arg_0 = *((double *)arg0);
		break;
	case SAY:
	case CHANGE_VIEW:
		if (arg0) string_arg_0 = *((std::string *)arg0);
		break;
	case TACKLE:
		if (arg0) double_arg_0 = *((double *)arg0);
		if (arg1) bool_arg_1 = *((bool *)arg1);
		break;
	default:
		break;
	}
}

std::string Command::getCommand() {
	return command;
}

int Command::getWeight() {
	return weight;
}

COMMAND_TYPE Command::getCommandType() {
	return type;
}

double Command::getDashPower() {
	return double_arg_0;
}

double Command::getDashDirection() {
	return double_arg_1;
}

double Command::getTurnMoment() {
	return double_arg_0;
}

double Command::getMoveX() {
	return double_arg_0;
}

double Command::getMoveY() {
	return double_arg_1;
}

std::string Command::getSayMessage() {
	return string_arg_0;
}

double Command::getCatchDirection() {
	return double_arg_0;
}

double Command::getKickPower() {
	return double_arg_0;
}

double Command::getKickDirection() {
	return double_arg_1;
}

double Command::getTacklePower() {
	return double_arg_0;
}

bool Command::getTackleWillToFoul() {
	return bool_arg_1;
}

double Command::getTurnNeckMoment() {
	return double_arg_0;
}

double Command::getPointDistance() {
	return double_arg_0;
}

double Command::getPointDirection() {
	return double_arg_1;
}

std::string Command::getChangeViewWidth() {
	return string_arg_0;
}

void Command::changeStatusTo(COMMAND_STATUS status) {
	this->status = status;
}

COMMAND_STATUS Command::getCommandStatus() {
	return status;
}

int Command::createdAt() {
	return simulation_time;
}
}