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
 * @file Player.hpp
 *
 * @author Nelson Ivan Gonzalez
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <string>
#include <vector>
#include "Position.hpp"
#include "geometry.hpp"

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
class Player {
friend class World;
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
	void initForPlayer(const Position* player_position, const Geometry::Vector2D* player_velocity);
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
	 * @brief Returns the current player absolute position in a Position pointer
	 * @return Pointer to player position
	 */
	Position* getPosition();
	/*!
	 * @brief Returns the team name of the player if available, returns "undefined" otherwise
	 * @return Player team name
	 */
	std::string getTeam();
	/*!
	 * @brief Returns the uniform number of the player if available, return 0 otherwise
	 * @return Player uniform number
	 */
	int getUniformNumber();
	/*!
	 * @brief Return the current ball absolute velocity in a Vector2D pointer
	 * @return Pointer to player velocity
	 */
	Geometry::Vector2D* getVelocity();
	/*!
	 * @brief Returns true if the seen player is a goalie
	 * @return True if the player is goalie and false otherwise
	 */
	bool isGoalie();
	/*!
	 * @brief Returns true if the player is pointing in the current cycle
	 * @return True if the player is pointing and false otherwise
	 */
	bool isPointing();
	/*!
	 * @brief Returns the relative direction of the arm when the player is pointing
	 * @return Relative direction the player is pointing to
	 */
	double getPointingDirection();
	/*!
	 * @brief Returns true if the player is kicking in the current cycle
	 * @return True if the player is kicking and false otherwise
	 */
	bool isKicking();
	/*!
	 * @brief Returns true if the player is tackling in the current cycle
	 * @return True if the playee is tackling and false otherwise
	 */
	bool isTackling();
	/*!
	 * @brief Returns the players id
	 * @return Player id
	 */
	int getPlayerId();
	/*!
	 * @brief Toggle the property is_in_sight_range from false to true or from true to false
	 */
	void toggleSightRange();
	/*!
	 * @brief Returns true if the player is in the vision sensor
	 * @return True if the player is in the vision range and false otherwise
	 */
	bool isInSightRange();
	/*!
	 * @brief Returns the player distance error
	 * @return Player distance error
	 */
	double getDistanceError();
	double getMatchValue();
private:
	double distance;				///< Player relative distance in the see sensor
	double direction;				///< Player relative direction in the see sensor
	double distChange;				///< Player relative distance change
	double dirChange;				///< Player relative direction change
	double bodyDirection;			///< Player relative body direction
	double headDirection;			///< Player relative head direction
	double pointDir;				///< Player relative pointing direction
	double x;						///< Player absolute position in x
	double y;						///< Player absolute position in y
	double body;					///< Player absolute body direction
	double head;					///< Player relative head direction
	double vx;						///< Player absolute velocity in x
	double vy;						///< Player absolute velocity in y
	bool has_body;					///< True if the see sensor returned a body direction value
	bool has_head;					///< True if the see sensor returned a head direction value
	bool pointing;					///< True if the see sensor returned a pointing direction value
	bool kicking;					///< True if the see sensor returned a kicking value
	bool tackling;					///< True if the see sensor returned a tackling value
	std::string team;				///< Team name of the player, "undefined" if not available
	int uniform_number;				///< Uniform number of the player, 0 if not available
	bool goalie;					///< True if the player is a goalie
	int player_id;					///< Player id
	bool is_in_sight_range;			///< True if the player is in the current visual sensor
	Position position;				///< Current player absolute position
	Geometry::Vector2D velocity;	///< Current player absolute velocity
	double error;					///< Player distance error
	bool vel;						///< Flag for velocity information received
	int ttl;						///< Time to live in memory for this player
	bool tracked;					///< True if this object has been matched with a new Player object
	double match;					///< Match value
};

} // End namespace Phoenix
/*! @} */

#endif /* PLAYER_HPP_ */
