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

void printUsage();

void printHelp();

void printVersion();

void loadAI(Phoenix::Controller controller) {

}

void loadTest(std::string test, Phoenix::Controller controller) {
	if (test.compare("localization") == 0) {
		controller.registerSetupFunction(localization::onStart);
		controller.registerPlayerFunction("before_kick_off", localization::executeBeforeKickOff);
		controller.registerPlayerFunction("play_on", localization::executePlayOn);
		controller.registerFinishFunction(localization::onFinish);
	}
}

int main(int argc, char **argv) {
	if (argc < 2) {
		printUsage();
		return 0;
	}
	std::string command = std::string(argv[1]);
	bool test = false;
	if (command.compare("--version") == 0) {
		printVersion();
		return 0;
	} else if (command.compare("--help") == 0) {
		printUsage();
		printHelp();
		return 0;
	} else if (command.compare("run") == 0) {

	} else if (command.compare("test") == 0) {
		test = true;
	} else {
		printUsage();
		return 0;
	}
	Phoenix::Configs config;
	const char *team_name, *hostname;
	std::string test_name;
	char agent_type;
	team_name = "Phoenix2D";
	agent_type = 'p';
	hostname = "localhost";
	if (test) {
		switch (argc) {
		case 1:
		case 2:
		case 3:
			test_name = std::string(argv[2]);
			break;
		case 4:
			test_name = std::string(argv[2]);
			team_name = argv[3];
			break;
		default:
			test_name = std::string(argv[2]);
			team_name = argv[3];
			hostname = argv[4];
			break;
		}
	}
	else {
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
	}
	Phoenix::Controller controller(team_name, agent_type, hostname);
	if (test) {
		loadTest(test_name, controller);
	} else {
		loadAI(controller);
	}
	controller.connect();
	controller.run();
	controller.disconnect();
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
	std::cout << "  run <team_name> <agent_type> <hostname> run the AI with type\n"
			     "         <agent_type> and team <team_name> in <hostname>" << std::endl;
	std::cout << "  test <test_name> <team_name> <hostname> runs the test <test_name>\n" ""
			     "         with team <team_name> in <hostname>"<< std::endl;
}
