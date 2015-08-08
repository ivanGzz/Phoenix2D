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
 * @file localization.hpp
 *
 * @author Nelson I. Gonzalez
 */

#ifndef LOCALIZATION_H_
#define LOCALIZATION_H_

#include <vector>
#include "WorldModel.hpp"
#include "Messages.hpp"
#include "Commands.hpp"

using namespace Phoenix;

namespace localization {

void onStart();
void executeBeforeKickOff(WorldModel worldModel, std::vector<Message> messages);
void executePlayOn(WorldModel worldModel, std::vector<Message> messages);
void onFinish();

}

#endif /* LOCALIZATION_H_ */
