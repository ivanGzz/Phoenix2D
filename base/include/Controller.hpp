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
 * @file Controller.hpp
 * 
 * @author Nelson Ivan Gonzalez
 */

#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include <string>
#include <vector>
#include "WorldModel.hpp"
#include "Message.hpp"

/*! @addtogroup phoenix_base
 * @{
 */
namespace Phoenix {

class Commands;

/*!
 * @typedef
 * @brief Function signatures for play modes function
 */
typedef void (* execute)(WorldModel, std::vector<Message>, Commands*);
/*!
 * @typedef
 * @brief Function signature for setup and finish function
 */
typedef void (* control)(void);

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
	/*!
	 * @brief Controller default Constructor
     * @param teamName User Defined Team Name
     * @param agentType see AGENT_TYPE
     * @param hostname ip address or host
     */
	Controller(std::string teamName, char agentType, std::string hostname);
	/*!
	 * @brief Controller default Destructor
     */
	~Controller();
	/*!
	 * @brief The main connection, should be called before anything else in Phoenix2D
     */
	void connect();
	/*!
	 * @return Connection status
     */
	bool isConnected();
	/*!
	 * @brief Register the function to be executed before the simulation start
	 * This method should be used to setup the necessary data structures to be used by the
	 * intelligent agent.
	 */
	void registerSetupFunction(control function);
	/*!
	 * @brief Register the function to be executed at the end of the simulation
	 * This method should be used to release resources used during the simulation, such as
	 * dynamic memory, files, services, etc.
	 */
	void registerFinishFunction(control function);
	/*!
	 * @brief Player play mode function register
     */
	void registerPlayerFunction(std::string play_mode, execute function);
	/*!
	 * @brief Goalie play mode function register
     */
	void registerGoalieFunction(std::string play_mode, execute function);
	/*!
	 * @brief Coach play mode function register
     */
	void registerCoachFunction(std::string play_mode, execute function);
	/*!
	 * @brief Trainer script register
	 * @param trainer
     */
	void registerTrainerScript(std::string trainer);
	/*!
	 * @brief Runs the main thread of execution
	 */
	void run();
	/*!
	 * @brief Reconnect a previously disconnected agent
     */
	void reconnect();
	/*! @brief Disconnect from the server
     */
	void disconnect();
private:
	bool connected;         ///< Connection status
	std::string hostname;	///< Host to connect
};

} // End namespace Phoenix
/*! @} */

#endif /* CONTROLLER_HPP_ */
