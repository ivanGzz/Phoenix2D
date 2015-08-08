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
 * @file Logger.cpp
 *
 * @author Nelson Ivan Gonzalez
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include "Logger.hpp"
#include "Self.hpp"
#include "Controller.hpp"
#include "Configs.hpp"

namespace Phoenix {

namespace Logger {

std::filebuf buf;
std::streambuf* oldbuf;

void startLoggers() {
	std::stringstream ss;
	time_t t = time(0);   // get time now
	struct tm* now = localtime(&t);
	switch (Controller::AGENT_TYPE) {
	case 'p':
	case 'g':
		ss << Self::TEAM_NAME << "_" << Self::UNIFORM_NUMBER << ".";
		break;
	case 't':
		ss << "Trainer.";
		break;
	}
	ss << (1900 + now->tm_year);
	if (now->tm_mon < 9) {
		ss << "0" << (now->tm_mon + 1);
	} else {
		ss << (now->tm_mon + 1);
	}
	if (now->tm_mday < 10) {
		ss << "0" << now->tm_mday;
	} else {
		ss << now->tm_mday;
	}
	ss << "-";
	if (now->tm_hour < 10) {
		ss << "0" << now->tm_hour;
	} else {
		ss << now->tm_hour;
	}
	if (now->tm_min < 10) {
		ss << "0" << now->tm_min;
	} else {
		ss << now->tm_min;
	}
	if (now->tm_sec < 10) {
		ss << "0" << now->tm_sec;
	} else {
		ss << now->tm_sec;
	}
	std::string prefix;
	std::getline(ss, prefix);
	if (Configs::LOGGING) {
		std::string filename = prefix;
		if (Configs::LOG_NAME.length() > 0) {
			filename += "." + Configs::LOG_NAME;
		} else {
			filename += ".log";
		}
		filename += "." + Configs::LOG_EXTENSION;
		buf.open(filename.c_str(), std::ios::out);
		oldbuf = std::clog.rdbuf(&buf);
	}
	if (Configs::SAVE_COMMANDS) {
		std::string filename = prefix + ".commands.log";
		commands.open(filename.c_str());
	}
	if (Configs::SAVE_SENSE_BODY) {
		std::string filename = prefix + ".body.log";
		body.open(filename.c_str());
	}
	if (Configs::SAVE_SEE) {
		std::string filename = prefix + ".see.log";
		see.open(filename.c_str());
	}
	if (Configs::SAVE_HEAR) {
		std::string filename = prefix + ".hear.log";
		hear.open(filename.c_str());
	}
	if (Configs::SAVE_FULLSTATE) {
		std::string filename = prefix + ".fullstate.log";
		fullstate.open(filename.c_str());
	}
}

void endLoggers() {
	if (Configs::LOGGING) {
		std::clog.rdbuf(oldbuf);
		buf.close();
	}
	if (Configs::SAVE_COMMANDS) {
		commands.close();
	}
	if (Configs::SAVE_SENSE_BODY) {
		body.close();
	}
	if (Configs::SAVE_SEE) {
		see.close();
	}
	if (Configs::SAVE_HEAR) {
		hear.close();
	}
	if (Configs::SAVE_FULLSTATE) {
		fullstate.close();
	}
}

}

}
