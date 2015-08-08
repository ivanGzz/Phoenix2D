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
 * @file Commands.cpp
 *
 * @author Nelson I. Gonzalez
 */

#ifndef COMMANDS_HPP_
#define COMMANDS_HPP_

#include <string>

/*! @addtogroup phoenix_base
 * @{
 */
namespace Phoenix {

class Command;
 
 /*!
 * @brief <STRONG> Commands <BR> </STRONG>
 * The Commans object, or Dispatcher, stores the commands to be sent at the end of
 * the current cycle.  It also is in charge of creating the actual string sent to the
 * server using the string commands stored.
 */
namespace Commands {

	/*!
	 * @brief Removes sent commands stored in memory
	 */
	void flush();
	/*!
	 * @brief Put in queue a move command
	 * @param x absolute position in x for the move command
	 * @param y absolute position in y for the move command
	 * This command can only be used in play modes before_kick_off and goal_<SIDE>
	 */
	Command* move(double x, double y);
	/*!
	 * @brief Put in queue a turn command
	 * @param moment angle to turn for the turn command
	 * This command cannot be appended along with a dash, kick or catch command
	 */
	Command* turn(double moment);
	/*!
	 * @brief Put in queue a turn neck command
	 * @param moment angle to turn the neck for the turn neck command
	 */
	Command* turnNeck(double moment);
	/*!
	 * @brief Put in queue a dash command
	 * @param power dash power for the dash command
	 * @param direction dash direction for the dash command
	 * This command cannot be appended along with a turn, kick or catch command
	 */
	Command* dash(double power, double direction);
	/*!
	 * @brief Put in queue a say command
	 * @param message message to broadcast in the say command
	 */
	Command* say(std::string message);
	/*!
	 * @brief Put in queue a catch command
	 * @param direction catch direction for the command command
	 * This command can only be issued by a goalie agent
	 */
	Command* catchBall(double direction);
	/*!
	 * @brief Put in queue a kick command
	 * @param power kick power for the kick command
	 * @param direction kick direction for the kick command
	 * This command cannot be appended along with a dash, turn or catch command
	 */
	Command* kick(double power, double direction = 0.0);
	/*!
	 * @brief Put in queue a tackle command
	 * @param power tackle power for the tackle command
	 * @param willToFoul boolean indicating the player is will to foul the ball owner
	 */
	Command* tackle(double power, bool willToFoul = false);
	/*!
	 * @brief Put in queue a point to command
	 * @param distance relative distance of the point to point for the point to command
	 * @param direction relative direction of the point to point for the point to command
	 */
	Command* pointTo(double distance, double direction);
	/*!
	 * @brief Put in queue a change view command
	 * @param width new width for the vision sensor to be used in the next cycle
	 */
	Command* changeView(std::string width);
	/*!
	 * @brief Put in queue a move object command
	 * @param object descriptor string for the object to move
	 * @param x absolute position in x for the object
	 * @param y absolute position in y for the object
	 * This command can only be issued by a trainer agent
	 */
	Command* moveObject(std::string object, double x, double y);
	/*!
	 * @brief Put in queue a change mode command
	 * @param mode new mode to be used in the next cycle
	 * This command can only be issued by a trainer agent.  The mode means the new play mode
	 * to be executed since the beginning of the next cycle
	 */
	Command* changeMode(std::string mode);
	/*!
	 * @brief Put in queue a start command
	 * This command can only be issued by a trainer agent. Equivalent to changeMode("kick_off_<SIDE>")
	 */
	Command* start();
	/*!
	 * @brief Put in queue a recover command
	 * This command can only be issued by a trainer agent.  The next cycle all the players stamina will
	 * be replenished.
	 */
	Command* recover();
	/*!
	 * @brief Sent the commands in queue in the order that the commands were received until the accumulated
	 * weight changes from 1 to 2.  
	 * @return amount of sent commands.
	 */
	int sendCommands();
	
}

} // End namespace Phoenix
/*! @} */

#endif /* COMMANDS_HPP_ */
