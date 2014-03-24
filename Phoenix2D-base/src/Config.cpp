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

#include <fstream>
#include <boost/regex.hpp>
#include <cstdlib>
#include <iostream>
#include "Config.h"
#include "Self.h"
namespace Phoenix
{
boost::regex config_regex("\\(config\\s(\\w+)\\s(\\w+)\\)");
boost::regex position_regex("\\(position\\s(\\d+)\\s([\\d\\.\\-]+)\\s([\\d\\.\\-]+)\\)");
boost::regex logging_regex("\\(logging\\s(\\d+)\\)");
boost::regex verbose_regex("\\(verbose\\s(\\d+)\\)");
boost::regex player_history_regex("\\(player_history\\s(\\d+)\\)");

//Globals
unsigned int Config::BUFFER_MAX_HISTORY = 4;
unsigned int Config::PLAYER_MAX_HISTORY = 16;
unsigned int Config::BALL_MAX_HISTORY = 16;
unsigned int Config::COMMANDS_MAX_HISTORY = 4;
unsigned int Config::COMMAND_PRECISION = 4;
std::string Config::LOG_NAME = "";
//individuals
Position Config::POSITION;
bool Config::PLAYER_HISTORY = false;
bool Config::LOGGING = false;
bool Config::TRAINER_LOGGING = false;
bool Config::VERBOSE = false;

Config::Config() {
	std::ifstream file("conf.phx", std::ifstream::in);
	if (file) {
		std::string line;
		while (std::getline(file, line)) {
			if (line.size() > 0 && line[0] == '#') continue;
			boost::cmatch match;
			if (boost::regex_match(line.c_str(), match, config_regex)) {
				std::string config = std::string() + match[1];
				if (config.compare("buffer_max_history") == 0) {
					Config::BUFFER_MAX_HISTORY = (unsigned int)atoi((std::string() + match[2]).c_str());
				} else if (config.compare("player_max_history") == 0) {
					Config::PLAYER_MAX_HISTORY = (unsigned int)atoi((std::string() + match[2]).c_str());
				} else if (config.compare("ball_max_history") == 0) {
					Config::BALL_MAX_HISTORY = (unsigned int)atoi((std::string() + match[2]).c_str());
				} else if (config.compare("commands_max_history") == 0) {
					Config::COMMANDS_MAX_HISTORY = (unsigned int)atoi((std::string() + match[2]).c_str());
				} else if (config.compare("commands_precision") == 0) {
					Config::COMMAND_PRECISION = (unsigned int)atoi((std::string() + match[2]).c_str());
				} else if (config.compare("log_name") == 0) {
					Config::LOG_NAME = std::string() + match[2];
				}
			} else if (boost::regex_match(line.c_str(), match, logging_regex)) {
				int number = atoi((std::string() + match[1]).c_str());
				if (number == 0) {
					Config::TRAINER_LOGGING = true;
				}
			}
		}
		file.close();
	} else {
		std::cerr << "Config::Config() -> error opening conf.phx file" << std::cerr;
	}
}

Config::~Config() {

}

void Config::load() {
	switch (Self::UNIFORM_NUMBER) {
	case 1:
		Config::POSITION = Position(-50.0, 0.0);;
		break;
	case 2:
		Config::POSITION = Position(-10.0, 0.0);
		break;
	case 3:
		Config::POSITION = Position(-1.0, -10.0);
		break;
	case 4:
		Config::POSITION = Position(-1.0, 10.0);
		break;
	case 5:
		Config::POSITION = Position(-12.0, 0.0);
		break;
	case 6:
		Config::POSITION = Position(-2.0, -11.0);
		break;
	case 7:
		Config::POSITION = Position(-2.0, 11.0);
		break;
	case 8:
		Config::POSITION = Position(-14.0, -5.0);
		break;
	case 9:
		Config::POSITION = Position(-14.0, 5.0);
		break;
	case 10:
		Config::POSITION = Position(-14.0, -10.0);
		break;
	case 11:
		Config::POSITION = Position(-14.0, 10.0);
		break;
	}
	std::string filename = Self::TEAM_NAME + ".phx";
	std::ifstream file(filename.c_str(), std::ifstream::in);
	if (file) {
		std::string line;
		while (std::getline(file, line)) {
			if (line.size() > 0 && line[0] == '#') continue;
			boost::cmatch match;
			if (boost::regex_match(line.c_str(), match, position_regex)) {
				int number = atoi((std::string() + match[1]).c_str());
				double x = atof((std::string() + match[2]).c_str());
				double y = atof((std::string() + match[3]).c_str());
				if (Self::UNIFORM_NUMBER == number) {
					Config::POSITION = Position(x, y);
				}
			} else if (boost::regex_match(line.c_str(), match, logging_regex)) {
				int number = atoi((std::string() + match[1]).c_str());
				if (Self::UNIFORM_NUMBER == number) {
					Config::LOGGING = true;
				}
			} else if (boost::regex_match(line.c_str(), match, verbose_regex)) {
				int number = atoi((std::string() + match[1]).c_str());
				if (Self::UNIFORM_NUMBER == number) {
					Config::VERBOSE = true;
				}
			} else if (boost::regex_match(line.c_str(), match, player_history_regex)) {
				int number = atoi((std::string() + match[1]).c_str());
				if (Self::UNIFORM_NUMBER == number) {
					Config::PLAYER_HISTORY = true;
				}
			}
		}
		file.close();
	} else {
		std::cerr << "Config::load() -> error opening " << filename << " file" << std::endl;
	}
}
}