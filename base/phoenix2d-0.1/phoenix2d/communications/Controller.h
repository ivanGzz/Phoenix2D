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

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <string>

/*!
 * @defgroup phoenix_main Phoenix Library Namespace
 * @brief <STRONG> Phoenix2D Master <BR> </STRONG>
 * The namespace that contains everything elated to the Phoenix Library
 * @{
 */
namespace Phoenix
{

class Connect;
class Reader;
class Server;
class Parser;
class Commands;
class World;
class Self;

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
class Controller 
{
public:
	static char AGENT_TYPE; ///< p = Player, t = Trainer
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
  /*! @brief Reconnection Logic @todo Define Method
   */
	void reconnect();
  /*! @brief Disconnect service
   */
	void disconnect();
  /*! @brief Commands getter
   */
	Commands* getCommands();
  /*! @brief World getter
   */
	World* getWorld();
  /*! @brief Self getter
   */	
  Self* getSelf();
private:
	Parser* parser;         ///< Pointer to inner Parser Object
	Connect* c;             ///< Pointer to inner Connect Object
	Reader* reader;         ///< Pointer to inner Reader Object
	Server* server;         ///< Pointer to inner Server Object
	Commands* commands;     ///< Pointer to inner Commans Object
	World* world;           ///< Pointer to inner World Object
	Self* self;             ///< Pointer to inner Self Object
	bool connected;         ///< Connection status
	std::string team_name;
	std::string hostname;
};

} // End namespace Phoenix
/*! @} */

#endif /* CONTROLLER_H_ */
