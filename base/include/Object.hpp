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
 * @file Object.hpp
 *
 * @author Nelson I. Gonzalez
 */

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include "Position.hpp"
#include "geometry.hpp"

/*! @addtogroup phoenix_base
 * @{
 */
namespace Phoenix {

/*!
 * @brief <STRONG> OBJECT_STATUS <BR> </STRONG>
 * The object status refers to the current status for the object.
 */
enum OBJECT_STATUS {
	LOST,		///< Object position is unknown
	COMM,		///< Object position has been communicated
	INFERRED,	///< Object position is inferred
	POSITION,	///< Only the object position is known
	LOCALIZED	///< The object position and object velocity are known
}

/*!
 * @brief <STRONG> Command <BR> </STRONG>
 * The Object object is the abstract type for players, flags and the ball. It includes
 * common methods for dynamic and static objects such as position and velocity. This
 * class is meant to be always inherited.
 */
class Object : public Position {
protected:
	double _vx;				///< Velocity component in x
	double _vy;				///< Velocity component in y
	OBJECT_STATUS _status;	///< Current object localization status
public:
	/*!
	 * @brief Object default constructor
	 */
	Object();
	/*!
	 * @brief Object default destructor
	 */
	~Object();
	/*!
	 * @brief Gets the current object position
	 * @return The current object position
	 */
	Position position();
	/*!
	 * @brief
	 */
	void setPosition(Position position);
	/*!
	 * @brief Gets the current object velocity
	 * @return The current object velocity
	 */
	Geometry::Vector2D velocity();
	/*!
	 * @brief
	 */
	void setVelocity(Geometry::Vector2D new_velocity);
	/*!
	 * @brief Gets the inferred position time cycles ahead of the current cycle
	 * @param time Cycles ahead to compute the position
	 */
	Position positionAtTime(int time);
	/*!
	 * @brief Gets the current object localization status
	 * @return Object localization status
	 */
	OBJECT_STATUS status();
	/*!
	 * @brief Sets the current object localization status
	 * @param status The new object localization status
	 */
	void setStatus(OBJECT_STATUS status);
};

} // End namespace Phoenix
/*! @} */

#endif /* BALL_HPP_ */