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
 * @file Messages.cpp
 *
 * @author Nelson Ivan Gonzalez
 */

#include "Messages.hpp"
#include <iostream>
#include "Controller.hpp"

namespace Phoenix {

Messages::Messages() {

}

Messages::~Messages() {

}

std::vector<Message> Messages::getMessages() {
	return messages;
}

void Messages::setMessages(std::vector<Message> new_messages) {
	messages.clear();
	for (std::vector<Message>::iterator it = new_messages.begin(); it != new_messages.end(); ++it) {
		messages.push_back(*it);
	}
}

}
