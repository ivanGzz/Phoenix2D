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
 * @file PlayMode.cpp
 *
 * @author Nelson Ivan Gonzalez
 */

#include "PlayMode.hpp"
#include "Commands.hpp"
#include "Parser.hpp"

namespace Phoenix {

PlayMode::PlayMode(Commands *commands) {
	this->commands = commands;
}

PlayMode::~PlayMode() {

}

void PlayMode::onStart(void(* setup)(void)) {
	setup();
}

void PlayMode::onExecute(WorldModel world, std::vector<Message> messages, void(* execute)(WorldModel, std::vector<Message>, Commands*)) {
	execute(world, messages, commands);
}

void PlayMode::onPreExecute() {
	commands->flush();
}

void PlayMode::onPostExecute() {
	commands->sendCommands();
}

void PlayMode::onEnd(void(* end)(void)) {
	end();
}

}
