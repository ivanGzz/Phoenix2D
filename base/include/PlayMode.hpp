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
 * @file PlayMode.hpp
 *
 * @author Nelson Ivan Gonzalez
 */

#ifndef PLAYMODE_HPP_
#define PLAYMODE_HPP_

#include "WorldModel.hpp"
#include <vector>
#include "Message.hpp"

/*! @addtogroup phoenix_base
 * @{
 */
namespace Phoenix {

class Commands;

/*!
 * @brief <STRONG> PlayMode <BR> </STRONG>
 * The PlayMode object is in charge of execute the given function
 */
class PlayMode {
public:
	/*!
	 * @brief PlayMode default constructor
	 * @param commands Pointer to Commands object
	 */
	PlayMode(Commands* commands);
	/*!
	 * @brief PlayMode default destructor
	 */
	~PlayMode();
	/*!
	 * @brief Executes setup function at the beginning of the simulation
	 * @param setup function to be executed
	 */
	void onStart(void(* setup)(void));
	/*!
	 * @brief it is executed at the beginning of a new cycle, it flushes the commands queue
	 */
	void onPreExecute();
	/*!
	 * @brief Executes the given function every simulation cycle
	 * @param world Current world model
	 * @param messages Messages received in the current cycle
	 * @param execute function to be executed
	 */
	void onExecute(WorldModel world, std::vector<Message> messages, void(* execute)(WorldModel, std::vector<Message>, Commands*));
	/*!
	 * @brief It is executed at the end of the current cycle, it actually sends the commands
	 */
	void onPostExecute();
	/*!
	 * @brief It executes the given function at the end of the simulation
	 * @param end function to be executed
	 */
	void onEnd(void(* end)(void));
private:
	Commands* commands;	///< Pointer to Commands object
};

} // End namespace Phoenix
/*! @} */

#endif /* PLAYMODE_HPP_ */
