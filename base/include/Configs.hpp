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
namespace Configs {

	/*!
	 * @brief Load general configurations values from the provided filename
	 * @param filename file path from where to load the configuration values
	 */
	void loadConfigs(std::string filename = "");
	/*!
	 * @brief Load team configuration values from the provided filename
	 * @param filename file path from where to load the configuration values
	 */
	void loadTeam(std::string filename = "");
	Position POSITION;					///< Default position for the agent
	bool LOGGING;						///< If true the player can dump data to a file log
	bool TRAINER_LOGGING;				///< If true the trainer can dump data to a file log
	bool VERBOSE;						///< If true the agent will print data for debugging purposes
	bool SAVE_SEE;						///< If true the agent will log the data received in the see sensor
	bool SAVE_HEAR;						///< If true the agent will log the data received in the hear sensor
	bool SAVE_FULLSTATE;				///< If true the agent will log the data received in the fullstate sensor
	bool SAVE_SENSE_BODY;				///< If true the agent will log the data received in the sense_body sensor
	bool SAVE_COMMANDS;					///< If true the agent will log the commands sent to the server
	unsigned int CYCLE_OFFSET;			///< Number of milliseconds to wait for new messages before the new cycle start
	unsigned int BUFFER_MAX_HISTORY;	///< Size of the circular buffers used for the sense body data
	unsigned int PLAYER_MAX_HISTORY;	///< Size of the player buffers used for the see data
	unsigned int BALL_MAX_HISTORY;		///< Size of the ball buffer used for the see data
	unsigned int COMMANDS_MAX_HISTORY;	///< Size of the commands buffer used for the commands to be sent
	unsigned int COMMAND_PRECISION;		///< Decimal precision for the string commands to be sent to the server
	std::string LOG_NAME;				///< Log name to be used if LOGGING is enabled
	std::string LOG_EXTENSION;			///< Extension for the log file
	bool PLAYER_HISTORY;				///< If true the agent will use the player buffers to access data from previous cycles
	bool PLAYER_TRACKING;				///< If true the agent will construct the path for each player in the field
	bool BALL_TRACKING;					///< If true the agent will construct the path for the ball
	double TRACKING_THRESHOLD;			///< When the match for two players is below this value the player will not be tracked
	std::string TRACKING;				///< Indicates which tracking method will be used for the player tracking
	std::string LOCALIZATION;			///< Indicates which localization method will be used for the player and goalie agents

}

} // End namespace Phoenix
/*! @} */


#endif /* CONFIGS_HPP_ */
