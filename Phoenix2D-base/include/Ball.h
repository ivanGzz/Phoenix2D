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

#ifndef BALL_H_
#define BALL_H_

#include <string>
#include "Position.h"
#include "Vector2D.h"

/*! @addtogroup phoenix_main
 * @{
 */
namespace Phoenix
{

 /*!
 * @brief <STRONG> Ball <BR> </STRONG>
 * The Ball lorem Ipsum
 */
class Ball {
	double distance;
	double direction;
	double distChange;
	double dirChange;
	double x;
	double y;
	double vx;
	double vy;
	int simulation_time;
	bool in_sight_range;
	Ball* bound;
public:
	Ball();
	Ball(int simulation_time);
	Ball(std::string position, int simulation_time);
	Ball(std::string position, int simulation_time, Position player_position, Vector2D player_velocity);
	~Ball();
	Position getPosition();
	Vector2D getVelocity();
	bool isInSightRange();
	void boundTo(Ball* ball);
	Ball* getBound();
};

} // End namespace Phoenix
/*! @} */


#endif /* BALL_H_ */
