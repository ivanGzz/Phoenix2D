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
 * @file Configs.cpp
 *
 * @author Nelson I. Gonzalez
 */

#include <fstream>
#include <iostream>
#include "Configs.hpp"
#include "Self.hpp"
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <exception>
#include "Controller.hpp"

namespace Phoenix {

namespace Configs {

//Globals
unsigned int CYCLE_OFFSET = 20;
unsigned int BUFFER_MAX_HISTORY = 4;
unsigned int PLAYER_MAX_HISTORY = 16;
unsigned int BALL_MAX_HISTORY = 16;
unsigned int COMMANDS_MAX_HISTORY = 4;
unsigned int COMMAND_PRECISION = 4;
std::string LOG_NAME = "";
std::string LOG_EXTENSION = "log";
double TRACKING_THRESHOLD = 1.5;
//individuals
double xs[] = {-50.0, -10.0, -1.0, -1.0, -12.0, -2.0, -2.0, -14.0, -14.0, -14.0, -14.0};
double ys[] = {0.0, 0.0, -10.0, 10.0, 0.0, -11.0, 11.0, -5.0, 5.0, -10.0, 10.0};
Position POSITION;
bool PLAYER_HISTORY = false;
bool PLAYER_TRACKING = false;
bool BALL_TRACKING = true;
bool LOGGING = false;
bool TRAINER_LOGGING = false;
bool VERBOSE = false;
std::string LOCALIZATION = "lowpassfilter";
std::string TRACKING = "qualifier";
bool SAVE_SEE = false;
bool SAVE_HEAR = false;
bool SAVE_FULLSTATE = false;
bool SAVE_SENSE_BODY = false;
bool SAVE_COMMANDS = false;

/*
 * Example:
 * {"configs": {
 *    "commands": {
 *      "buffer": 4,
 *      "precision": 4
 *    },
 *    "players": {
 *      "buffer": 8
 *    },
 *    "ball": {
 *      "buffer": 8
 *    }
 *    "logging": {
 *      "logname": "test"
 *    }
 *    "self": {
 *      "params": {
 *        "buffer": 8
 *      },
 *      "offset": 20,
 *      "localization": "lowpassfilter"
 *    }
 *  }
 *  }
 */
void loadConfigs(std::string filename) {
	bool using_default = false;
	if (filename.length() == 0) {
		filename = "configs.json";
		using_default = true;
	}
	std::ifstream file(filename.c_str(), std::ifstream::in);
	if (file) {
		try {
			boost::property_tree::ptree pt;
			boost::property_tree::read_json(file, pt);
			CYCLE_OFFSET         = pt.get("configs.self.offset", 20);
			BUFFER_MAX_HISTORY   = pt.get("configs.self.params.buffer", 8);
			PLAYER_MAX_HISTORY   = pt.get("configs.players.buffer", 16);
			BALL_MAX_HISTORY     = pt.get("configs.ball.buffer", 16);
			COMMANDS_MAX_HISTORY = pt.get("configs.commands.buffer", 4);
			COMMAND_PRECISION    = pt.get("configs.commands.precision", 4);
			LOG_NAME             = pt.get("configs.logging.logname", "");
			LOG_EXTENSION		 = pt.get("configs.logging.extension", "log");
			TRACKING			  = pt.get("configs.self.tracking", "qualifier");
			LOCALIZATION         = pt.get("configs.self.localization", "lowpassfilter");
			TRACKING_THRESHOLD   = pt.get("configs.world.threshold", 1.50);
			file.close();
		}
		catch (std::exception const &e) {
			std::cerr << e.what() << std::endl;
			file.close();
		}
	} else {
		if (!using_default) {
			std::cerr << "Configs::loadConfigs() -> file " << filename << " does not exist" << std::endl;
		}
	}
}

/*
 * Example:
 * {"team": {
 *    "1": {
 *      "x": -10.0,
 *      "y": 0.0,
 *      "logging": false,
 *      "verbose": false
 *      "world" : {
 *      	"history": false,
 *      	"tracking": false,
 *      },
 *      "sensors": {
 *      	"see": false,
 *      	"body": false,
 *      	"hear": false,
 *      	"fullstate": false,
 *    	},
 *    	"commands": false
 *    },
 *    "2": {
 *      "x": -20.0,
 *      "y": 0.0,
 *      "logging": true,
 *      "verbose": false
 *    }
 *  }
 * }
 */
void loadTeamConfigs(std::string filename) {
	bool using_default = false;
	if (filename.length() == 0) {
		filename = Self::TEAM_NAME + ".json";
		using_default = true;
	}
	std::ifstream file(filename.c_str(), std::ifstream::in);
	if (file) {
		std::stringstream ss;
		ss << "team." <<  Self::UNIFORM_NUMBER << "." << std::endl;
		std::string path;
		std::getline(ss, path);
		try {
			boost::property_tree::ptree pt;
			boost::property_tree::read_json(file, pt);
			double x_default = xs[Self::UNIFORM_NUMBER - 1];
			double y_default = ys[Self::UNIFORM_NUMBER - 1];
			double x = pt.get(path + "x", x_default);
			double y = pt.get(path + "y", y_default);
			POSITION 			= Position(x, y);
			LOGGING  			= pt.get(path + "logging", false);
			VERBOSE  			= pt.get(path + "verbose", false);
			PLAYER_HISTORY 	= pt.get(path + "world.history", false);
			PLAYER_TRACKING	= pt.get(path + "world.tracking", false);
			BALL_TRACKING      = pt.get(path + "world.ball", true);
			SAVE_FULLSTATE 	= pt.get(path + "sensors.fullstate", false);
			SAVE_SEE 			= pt.get(path + "sensors.see", false);
			SAVE_SENSE_BODY 	= pt.get(path + "sensors.body", false);
			SAVE_HEAR			= pt.get(path + "sensors.hear", false);
			SAVE_COMMANDS		= pt.get(path + "commands", false);
			file.close();
		}
		catch (std::exception const &e) {
			std::cerr << e.what() << std::endl;
			file.close();
		}
	} else {
		if (!using_default) {
			std::cerr << "Configs::loadTeamConfigs() -> file " << filename << " does not exist" << std::endl;
		}
	}
}

}

}
