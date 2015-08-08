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
 * @file World.hpp
 *
 * @author Nelson I. Gonzalez
 */

#ifndef WORLD_HPP_
#define WORLD_HPP_

#include <list>
#include "Player.hpp"
#include "Ball.hpp"
#include "WorldModel.hpp"

/*! @addtogroup phoenix_base
 * @{
 */
namespace Phoenix {

/*!
 * @brief <STRONG> World <BR> </STRONG>
 * The World object stores the information about the current state of the world.  It also
 * includes routines to perform object track and object linking.
 */
namespace World {

	/*!
	 * @brief Update the world model with the new information received in the see sensor
	 * @param players List of current players received in the see sensor
	 * @param ball Ball object containing information about the ball received in the see sensor
	 * @param fs_players List of players received in the full state sensor
	 * @param fs_ball ball object received in the full state sensor
	 */
	void updateWorld(std::list<Player> players, Ball ball, std::list<Player> fs_players, Ball fs_ball, bool on_see);
	/*!
	 * @brief Returns the current world model
	 * @return Current world model
	 */
	WorldModel worldModel();
	/*!
	 * @brief 
	 */
	void decode(std::string message);
	/*!
	 * @brief
	 */
	std::string encode();
	
}

} // End namespace Phoenix
/*! @} */


#endif /* WORLD_HPP_ */
