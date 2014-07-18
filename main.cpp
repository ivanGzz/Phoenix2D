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
#include <string>
#include "Controller.hpp"
#include "Configs.hpp"
#include "tests.hpp"
#include "ai.hpp"

void loadAI(Phoenix::Controller &controller) {
	switch (Controller::AGENT_TYPE) {
	case 'p':
		controller.registerSetupFunction(player::onSetup);
		controller.registerPlayerFunction("before_kick_off", player::executeBeforeKickOff);
		controller.registerFinishFunction(player::onFinish);
		break;
	case 'g':
		controller.registerSetupFunction(goalie::onSetup);
		controller.registerPlayerFunction("before_kick_off", goalie::executeBeforeKickOff);
		controller.registerFinishFunction(goalie::onFinish);
		break;
	case 'c':
		controller.registerSetupFunction(coach::onSetup);
		controller.registerPlayerFunction("before_kick_off", coach::executeBeforeKickOff);
		controller.registerFinishFunction(coach::onFinish);
		break;
	default:
		break;
	}
}

void loadTest(std::string test, Phoenix::Controller &controller) {
	if (test.compare("localization") == 0) {
		controller.registerSetupFunction(localization::onStart);
		controller.registerPlayerFunction("before_kick_off", localization::executeBeforeKickOff);
		controller.registerPlayerFunction("play_on", localization::executePlayOn);
		controller.registerFinishFunction(localization::onFinish);
	} else if (test.compare("dribble") == 0) {
		controller.registerSetupFunction(dribble::onStart);
		controller.registerPlayerFunction("before_kick_off", dribble::executeBeforeKickOff);
		controller.registerPlayerFunction("play_on", dribble::executePlayOn);
		controller.registerFinishFunction(dribble::onFinish);
	} else if (test.compare("world") == 0) {
		controller.registerSetupFunction(worldtest::onStart);
		controller.registerPlayerFunction("before_kick_off", worldtest::executeBeforeKickOff);
		controller.registerPlayerFunction("play_on", worldtest::executePlayOn);
		controller.registerFinishFunction(worldtest::onFinish);
	}
}

void printUsage();

void printHelp();

void printVersion();

void runTest(std::string test, char type, char* teamname, char* hostname);

void runAI(char type, char* teamname, char* hostname);

void runTrainer(char* script, char* hostname);

int main(int argc, char **argv) {
	if (argc < 2) {
		printUsage();
		return 0;
	}
	std::string command = std::string(argv[1]);
	std::string test_name;
	char* team_name = "Phoenix2D";
	char agent_type = 'p';
	char* hostname = "localhost";
	if (command.compare("--version") == 0) {
		printVersion();
	}
	else if (command.compare("--help") == 0) {
		printUsage();
		printHelp();
	}
	else if (command.compare("run") == 0) {
		switch (argc) {
		case 1:
		case 2:
			break;
		case 3:
			team_name = argv[2];
			break;
		case 4:
			team_name = argv[2];
			agent_type = argv[3][0];
			break;
		default:
			team_name = argv[2];
			agent_type = argv[3][0];
			hostname = argv[4];
			break;
		}
		runAI(agent_type, team_name, hostname);
	}
	else if (command.compare("test") == 0) {
		switch (argc) {
		case 1:
		case 2:
			std::cerr << "Test need test name" << std::endl;
			return 0;
			break;
		case 3:
			test_name = std::string(argv[2]);
			break;
		case 4:
			test_name = std::string(argv[2]);
			team_name = argv[3];
			break;
		case 5:
			test_name = std::string(argv[2]);
			team_name = argv[3];
			agent_type = argv[4][0];
			break;
		default:
			test_name = std::string(argv[2]);
			team_name = argv[3];
			agent_type = argv[4][0];
			hostname = argv[5];
			break;
		}
		runTest(test_name, agent_type, team_name, hostname);
	}
	else if (command.compare("trainer") == 0) {
		char* script;
		char* hostname = "localhost";
		if (argc > 2) {
			script = argv[2];
			if (argc > 3) {
				hostname = argv[3];
			}
			runTrainer(script, hostname);
		} else {
			std::cerr << "Trainer need the script file" << std::endl;
		}
	}
	else {
		printUsage();
	}
	return 0;
}

void printVersion() {
	std::cout << "--- Phoenix2D 2014 ---\n"
			     "version 1.1" << std::endl;
}

void printUsage() {
	std::cout << "--- Phoenix2D 2014 ---\n\n"
			     "usage: ./agent [--version] [--help] <command>\n" << std::endl;
}

void printHelp() {
	std::cout << "Commands:\n";
	            /*--------------------------------------------------------------------------------*/
	std::cout << "  run <team_name> <agent_type> <hostname>: runs the AI with type\n"
			     "         <agent_type> and team <team_name> in <hostname>" << std::endl;
	std::cout << "  test <test_name> <teamname> <agent_type> <hostname>: runs the\n"
			     "         test <test_name> of type <agent_type> with <teamname>\n" ""
			     "         in <hostname>"<< std::endl;
	std::cout << "  trainer <script> <hostname>: runs the trainer with the given\n"
			     "         <script> file in <hostname>" << std::endl;
	std::cout << "\n<agent_type> can be p(layer), g(oalie) or c(oach)" << std::endl;
}

void runTest(std::string test, char type, char* teamname, char* hostname) {
	Configs::loadConfigs("");
	Phoenix::Controller controller(teamname, type, hostname);
	loadTest(test, controller);
	controller.connect();
	controller.run();
	controller.disconnect();
}

void runAI(char type, char* teamname, char* hostname) {
	Configs::loadConfigs("");
	Phoenix::Controller controller(teamname, type, hostname);
	loadAI(controller);
	controller.connect();
	controller.run();
	controller.disconnect();
}

void runTrainer(char* script, char* hostname) {
//	Configs::loadConfigs("");
	Phoenix::Controller controller("trainer", 't', hostname);
	controller.registerTrainerScript(std::string(script));
	controller.connect();
	controller.run();
	controller.disconnect();
}
