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
 * @file Ball.cpp
 *
 * @author Nelson Ivan Gonzalez
 */

#ifndef BALL_HPP_
#define BALL_HPP_

#include <string>
#include "Position.hpp"
#include "geometry.hpp"

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
class Ball {
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
	void initForPlayer(std::string position, const Position* player_position, const Geometry::Vector2D* player_velocity);
	/*!
	 * @brief Init method for agent type player using fullstate sensor
	 * @param x ball absolute position in x
	 * @param y ball absolute position in y
	 * @param vx ball absolute velocity in x
	 * @param vy ball absolute velocity in y
	 */
	void initForFullstate(double x, double y, double vx, double vy);
	/*!
	 * @brief Returns the current ball absolute position in a Position pointer
	 */
	Position* getPosition();
	/*!
	 * @brief Return the current ball absolute velocity in a Vector2D pointer
	 * @return Pointer to ball velocity
	 */
	Geometry::Vector2D* getVelocity();
	/*!
	 * @brief Returns true is the ball is in the vision range in the current cycle, and false otherwise
	 * @return true if the ball is in the vision range, false otherwise
	 */
	bool isInSightRange();
private:
	double distance;				///< ball relative distance
	double direction;				///< ball relative direction
	double distChange;				///< ball relative distance change
	double dirChange;				///< ball relative direction change
	double x;						///< computed ball position in x
	double y;						///< computed ball position in y
	double vx;						///< computed ball velocity in x
	double vy;						///< computed ball velocity in y
	Position position;				///< computed ball absolute position using x and y
	Geometry::Vector2D velocity;	///< computed ball absolute velocity using vx and vy
	bool in_sight_range;			///< boolean indicating if the ball is in the vision sensor
};

} // End namespace Phoenix
/*! @} */


#endif /* BALL_HPP_ */
