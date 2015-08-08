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
 * @file Command.cpp
 *
 * @author Nelson I. Gonzalez
 */

#ifndef COMMAND_HPP_
#define COMMAND_HPP_

#include <string>

/*! @addtogroup phoenix_base
 * @{
 */
namespace Phoenix {

/*!
 * @brief <STRONG> COMMAND_STATUS <BR> </STRONG>
 * The Command Status means the current status of the command.  All the commands are created in CREATED
 * status and this status is changed once the command is sent to SENT.  In the new cycle the command is
 * compared to the commands executed in the previous cycle using the information provided by the sense_body
 * sensor to change the status to EXECUTED.  In case the command is not sent and flags an error, the status
 * is changed to ERROR.
 */
enum COMMAND_STATUS {
	CREATED,		///< Command created status
	SENT,			///< Command sent status
	EXECUTED,		///< Command executed status
	ERROR			///< Command error status
};

/*!
 * @brief <STRONG> COMMAND_TYPE <BR> </STRONG>
 * The Command Type is used to store the related information about the command.  For example, for a DASH
 * command type, the given information is stored as power and direction and can be accessed using the
 * getDashPower() and getDashDirection() methods respectively.
 */
enum COMMAND_TYPE {
	EMPTY,				///< Used by Player and Goalie
	MOVE,				///< Used by Player and Goalie
	DASH,				///< Used by Player and Goalie
	TURN,				///< Used by Player and Goalie
	SAY,				///< Used by Player and Goalie
	CATCH,				///< Used by Player and Goalie
	KICK,				///< Used by Player and Goalie
	TACKLE,				///< Used by Player and Goalie
	TURN_NECK,			///< Used by Player and Goalie
	POINT,				///< Used by Player and Goalie
	CHANGE_VIEW,		///< Used by Player and Goalie
	MOVE_OBJECT,		///< Used by Trainer
	CHANGE_MODE,		///< Used by Trainer
	START,				///< Used by Trainer
	RECOVER,			///< Used by Trainer
	CHANGE_PLAYER_TYPE	///< Used by trainer and/or coach
};

/*!
 * @brief <STRONG> Command <BR> </STRONG>
 * The Command object store information about the basic commands understood by the server.  It stores the
 * command in string format ready to be sent to the server, along with the primitive value of the arguments
 * for any given command.
 */
class Command {
public:
	/*!
	 * @brief Command default constructor
	 */
	Command();
	/*!
	 * @brief Command constructor given the arguments
	 * @param command command string ready to be sent to the server
	 * @param weight command weight, it is 1 or 0
	 * @param type command type
	 * There are some commands that can be appended to others, and there are some command that cannot.  For
	 * example, a change view command can be sent along with a dash command, but a turn command cannot be sent
	 * along with a dash command.  The weight parameter indicates the dispatcher if the command can be appended
	 * to the string to be sent to the server.  See the Commands object.
	 */
	Command(std::string command, int weight, COMMAND_TYPE type);
	/*!
	 * @brief Command constructor given the arguments
	 * @param command command string ready to be sent to the server
	 * @param weight command weight, it is 1 or 0
	 * @param type command type
	 */
	Command(std::string command, int weight, COMMAND_TYPE type, double arg0);
	/*!
	 * @brief Command constructor given the arguments
	 * @param command command string ready to be sent to the server
	 * @param weight command weight, it is 1 or 0
	 * @param type command type
	 */
	Command(std::string command, int weight, COMMAND_TYPE type, double arg0, double arg1);
	/*!
	 * @brief Command constructor given the arguments
	 * @param command command string ready to be sent to the server
	 * @param weight command weight, it is 1 or 0
	 * @param type command type
	 */
	Command(std::string command, int weight, COMMAND_TYPE type, std::string arg0);
	/*!
	 * @brief Command constructor given the arguments
	 * @param command command string ready to be sent to the server
	 * @param weight command weight, it is 1 or 0
	 * @param type command type
	 */
	Command(std::string command, int weight, COMMAND_TYPE type, double arg0, bool arg1);
	/*!
	 * @brief Command default destructor
	 */
	~Command();
	/*!
	 * @brief Returns the command string to be sent to the server
	 */
	std::string command();
	/*!
	 * @brief Returns the current command weight
	 */
	int weight();
	/*!
	 * @brief Returns the current command type
	 */
	COMMAND_TYPE commandType();
	/*!
	 * @brief Returns the current command status
	 */
	COMMAND_STATUS status();
	/*!
	 * @brief Returns the dash power for a DASH command
	 */
	double dashPower();
	/*!
	 * @brief Returns the dash direction for a DASH command
	 */
	double dashDirection();
	/*!
	 * @brief Returns the turn moment for a TURN command
	 */
	double turnMoment();
	/*!
	 * @brief Returns the absolute x position for a MOVE command
	 */
	double moveX();
	/*!
	 * @brief Returns the absolute y position for a MOVE command
	 */
	double moveY();
	/*!
	 * @brief Returns the message broadcasted for a SAY command
	 */
	std::string sayMessage();
	/*!
	 * @brief Returns the catch direction for a CATCH direction (only valid for a coach agent)
	 */
	double catchDirection();
	/*!
	 * @brief Returns the kick power for a KICK command
	 */
	double kickPower();
	/*!
	 * @brief Returns the kick direction for a KICK command
	 */
	double kickDirection();
	/*!
	 * @brief Returns the tackle power for a TACKLE command
	 */
	double tacklePower();
	/*!
	 * @brief Returns the will to tackle for a TACKLE command
	 * According to the rcssserver manual, if the will to tackle is true the kick applied to
	 * the ball is 10x higher, however, it is highly probably to be marked as fault
	 */
	bool tackleWillToFoul();
	/*!
	 * @brief Returns the turn neck moment for a TURN_NECK command
	 */
	double turnNeckMoment();
	/*!
	 * @brief Returns the point relative distance for a POINT command
	 */
	double pointDistance();
	/*!
	 * @brief Returns the point relative direction for a POINT command
	 */
	double pointDirection();
	/*!
	 * @brief Returns the new width to be changed in a CHANGE_VIEW command
	 */
	std::string changeViewWidth();
	/*!
	 * @brief Change the command current status to the given status
	 * @param status new command status for the object
	 */
	void setStatus(COMMAND_STATUS status);
	/*!
	 * @brief Returns the simulation time the command was created
	 */
	int createdAt();
private:
	int _weight;				///< current command weight
	int _simulation_time;		///< simulation time the command was created
	double _double_arg_0;		///< first double argument for a given command type
	double _double_arg_1;		///< second double argument for a given command type
	bool _bool_arg_0;			///< first boolean argument for a given command type
	bool _bool_arg_1;			///< second boolean argument for a given command type
	std::string _string_arg_0;	///< first string argument for a given command type
	std::string _string_arg_1;	///< second string argument for a given command type
	std::string _command;		///< current command string to be sent to the server
	COMMAND_TYPE _type;			///< current command type
	COMMAND_STATUS _status;		///< current comman status
};

} // End namespace Phoenix
/*! @} */


#endif /* COMMAND_HPP_ */
