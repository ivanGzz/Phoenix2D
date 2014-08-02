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
 * @file Connect.hpp
 *
 * @author Nelson Ivan Gonzalez
 */

#ifndef CONNECT_HPP_
#define CONNECT_HPP_

#include <string>

/*! @addtogroup phoenix_base
 * @{
 */
namespace Phoenix {

/*!
* @brief <STRONG> Connect <BR> </STRONG>
* The Configs object is in charge of send and receives UDP packages to and from
* the server.
*/
class Connect {
public:
	/*!
	 * @brief Connect default constructor
	 * @param host hostname to connect, where the server is running
	 * @param port port to connect, where the server is listening
	 * The port for players and goalies is 6000, for trainer 6001 and coaches 6002.
	 */
	Connect(std::string host, int port);
	/*!
	 * @brief Connect default destructor
	 */
	~Connect();
	/*!
	 * @brief Stops and shuts down the connection with the server
	 */
	void disconnect();
	/*!
	 * @brief send a message to the server in hostname and port
	 * @param msg message to send
	 */
	bool sendMessage(std::string msg);
	/*!
	 * @brief Returns a message sent by the server.
	 * It is a blocking method: returns until there is a new message in the buffer.
	 */
	std::string receiveMessage();
};

} // End namespace Phoenix
/*! @} */


#endif /* CONNECT_HPP_ */
