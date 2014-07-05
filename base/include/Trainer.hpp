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
 * @file Trainer.hpp
 *
 * @author Nelson Ivan Gonzalez
 */

#ifndef TRAINER_HPP_
#define TRAINER_HPP_

#include "WorldModel.hpp"
#include <vector>
#include "Message.hpp"
#include <string>

/*! @addtogroup phoenix_base
 * @{
 */
namespace Phoenix {

class Commands;

 /*!
 * @brief <STRONG> Trainer <BR> </STRONG>
 * The Trainer object is used to automate the trainer loading a script file.  The script file
 * is converted to action to be performed every simulation cycle until the simulation end.
 */
class Trainer {
public:
	/*!
	 * @brief Trainer default constructor
	 * @param commands Pointer to Commands object
	 */
	Trainer(Commands *commands);
	/*!
	 * @brief Trainer default destructor
	 */
	~Trainer();
	/*!
	 * @brief Load script file
	 * @param trainer Path for the script file
	 */
	bool load(std::string trainer);
	/*!
	 * @brief Executes a single line converted from the script file
	 * @param world The current world model
	 * @param messages A list of messages received in the current cycle
	 */
	void execute(WorldModel world, std::vector<Message> messages);
	/*!
	 * @brief Returns true if the execution must continue or false if the simulation must end
	 */
	bool continueExecution();
private:
	Commands *commands;	///< Pointer to Commands object
	bool newExecution;	///< If true the execution must continue, false otherwise
};

} // End namespace Phoenix
/*! @} */

#endif /* TRAINER_HPP_ */
