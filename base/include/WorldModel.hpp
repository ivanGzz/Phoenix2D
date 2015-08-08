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
 * @file WorldModel.hpp
 *
 * @author Nelson I. Gonzalez
 */

#ifndef WORLDMODEL_HPP_
#define WORLDMODEL_HPP_

#include <list>
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
	 * @brief WorldModel constructor
	 * @param players List of current players received in the see sensor
	 * @param ball Ball object received in the see sensor
	 * @param fs_player List of current players received in the full state sensor
	 * @param fs_ball Ball object received in the full state sensor
	 * @param current Indicates if the information was currently received in the see sensor
	 */
	WorldModel(std::list<Player> players, Ball ball, std::list<Player> fs_player, Ball fs_ball, bool current = false);
	/*!
	 * @brief WorldModel default destructor
	 */
	~WorldModel();
	/*!
	 * @brief Returns list of all current players
	 * @return List of all players
	 */
	std::list<Player*> players();
	/*!
	 * @brief Returns list of all current players ordered from nearest to farthest in function of the position
	 * @param position Position anchor to order the players
	 * @return List of all players ordered by distance
	 */
	std::list<Player*> playersOrderedByDistanceTo(Position position);
	/*!
	 * @brief Returns list of players of the same team
	 * @return List of players of the same team
	 */
	std::list<Player*> ourPlayers();
	/*!
	 * @brief Returns list of players of the same team ordered from nearest to farthest in function of the position
	 * @param position Position anchor to order the players
	 * @return List of players of the same team ordered by distance
	 */
	std::list<Player*> ourPlayersOrderedByDistanceTo(Position position);
	/*!
	 * @brief Returns list of players of the opponent team
	 * @return List of players of the opponent team
	 */
	std::list<Player*> oppPlayers();
	/*!
	 * @brief Returns list of players of the opponent team ordered from nearest to farthest in function of the position
	 * @param position Position anchor to order the players
	 * @return List of players of the opponent team ordered by distance
	 */
	std::list<Player*> oppPlayersOrderedByDistanceTo(Position position);
	/*!
	 * @brief Returns list of players with undefined team
	 * @return List of players of unknown team
	 */
	std::list<Player*> undPlayers();
	/*!
	 * @brief Returns list of players with undefined team ordered from nearest to farthest in function of the position
	 * @param position Position anchor to order the players
	 * @return List of players of unknown team ordered by distance
	 */
	std::list<Player*> undPlayersOrderedByDistanceTo(Position position);
	/*!
	 * @brief Returns player from the same team with the uniform number from the full state sensor
	 * @param unum Uniform number to search
	 * @return Player of the same team with given uniform number
	 * This method returns the player with the given number iff the full state sensor is enabled and
	 * the player is connected to the server
	 */
	Player* ourExactPlayer(int unum);
	/*!
	 * @brief Returns the list of all players received in the full state sensor
	 * @return List of all players
	 * This method returns all the players iff the state sensor is enabled
	 */
	std::list<Player*> exactPlayers();
	/*!
	 * @brief Returns player from the opponent team with the uniform number from the full state sensor
	 * @param unum Uniform number to search
	 * @return Player of the opponent team with given uniform number
	 * This method returns the player with the given number iff the full state sensor is enabled and
	 * the player is connected to the server
	 */
	Player* oppExactPlayer(int unum);
	/*!
	 * @brief Return pointer to the Ball object received in the see sensor
	 * @return Pointer to ball object
	 */
	Ball* ball();
	/*!
	 * @brief Returns pointer to the Ball object received in the full state sensor
	 * @return Pointer to ball object
	 * This method returns the ball with exact data iff the full state sensor is enabled
	 */
	Ball* exactBall();
	/*!
	 * @brief 
	 */
	bool current();
	int real_matches;
	int method_matches;
	int correct_matches;
private:
	std::list<Player> _players;		///< Current player in the see sensor
	std::list<Player> _fs_players;	///< Current player in the full state sensor
	std::list<Player*> _all_players;
	std::list<Player*> _ours;
	std::list<Player*> _opps;
	std::list<Player*> _unds;
	Ball _ball;						///< Current ball in the see sensor
	Ball _fs_ball;					///< Current ball in the full state sensor
	Player _ours[12];				///< Players of the same team ordered by uniform number
	Player _opps[12];				///< Players of the opponent team ordered by uniform number
	bool _current;					///< If true then the world model is the current world model received in the see sensor, false otherwise
};

} // End namespace Phoenix
/*! @} */

#endif /* WORLDMODEL_HPP_ */
