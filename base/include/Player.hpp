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
 * @file Player.hpp
 *
 * @author Nelson I. Gonzalez
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <string>
#include <vector>
#include "Position.hpp"
#include "geometry.hpp"
#define FAR '('

/*! @addtogroup phoenix_base
 * @{
 */
namespace Phoenix {

/*!
 * @brief <STRONG> Player <BR> </STRONG>
 * A Player object stores information about a single player in the visual sensor.  A Player
 * object is generated every time a new player is detected in the visual sensor.  If player history
 * is enabled then the player can be in sight range or not, you can check this property with the
 * isInSightRange method.
 */
class Player : public Object {
public:
	/*!
	 * @brief Player default constructor
	 */
	Player();
	/*!
	 * @brief Player default destructor
	 */
	~Player();
	/*!
	 * @brief Set the necessary data for the player to be created
	 * @param name Name string received from the server in the see sensor
	 * @param data Position string received from the server in the see sensor
	 * This method just parse the information as is received from the server, and then the
	 * player is initialized in the iniForPlayer method
	 */
	void setDataForPlayer(std::string name, std::string data);
	/*!
	 * @brief Init method for agent type player and goalie
	 * @param player_position current agent position used to compute the absolute position for the ball
	 * @param player_velocity current agent velocity used to compute the absolute velocity for the ball
	 */
	void initForPlayer(Position player_position, Geometry::Vector2D player_velocity);
	/*!
	 * @brief Init method for agent type coach
	 * @param name Name string received from the server in the see_global sensor
	 * @param data Position string received from the server in the see global sensor
	 */
	void initForCoach(std::string name, std::string data);
	/*!
	 * @brief Init method for agent type player and goalie using the fullstate sensor
	 * @param team Team name for the player
	 * @param unum Uniform number for the player
	 * @param x Player absolute position in x
	 * @param y Player absolute position in y
	 * @param vx Player absolute velocity in x
	 * @param vy Player absolute velocity in y
	 * @param b Player absolute body direction
	 * @param n Player relative neck direction
	 */
	void initForFullstate(std::string team, int unum, double x, double y, double vx, double vy, double b, double n);
	/*!
	 * @brief Decode a position used in the world model communication protocol
	 * @param from Position zero for the encoding position
	 * @param position Relative position of the player
	 * @param our True if the player is from the same team, false otherwise
	 */
	void decode(Position from, char position, bool our);
	/*!
	 * @brief Encode the relative position for use in the world model communication protocol
	 * @return A char representing the relative position
	 */
	char encode();
	/*!
	 * @brief Returns the team name of the player if available, returns "undefined" otherwise
	 * @return Player team name
	 */
	std::string team();
	/*!
	 * @brief Sets the team
	 * @param team The team can be our or opp
	 */
	void setTeam(std::string team);
	/*!
	 * @brief Returns the real team name of the player when the player is initialized with the full-state sensor
	 * @return Player team name
	 */
	std::string realTeam();
	/*!
	 * @brief
	 */
	void setRealTeam(std::string real_team);
	/*!
	 * @brief Returns the uniform number of the player if available, return 0 otherwise
	 * @return Player uniform number
	 */
	int uniformNumber();
	/*!
	 * @brief
	 */
	void setUniformNumber();
	/*!
	 * @brief Returns the real uniform number of the player when the player is initialized with the full-state sensor
	 * @return Player uniform number
	 */
	int realUniformNumber();
	/*!
	 * @brief
	 */
	void setRealUniformNumber(int real_unum);
	/*!
	 * @brief Returns true if the player is a goalie
	 * @return True if the player is goalie and false otherwise
	 */
	bool goalie();
	/*!
	 * @brief Returns true if the player is pointing in the current cycle
	 * @return True if the player is pointing and false otherwise
	 */
	bool pointing();
	/*!
	 * @brief Returns the relative direction of the arm when the player is pointing
	 * @return Relative direction the player is pointing to
	 */
	double pointingDirection();
	/*!
	 * @brief Returns true if the player is kicking in the current cycle
	 * @return True if the player is kicking and false otherwise
	 */
	bool kicking();
	/*!
	 * @brief Returns true if the player is tackling in the current cycle
	 * @return True if the playee is tackling and false otherwise
	 */
	bool tackling();
	/*!
	 * @brief Returns the players id
	 * @return Player id
	 */
	int playerId();
	/*!
	 * @brief Sets the players id
	 * @param id Player id
	 */
	void setPlayerId(int id);
	/*!
	 * @brief Returns the player distance error
	 * @return Player distance error
	 */
	double distanceError();
	double distance;				///< raw player relative distance in the see sensor
	double direction;				///< raw player relative direction in the see sensor
	double dist_change;				///< raw player relative distance change
	double dir_change;				///< raw player relative direction change
	double body_direction;			///< raw player relative body direction
	double head_direction;			///< raw player relative head direction
	double point_dir;				///< raw player relative pointing direction
	bool has_body;					///< True if the see sensor returned a body direction value
	bool has_head;					///< True if the see sensor returned a head direction value
	int ttl;						///< Time to live in memory for this player
	bool tracked;					///< True if this object has been matched with a new Player object
	double match;					///< Match value
private:
	bool _is_pointing;				///< True if the see sensor returned a pointing direction value
	bool _is_kicking;				///< True if the see sensor returned a kicking value
	bool _is_tackling;				///< True if the see sensor returned a tackling value
	bool _is_goalie;				///< True if the player is a goalie
	std::string _team;				///< Team name of the player, "undefined" if not available
	int _uniform_number;			///< Uniform number of the player, 0 if not available
	int _player_id;					///< Player id
	double _error;					///< Player distance error
	int _real_uniform_number;		///< Real uniform number when checking with full state sensor
	std::string _real_team;			///< Real team when checking with full state sensor
};

} // End namespace Phoenix
/*! @} */

#endif /* PLAYER_HPP_ */
