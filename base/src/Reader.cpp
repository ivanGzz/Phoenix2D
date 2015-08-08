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
 * @file Reader.cpp
 *
 * @author Nelson I. Gonzalez
 */

#include <string>
#include <iostream>
#include <pthread.h>
#include "Reader.hpp"
#include "Connect.hpp"
#include "Parser.hpp"
#include "Configs.hpp"

namespace Phoenix {

namespace Reader {

bool _running = false;
pthread_t _thread = 0;

void* run(void* arg) {
	while (_running) {
		Parser::parseMessage(Connect::receiveMessage());
	}
	return 0;
}

bool running() {
	return _running;
}

void start() {
	_running = true;
	if (pthread_create(&_thread, 0, run, 0) != 0) { //success) {
		_running = false;
		std::cerr << "Reader::start() -> error creating thread" << std::endl;
	}
}

void stop() {
	void *res;
	running = false;
	Connect::sendMessage("(bye)");
	Connect::disconnect();
	if (pthread_join(thread, &res) != 0) { //success) {
		std::cerr << "Reader::stop() -> failed to join thread" << std::endl;
	}
}

}

}
