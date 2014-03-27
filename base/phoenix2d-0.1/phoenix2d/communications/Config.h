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

#ifndef CONFIG_H_
#define CONFIG_H_

#include "Position.h"
#include <string>

namespace Phoenix
{

class Config {
public:
	Config();
	~Config();
	void load();
	static Position POSITION;
	static bool LOGGING;
	static bool TRAINER_LOGGING;
	static bool VERBOSE;
	static unsigned int BUFFER_MAX_HISTORY;
	static unsigned int PLAYER_MAX_HISTORY;
	static unsigned int BALL_MAX_HISTORY;
	static unsigned int COMMANDS_MAX_HISTORY;
	static unsigned int COMMAND_PRECISION;
	static std::string LOG_NAME;
	static bool PLAYER_HISTORY;
};

} // End namespace Phoenix
/*! @} */


#endif /* CONFIG_H_ */
