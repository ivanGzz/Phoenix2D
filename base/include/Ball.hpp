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
 * @file Ball.hpp
 *
 * @author Nelson I. Gonzalez
 */

#ifndef BALL_HPP_
#define BALL_HPP_

#include "Position.hpp"
#include "geometry.hpp"
#include "Object.hpp"
#include <string>

/*! @addtogroup phoenix_base
 * @{
 */
namespace Phoenix {

/*!
 * @brief <STRONG> Ball <BR> </STRONG>
 * The Ball contains information about the current state of the ball in the field.  A Ball object is
 * generated every new cycle and can be empty.  You must check isInSightRange() to know if the ball is
 * seen in the current cycle.
 */
class Ball : public Object {
public:
	/*!
	 * @brief Ball default constructor
	 */
	Ball();
	/*!
	 * @brief Ball default destructor
	 */
	~Ball();
	/*!
	 * @brief Init method for agent type coach
	 * @param position string received from the server in the see_global sensor
	 */
	void initForCoach(std::string position);
	/*!
	 * @brief Init method for agent type player
	 * @param position string received from the server in the see sensor
	 * @param player_position current agent position used to compute the absolute position for the ball
	 * @param player_velocity current agent velocity used to compute the absolute velocity for the ball
	 */
	void initForPlayer(std::string position, Position player_position, Geometry::Vector2D player_velocity);
	/*!
	 * @brief Init method for agent type player using fullstate sensor
	 * @param x ball absolute position in x
	 * @param y ball absolute position in y
	 * @param vx ball absolute velocity in x
	 * @param vy ball absolute velocity in y
	 */
	void initForFullstate(double x, double y, double vx, double vy);
	/*!
	 * @brief Initialization method for agent type player using a defined position
	 * @param position defined position
	 */
	void initForPosition(Position position);
	double distance;				///< raw value of ball relative distance
	double direction;				///< raw value of ball relative direction
	double dist_change;				///< raw value of ball relative distance change
	double dir_change;				///< raw value of ball relative direction change
};

} // End namespace Phoenix
/*! @} */


#endif /* BALL_HPP_ */
