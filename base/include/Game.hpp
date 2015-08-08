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
 * @file Game.hpp
 *
 * @author Nelson I. Gonzalez
 */

#ifndef GAME_HPP_
#define GAME_HPP_

#include <string>

/*! @addtogroup phoenix_base
 * @{
 */
namespace Phoenix {

/*!
 * @brief <STRONG> Game <BR> </STRONG>
 * The Game object stores information about the current status of the game.  It
 * also synchronize the main thread with the server through the Game::nextCycle()
 * method.
 */
namespace Game {

	unsigned int SIMULATION_TIME;	///< Current simulation time
	unsigned int GAME_TIME;			///< Current game time, it does not run in before_kick_off play mode
	unsigned int GOALS;				///< Current goals scored
	unsigned int GOALS_AGAINST;		///< Current goals against
	std::string PLAY_MODE;			///< Current play mode
	/*!
	 * @brief returns true if there is a new cycle and false otherwise
	 * This method is blocking and it is used by the method Controller::run()
	 * to start a new cycle.
	 */
	bool nextCycle();
	/*!
	 * @brief Update the game time and the simulation time
	 * @param game_time current game time sent by the server
	 */
	void updateTime(int game_time);
	/*!
	 * @brief It unlocks the Game::nextCycle() method
	 */
	void onNextCycle(); // int game_time);
	/*!
	 * @brief Update the current play mode
	 * @param play_mode new play mode sent by the server
	 */
	void updatePlayMode(std::string play_mode);

}

} // End namespace Phoenix
/*! @} */

#endif /* GAME_HPP_ */
