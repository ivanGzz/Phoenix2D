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
 */

#ifndef GAME_H_
#define GAME_H_

#include <string>


/*! @addtogroup phoenix_main
 * @{
 */
namespace Phoenix
{
/*!
 * @brief <STRONG> Game <BR> </STRONG>
 * The Game lorem Ipsum
 */
class Game {
public:
	static unsigned int SIMULATION_TIME;
	static unsigned int GAME_TIME;
	static unsigned int GOALS;
	static unsigned int GOALS_AGAINST;
	static std::string PLAY_MODE;
	static bool nextCycle();
	Game();
	~Game();
	void updateTime(int game_time);
	void updatePlayMode(std::string play_mode);
};
} // End namespace Phoenix
/*! @} */

#endif /* GAME_H_ */
