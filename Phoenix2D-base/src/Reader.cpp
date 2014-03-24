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

#include <string>
#include <iostream>
#include <pthread.h>
#include "Reader.h"
#include "Connect.h"
#include "Parser.h"
#include "Config.h"
namespace Phoenix
{
Connect* connect_ptr = 0;
Parser* parser_ptr = 0;
bool running = false;
pthread_t thread = 0;

void* run(void* arg) {
	Reader* reader = (Reader *)arg;
	reader->execute();
	return 0;
}

Reader::Reader(Connect *connect, Parser *parser) {
	connect_ptr = connect;
	parser_ptr = parser;
}

Reader::~Reader() {
	if (Config::VERBOSE) std::cout << "Reader out" << std::endl;
}

void Reader::execute() {
	while (running) {
		parser_ptr->parseMessage(connect_ptr->receiveMessage());
	}
}

bool Reader::isRunning() {
	return running;
}

void Reader::start() {
	running = true;
	int success = pthread_create(&thread, 0, run, (void *)this);
	if (success) {
		running = false;
		std::cerr << "Reader::start() -> error creating thread" << std::endl;
	}
}

void Reader::stop() {
	void *res;
	running = false;
	connect_ptr->sendMessage("(bye)");
	connect_ptr->disconnect();
	int success = pthread_join(thread, &res);
	if (success) {
		std::cerr << "Reader::stop() -> failed to join thread" << std::endl;
	}
}
}