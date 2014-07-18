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
 * @file Message.hpp
 *
 * @author Nelson Ivan Gonzalez
 */

#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include <string>

/*! @addtogroup phoenix_base
 * @{
 */
namespace Phoenix {

/*!
 * @brief <STRONG> Message <BR> </STRONG>
 * A Message object stores information about a message received in the hear sensor where the
 * sender can be any other agent connected to the server.
 */
class Message {
public:
	/*!
	 * @brief Message constructor for messages from the opponent team
	 * @param d relative direction of the sender
	 * @param team team name of the sender
	 * @param message message broadcasted by the sender
	 */
	Message(double d, std::string team, std::string message);
	/*!
	 * @brief Message constructor for messages from the same team
	 * @param d relative direction of the sender
	 * @param team team name of the sender
	 * @param unum uniform number of the sender
	 * @param message message broadcasted by the sender
	 */
	Message(double d, std::string team, int unum, std::string message);
	/*!
	 * @brief Message default destructor
	 */
	~Message();
	/*!
	 * @brief Returns message broadcasted by the sender
	 */
	std::string getMessage();
	/*!
	 * @brief Returns team name of the sender
	 */
	std::string getTeam();
	/*!
	 * @brief Returns uniform number of the sender if available, 0 if not
	 */
	int getUniformNumber();
	/*!
	 * @brief Returns relative direction of the sender
	 */
	double getDirection();
private:
	std::string message;	///< Message sent by the sender
	std::string team;		///< Team name of the sender
	int unum;				///< Uniform number of the sender
	double direction;		///< Relative direction of the sender
};

} // End namespace Phoenix
/*! @} */

#endif /* MESSAGE_HPP_ */
