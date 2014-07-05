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

#ifndef CONFIGS_HPP_
#define CONFIGS_HPP_

#include "Position.hpp"
#include <string>

/*! @addtogroup phoenix_base
 * @{
 */
namespace Phoenix {

 /*!
 * @brief <STRONG> Configs <BR> </STRONG>
 * The Configs object is a set of configuration values used to customize
 * the behaviour of a Phoenix2D agent.
 */
class Configs {
public:
	/*!
	 * @brief Load general configurations values from the provided filename
	 * @param filename file path from where to load the configuration values
	 */
	static void loadConfigs(std::string filename);
	/*!
	 * @brief Load team configuration values from the provided filename
	 * @param filename file path from where to load the configuration values
	 */
	static void loadTeam(std::string filename);
	static Position POSITION;					///< Default position for the agent
	static bool LOGGING;						///< If true the player can dump data to a file log
	static bool TRAINER_LOGGING;				///< If true the trainer can dump data to a file log
	static bool VERBOSE;						///< If true the agent will print data for debugging purposes
	static bool SAVE_SEE;						///< If true the agent will log the data received in the see sensor
	static bool SAVE_HEAR;						///< If true the agent will log the data received in the hear sensor
	static bool SAVE_FULLSTATE;					///< If true the agent will log the data received in the fullstate sensor
	static bool SAVE_SENSE_BODY;				///< If true the agent will log the data received in the sense_body sensor
	static unsigned int CYCLE_OFFSET;			///< Number of millisencods to wait for new messages before the new cycle start
	static unsigned int BUFFER_MAX_HISTORY;		///< Size of the circular buffers used for the sense body data
	static unsigned int PLAYER_MAX_HISTORY;		///< Size of the player buffers used for the see data
	static unsigned int BALL_MAX_HISTORY;		///< Size of the ball buffer used for the see data
	static unsigned int COMMANDS_MAX_HISTORY;	///< Size of the commands buffer used for the commands to be sent
	static unsigned int COMMAND_PRECISION;		///< Decimal precision for the string commands to be sent to the server
	static std::string LOG_NAME;				///< Log name to be used if LOGGING is enabled
	static bool PLAYER_HISTORY;					///< If true the agent will use the player buffers to access data from previous cycles
	static std::string LOCALIZATION;			///< Indicates which localization method will be used for the player and goalie agents
};

} // End namespace Phoenix
/*! @} */


#endif /* CONFIGS_HPP_ */
