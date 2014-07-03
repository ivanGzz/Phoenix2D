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
	/*
	 */
	Ball();
	~Ball();
	void initForCoach(std::string position);
	void initForPlayer(std::string position, const Position* player_position, const Geometry::Vector2D* player_velocity);
	void initForFullstate(double x, double y, double vx, double vy);
	Position* getPosition();
	Geometry::Vector2D* getVelocity();
	bool isInSightRange();
private:
	double distance;
	double direction;
	double distChange;
	double dirChange;
	double x;
	double y;
	double vx;
	double vy;
	Position position;
	Geometry::Vector2D velocity;
	bool in_sight_range;
};

} // End namespace Phoenix
/*! @} */


#endif /* BALL_HPP_ */
