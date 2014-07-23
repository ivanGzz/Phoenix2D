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
 * @file Configs.cpp
 *
 * @author Nelson Ivan Gonzalez
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

//Globals
unsigned int Configs::CYCLE_OFFSET = 20;
unsigned int Configs::BUFFER_MAX_HISTORY = 4;
unsigned int Configs::PLAYER_MAX_HISTORY = 16;
unsigned int Configs::BALL_MAX_HISTORY = 16;
unsigned int Configs::COMMANDS_MAX_HISTORY = 4;
unsigned int Configs::COMMAND_PRECISION = 4;
std::string Configs::LOG_NAME = "";
double Configs::TRACKING_THRESHOLD = 1.5;
//individuals
double xs[] = {-50.0, -10.0, -1.0, -1.0, -12.0, -2.0, -2.0, -14.0, -14.0, -14.0, -14.0};
double ys[] = {0.0, 0.0, -10.0, 10.0, 0.0, -11.0, 11.0, -5.0, 5.0, -10.0, 10.0};
Position Configs::POSITION;
bool Configs::PLAYER_HISTORY = false;
bool Configs::PLAYER_TRACKING = false;
bool Configs::LOGGING = false;
bool Configs::TRAINER_LOGGING = false;
bool Configs::VERBOSE = false;
std::string Configs::LOCALIZATION = "lowpassfilter";
bool Configs::SAVE_SEE = false;
bool Configs::SAVE_HEAR = false;
bool Configs::SAVE_FULLSTATE = false;
bool Configs::SAVE_SENSE_BODY = false;
bool Configs::SAVE_COMMANDS = false;

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
void Configs::loadConfigs(std::string filename) {
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
//			Configs::SAVE_SEE             = pt.get("configs.savesensors.see", false);
//			Configs::SAVE_SENSE_BODY      = pt.get("configs.savesensors.body", false);
//			Configs::SAVE_HEAR            = pt.get("configs.savesensors.hear", false);
//			Configs::SAVE_FULLSTATE       = pt.get("configs.savesensors.fullstate", false);
//			Configs::SAVE_COMMANDS		  = pt.get("configs.savesensors.commands", false);
			Configs::CYCLE_OFFSET         = pt.get("configs.self.offset", 20);
			Configs::BUFFER_MAX_HISTORY   = pt.get("configs.self.params.buffer", 8);
			Configs::PLAYER_MAX_HISTORY   = pt.get("configs.players.buffer", 16);
			Configs::BALL_MAX_HISTORY     = pt.get("configs.ball.buffer", 16);
			Configs::COMMANDS_MAX_HISTORY = pt.get("configs.commands.buffer", 4);
			Configs::COMMAND_PRECISION    = pt.get("configs.commands.precision", 4);
			Configs::LOG_NAME             = pt.get("configs.logging.logname", "");
			Configs::LOCALIZATION         = pt.get("configs.self.localization", "lowpassfilter");
			Configs::TRACKING_THRESHOLD   = pt.get("configs.world.threshold", 0.25);
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
void Configs::loadTeam(std::string filename) {
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
			Configs::POSITION 			= Position(x, y);
			Configs::LOGGING  			= pt.get(path + "logging", false);
			Configs::VERBOSE  			= pt.get(path + "verbose", false);
			Configs::PLAYER_HISTORY 	= pt.get(path + "world.history", false);
			Configs::PLAYER_TRACKING	= pt.get(path + "world.tracking", false);
			Configs::SAVE_FULLSTATE 	= pt.get(path + "sensors.fullstate", false);
			Configs::SAVE_SEE 			= pt.get(path + "sensors.see", false);
			Configs::SAVE_SENSE_BODY 	= pt.get(path + "sensors.body", false);
			Configs::SAVE_HEAR			= pt.get(path + "sensors.hear", false);
			Configs::SAVE_COMMANDS		= pt.get(path + "commands", false);
			file.close();
		}
		catch (std::exception const &e) {
			std::cerr << e.what() << std::endl;
			file.close();
		}
	} else {
		if (!using_default) {
			std::cerr << "Configs::loadTeam() -> file " << filename << " does not exist" << std::endl;
		}
	}
}

}
