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
 * @file Parser.hpp
 *
 * @author Nelson Ivan Gonzalez
 */

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <string>

/*! @addtogroup phoenix_base
 * @{
 */
namespace Phoenix {

class Self;
class World;
class Messages;

 /*!
 * @brief <STRONG> Parser <BR> </STRONG>
 * The Parser object is in charge of convert the messages recieved by the server to
 * useful information to be used by the Phoenix2D framework.  It stores pointers to
 * Self, World and Messages objectos to send them their respective data structures.
 */
class Parser {
public:
	/*!
	 * @brief Parser default constructor
	 * @param self Pointer to Self object
	 * @param world Pointer to World object
	 * @param messages Pointer to Messages object
	 */
	Parser(Self *self, World *world, Messages* messages);
	/*!
	 * @brief Parser default destructor
	 */
	~Parser();
	/*!
	 * @brief Parse the received messages from the server
	 * @param message Message received from the server
	 */
	void parseMessage(std::string message);
};

} // End namespace Phoenix
/*! @} */

#endif /* PARSER_HPP_ */
