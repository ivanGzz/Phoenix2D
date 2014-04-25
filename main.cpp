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
#include <map>
#include "Controller.h"
#include "Game.h"
#include "Commands.h"
#include "Actions.h"
#include "BeforeKickOff.h"
#include "CornerKickL.h"
#include "CornerKickR.h"
#include "FreeKickL.h"
#include "FreeKickR.h"
#include "GoalKickL.h"
#include "GoalKickR.h"
#include "KickInL.h"
#include "KickInR.h"
#include "KickOffL.h"
#include "KickOffR.h"
#include "PlayOn.h"
#include "PlayMode.h"
#include "World.h"
#include "Trainer.h"
#include "Self.h"
#include "Config.h"
#include "Logger.h"

void printHelp();

int main(int argc, char **argv) {
	Phoenix::Config config;
	const char *team_name, *hostname;
	char agent_type;
	team_name = "Phoenix2D";
	agent_type = 'p';
	hostname = "localhost";
	switch (argc) {
	case 0:
		break;
	case 1:
		printHelp();
		std::cout << "Using <TEAM_NAME> = \"Phoenix2D\"" << std::endl;
		std::cout << "Using <AGENT_TYPE> = \"p\"" << std::endl;
		std::cout << "Using <HOSTNAME> = \"localhost\"" << std::endl;
		break;
	case 2:
		team_name = argv[1];
		printHelp();
		std::cout << "Using <AGENT_TYPE> = \"p\"" << std::endl;
		std::cout << "Using <HOSTNAME> = \"localhost\"" << std::endl;
		break;
	case 3:
		team_name = argv[1];
		agent_type = argv[2][0];
		printHelp();
		std::cout << "Using <HOSTNAME> = \"localhost\"" << std::endl;
		break;
	default:
		team_name = argv[1];
		agent_type = argv[2][0];
		hostname = argv[3];
		break;
	}
	Phoenix::Controller controller(team_name, agent_type, hostname);
	controller.connect();
	if (controller.isConnected()) {
		Phoenix::Commands* commands = controller.getCommands();
		Phoenix::World* world = controller.getWorld();
		std::map<std::string, Phoenix::PlayMode*> play_modes;
		if (Phoenix::Controller::AGENT_TYPE == 't') {
			std::cout << "Trainer launched" << std::endl;
			Phoenix::Logger logger;
			if (Phoenix::Config::TRAINER_LOGGING) logger.log();
			Phoenix::Trainer trainer(commands);
			while (Phoenix::Game::nextCycle() && trainer.continueExecution()) {
				trainer.execute(world->getWorldModel());
			}
			std::cout << "Trainer out" << std::endl;
		} else {
			config.load();
			if (Phoenix::Config::VERBOSE) std::cout << "Agent launched" << std::endl;
			Phoenix::Logger logger;
			if (Phoenix::Config::LOGGING) logger.log();
			Phoenix::Actions actions(commands);
			play_modes["before_kick_off"] = new Phoenix::BeforeKickOff(commands);
			play_modes["corner_kick_l"]   = new Phoenix::CornerKickL(commands);
			play_modes["corner_kick_r"]   = new Phoenix::CornerKickR(commands);
			play_modes["free_kick_l"]     = new Phoenix::FreeKickL(commands);
			play_modes["free_kick_r"]     = new Phoenix::FreeKickR(commands);
			play_modes["goal_kick_l"]     = new Phoenix::GoalKickL(commands);
			play_modes["goal_kick_r"]     = new Phoenix::GoalKickR(commands);
			play_modes["kick_in_l"]       = new Phoenix::KickInL(commands);
			play_modes["kick_in_r"]       = new Phoenix::KickInR(commands);
			play_modes["kick_off_l"]      = new Phoenix::KickOffL(commands);
			play_modes["kick_off_r"]      = new Phoenix::KickOffR(commands);
			play_modes["play_on"]         = new Phoenix::PlayOn(commands, &actions);
			std::string current_play_mode = "launching";
			while (Phoenix::Game::nextCycle()) {
				if (current_play_mode.compare(Phoenix::Game::PLAY_MODE) != 0) {
					current_play_mode = Phoenix::Game::PLAY_MODE;
					play_modes[current_play_mode]->onStart();
					play_modes[current_play_mode]->onPreExecute();
					play_modes[current_play_mode]->setup(world->getWorldModel());
				} else {
					play_modes[current_play_mode]->onPreExecute();
					switch (Phoenix::Controller::AGENT_TYPE) {
					case 'p':
						play_modes[current_play_mode]->onPlayerExecute(world->getWorldModel());
						break;
					case 'g':
						play_modes[current_play_mode]->onGoalieExecute(world->getWorldModel());
						break;
					case 'c':
						play_modes[current_play_mode]->onCoachExecute(world->getWorldModel());
						break;
					default:
						break;
					}
				}
				play_modes[current_play_mode]->onPostExecute();
//				if (Config::VERBOSE) {
//
//				}
			}
			//This must be always called in order to avoid memory leaks
			for (std::map<std::string, Phoenix::PlayMode*>::iterator it = play_modes.begin(); it != play_modes.end(); ++it) {
				delete it->second;
			}
			if (Phoenix::Config::VERBOSE) std::cout << "Agent out" << std::endl;
		}
		controller.disconnect();
	}
	if (Phoenix::Config::VERBOSE) std::cout << "Finish" << std::endl;
	return 0;
}

void printHelp() {
	std::cout << "--- Phoenix2D 2013 ---" << std::endl << std::endl;
	std::cout << "Syntax:" << std::endl;
	std::cout << "\t./Phoenix2D-CPP <TEAM_NAME = \"Phoenix2D\"> <AGENT_TYPE = \"p\"> <HOSTNAME = \"localhost\">" << std::endl;
	std::cout << "Where:" << std::endl;
	std::cout << "\t<TEAM_NAME>  is the team name with Phoenix2D as default" << std::endl;
	std::cout << "\t<AGENT_TYPE> can be p(layer), g(oalie), c(oach) or t(trainer), and it is p as default" << std::endl;
	std::cout << "\t<HOSTNAME>   is the dns domain or ip address of the running host, and hostname is by default" << std::endl;
	std::cout << "Enjoy!" << std::endl;
	std::cout << "Ivan Gonzalez nigm2005@gmail.com" << std::endl << std::endl;
}
