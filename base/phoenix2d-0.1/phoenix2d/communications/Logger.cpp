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
#include <iostream>
#include <sstream>
#include <ctime>
#include "Logger.h"
#include "Self.h"
#include "Controller.h"
#include "Config.h"
namespace Phoenix
{
std::filebuf buf;
std::streambuf* oldbuf;

Logger::Logger() {
	logging = false;
}

Logger::~Logger() {
	if (logging) {
		std::clog.rdbuf(oldbuf);
		buf.close();
	}
}

void Logger::log() {
	logging = true;
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
	if (Config::LOG_NAME.length() > 0) {
		ss << Config::LOG_NAME << ".";
	}
	if (now->tm_mday < 10) {
		ss << "0" << now->tm_mday << ".";
	} else {
		ss << now->tm_mday << ".";
	}
	if (now->tm_mon < 10) {
		ss << "0" << now->tm_mon << "-";
	} else {
		ss << now->tm_mon << "-";
	}
	if (now->tm_hour < 10) {
		ss << "0" << now->tm_hour << ".";
	} else {
		ss << now->tm_hour << ".";
	}
	if (now->tm_min < 10) {
		ss << "0" << now->tm_min << ".";
	} else {
		ss << now->tm_min << ".";
	}
	if (now->tm_sec < 10) {
		ss << "0" << now->tm_sec;
	} else {
		ss << now->tm_sec;
	}
	ss << ".log" << std::endl;
	std::string filename;
	std::getline(ss, filename);
	buf.open(filename.c_str(), std::ios::out);
	oldbuf = std::clog.rdbuf(&buf);
}
}