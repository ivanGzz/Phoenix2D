// $Id$
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
 *
 * @file Controller.h
 * 
 *
 *
 * @author Iván González
 */
 // $Log$

#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include <string>
#include <vector>
#include "WorldModel.hpp"
#include "Message.hpp"

/*!
 * @defgroup phoenix_main Phoenix Library Namespace
 * @brief <STRONG> Phoenix2D Master <BR> </STRONG>
 * The namespace that contains everything related to the Phoenix Library
 * @{
 */
namespace Phoenix {

class Commands;

typedef void (* execute)(WorldModel, std::vector<Message>, Commands*);
typedef void (* control)(void);

/*!
 * @defgroup core Phoenix Core Objects
 * @brief <STRONG> Phoenix2D Core Objects <BR> </STRONG>
 * The following namespace contains the following objects<BR>
 * 	<ul>
 *    <li>Controller</li>
 *	  <li>Connect</li>
 *	  <li>Reader</li>
 *	  <li>Server</li>
 *	  <li>Parser</li>
 *	  <li>Commands</li>
 *	  <li>World</li>
 *	  <li>Self</li>
 *	</ul> 
 * @{
 */

/*!
 * @brief <STRONG> Controller <BR> </STRONG>
 * The Controller is the Main Manager of the Phoenix2D Player. 
 * It is composed of references to the Main Objects in the Library. 
 * The Controller is in charge of instantiation of the rest of the inner 
 * objects using the user's parameters. 
 */
class Controller {
public:
	static char AGENT_TYPE; ///< p = Player, g = Goalie, c = Coach, t = Trainer
  /*! @brief Default Constructor
   * @param teamName User Defined Team Name
   * @param agentType see AGENT_TYPE
   * @param hostname ip address or host
   */
	Controller(const char *teamName, char agentType, const char *hostname);
  /*! @brief Default Destructor
   */
	~Controller();
  /*! @brief The main connection, should be called before anything
      else in Phoenix2D
   */
	void connect();
  /*! @return Connection Status Getter
   */
	bool isConnected();
	void registerSetupFunction(control function);
	void registerFinishFunction(control function);
  /*! @brief Player function register
   */
	void registerPlayerFunction(std::string play_mode, execute function);
  /*! @brief Goalie function register
   */
	void registerGoalieFunction(std::string play_mode, execute function);
  /*! @brief Coach function register
   */
	void registerCoachFunction(std::string play_mode, execute function);
  /*! @brief Run
   */
	void run();
  /*! @brief Reconnection Logic @todo Define Method
   */
	void reconnect();
  /*! @brief Disconnect service
   */
	void disconnect();
private:
	bool connected;         ///< Connection status
	std::string hostname;
};
/*! @} */
} // End namespace Phoenix
/*! @} */

#endif /* CONTROLLER_HPP_ */
