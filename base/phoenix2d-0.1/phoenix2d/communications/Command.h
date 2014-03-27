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

#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>

/*! @addtogroup phoenix_main
 * @{
 */
namespace Phoenix
{

 /*!
 * @brief <STRONG> COMMAND_STATUS <BR> </STRONG>
 * The Command type lorem Ipsum
 */
enum COMMAND_STATUS {
	CREATED,		///<
	SENT,			///<
	EXECUTED,		///<
	ERROR			///<
};

 /*!
 * @brief <STRONG> COMMAND_TYPE <BR> </STRONG>
 * The Command type lorem Ipsum
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
 * The Command lorem Ipsum
 */
class Command {
	std::string command;
	int weight;
	COMMAND_TYPE type;
	COMMAND_STATUS status;
	double double_arg_0;
	double double_arg_1;
	std::string string_arg_0;
	std::string string_arg_1;
	bool bool_arg_0;
	bool bool_arg_1;
	int simulation_time;
public:
	Command();
	Command(std::string command, int weight, COMMAND_TYPE type);
	~Command();
	void setArgs(void* arg0, void* arg1 = 0, void* arg2 = 0);
	std::string getCommand();
	int getWeight();
	COMMAND_TYPE getCommandType();
	COMMAND_STATUS getCommandStatus();
	double getDashPower();
	double getDashDirection();
	double getTurnMoment();
	double getMoveX();
	double getMoveY();
	std::string getSayMessage();
	double getCatchDirection();
	double getKickPower();
	double getKickDirection();
	double getTacklePower();
	bool getTackleWillToFoul();
	double getTurnNeckMoment();
	double getPointDistance();
	double getPointDirection();
	std::string getChangeViewWidth();
	void changeStatusTo(COMMAND_STATUS status);
	int createdAt();
};

} // End namespace Phoenix
/*! @} */


#endif /* COMMAND_H_ */
