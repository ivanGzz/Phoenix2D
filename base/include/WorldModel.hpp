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

#ifndef WORLDMODEL_HPP_
#define WORLDMODEL_HPP_

#include <vector>
#include "Player.hpp"
#include "Ball.hpp"

/*! @addtogroup phoenix_main
 * @{
 */
namespace Phoenix {

 /*!
 * @brief <STRONG> WorldModel <BR> </STRONG>
 * The WorldModel lorem Ipsum
 */
class WorldModel {
	std::vector<Player> players;
	Ball ball;
public:
	WorldModel(std::vector<Player> players, Ball ball);
	~WorldModel();
	std::vector<Player*> getPlayers();
	std::vector<Player*> getPlayersOrderedByDistanceTo(Position position);
	std::vector<Player*> getOurPlayers();
	std::vector<Player*> getOurPlayersOrderedByDistanceTo(Position position);
	std::vector<Player*> getOppPlayers();
	std::vector<Player*> getOppPlayersOrderedByDistanceTo(Position position);
	std::vector<Player*> getUndPlayers();
	std::vector<Player*> getUndPlayersOrderedByDistanceTo(Position position);
	Ball* getBall();
};

} // End namespace Phoenix
/*! @} */

#endif /* WORLDMODEL_HPP_ */
