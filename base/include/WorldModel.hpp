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
 * @file WorldModel.hpp
 *
 * @author Nelson Ivan Gonzalez
 */

#ifndef WORLDMODEL_HPP_
#define WORLDMODEL_HPP_

#include <vector>
#include "Player.hpp"
#include "Ball.hpp"

/*! @addtogroup phoenix_base
 * @{
 */
namespace Phoenix {

 /*!
 * @brief <STRONG> WorldModel <BR> </STRONG>
 * A WorldModel object stores information about the current state of the world.  It includes information
 * about players and the ball received in the see sensor along with information about players and the ball
 * received in the full state sensor.
 */
class WorldModel {
public:
	/*!
	 * @brief Constructor deprecated
	 * @param players List of current players received in the see sensor
	 * @param ball Ball object received in the see sensor
	 */
	WorldModel(std::vector<Player> players, Ball ball);
	/*!
	 * @brief WorldModel constructor
	 * @param players List of current players received in the see sensor
	 * @param ball Ball object received in the see sensor
	 * @param fs_player List of current players received in the full state sensor
	 * @param fs_ball Ball object received in the full state sensor
	 */
	WorldModel(std::vector<Player> players, Ball ball, std::vector<Player> fs_player, Ball fs_ball);
	/*!
	 * @brief WorldModel default destructor
	 */
	~WorldModel();
	/*!
	 * @brief Returns list of all current players
	 * @return List of all players
	 */
	std::vector<Player*> getPlayers();
	/*!
	 * @brief Returns list of all current players ordered from nearest to farthest in function of the position
	 * @param position Position anchor to order the players
	 * @return List of all players ordered by distance
	 */
	std::vector<Player*> getPlayersOrderedByDistanceTo(Position position);
	/*!
	 * @brief Returns list of players of the same team
	 * @return List of players of the same team
	 */
	std::vector<Player*> getOurPlayers();
	/*!
	 * @brief Returns list of players of the same team ordered from nearest to farthest in function of the position
	 * @param position Position anchor to order the players
	 * @return List of players of the same team ordered by distance
	 */
	std::vector<Player*> getOurPlayersOrderedByDistanceTo(Position position);
	/*!
	 * @brief Returns list of players of the opponent team
	 * @return List of players of the opponent team
	 */
	std::vector<Player*> getOppPlayers();
	/*!
	 * @brief Returns list of players of the opponent team ordered from nearest to farthest in function of the position
	 * @param position Position anchor to order the players
	 * @return List of players of the opponent team ordered by distance
	 */
	std::vector<Player*> getOppPlayersOrderedByDistanceTo(Position position);
	/*!
	 * @brief Returns list of players with undefined team
	 * @return List of players of unknown team
	 */
	std::vector<Player*> getUndPlayers();
	/*!
	 * @brief Returns list of players with undefined team ordered from nearest to farthest in function of the position
	 * @param position Position anchor to order the players
	 * @return List of players of unknown team ordered by distance
	 */
	std::vector<Player*> getUndPlayersOrderedByDistanceTo(Position position);
	/*!
	 * @brief Returns player from the same team with the uniform number from the full state sensor
	 * @param unum Uniform number to search
	 * @return Player of the same team with given uniform number
	 * This method returns the player with the given number iff the full state sensor is enabled and
	 * the player is connected to the server
	 */
	Player* getOurExactPlayer(int unum);
	/*!
	 * @brief Returns the list of all players received in the full state sensor
	 * @return List of all players
	 * This method returns all the players iff the state sensor is enabled
	 */
	std::vector<Player*> getAllExactPlayers();
	/*!
	 * @brief Returns player from the opponent team with the uniform number from the full state sensor
	 * @param unum Uniform number to search
	 * @return Player of the opponent team with given uniform number
	 * This method returns the player with the given number iff the full state sensor is enabled and
	 * the player is connected to the server
	 */
	Player* getOppExactPlayer(int unum);
	/*!
	 * @brief Return pointer to the Ball object received in the see sensor
	 * @return Pointer to ball object
	 */
	Ball* getBall();
	/*!
	 * @brief Returns pointer to the Ball object received in the full state sensor
	 * @return Pointer to ball object
	 * This method returns the ball with exact data iff the full state sensor is enabled
	 */
	Ball* getExactBall();
private:
	std::vector<Player> players;	///< Current player in the see sensor
	std::vector<Player> fs_players;	///< Current player in the full state sensor
	Ball ball;						///< Current ball in the see sensor
	Ball fs_ball;					///< Current ball in the full state sensor
	Player ours[12];				///< Players of the same team ordered by uniform number
	Player opps[12];				///< Players of the opponent team ordered by uniform number
};

} // End namespace Phoenix
/*! @} */

#endif /* WORLDMODEL_HPP_ */
