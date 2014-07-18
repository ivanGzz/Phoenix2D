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
 * @file Messages.hpp
 *
 * @author Nelson Ivan Gonzalez
 */

#ifndef MESSAGES_HPP_
#define MESSAGES_HPP_

#include <vector>
#include "Message.hpp"

/*! @addtogroup phoenix_base
 * @{
 */
namespace Phoenix {

/*!
 * @brief <STRONG> Messages <BR> </STRONG>
 * The Messages object stores all the messages received in a given simulation cycle.
 */
class Messages {
public:
	/*!
	 * @brief Messages default constructor
	 */
	Messages();
	/*!
	 * @brief Messages default destructor
	 */
	~Messages();
	/*!
	 * @brief Returns the messages received in the current cycle
	 */
	std::vector<Message> getMessages();
	/*!
	 * @brief Set the messages received in the current cycle
	 * @param messages list of messages recieved in the current cycle
	 */
	void setMessages(std::vector<Message> messages);
private:
	std::vector<Message> messages;	///< Current messages
};

} // End namespace Phoenix
/*! @} */

#endif /* MESSAGES_HPP_ */
