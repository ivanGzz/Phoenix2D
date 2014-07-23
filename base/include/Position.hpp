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
 * @file Position.hpp
 *
 * @author Nelson Ivan Gonzalez
 */

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <string>
#include "geometry.hpp"

/*! @addtogroup phoenix_base
 * @{
 */
namespace Phoenix {

/*!
 * @brief <STRONG> Position <BR> </STRONG>
 * A Position object stores information about the absolute position of an object
 * inside the field.  It also includes information about the body direction and
 * head direction for player objects.
 */
class Position {
public:
	double x;		///< Absolute position in x
	double y;		///< Absolute position in y
	double body;	///< Absolute body direction for players
	double neck;	///< Relative head direction for players
	/*!
	 * @brief Position constructor with x, y, body direction and head direction as arguments
	 * @param x Absolute coordinate in x
	 * @param y Absolute coordinate in y
	 * @param body Absolute body direction for players
	 * @param neck Relative head direction for players
	 */
	Position(double x = 0.0, double y = 0.0, double body = 0.0, double neck = 0.0);
	/*!
	 * @brief Position constructor with Point argument
	 * @param point Absolute point
	 */
	Position(Geometry::Point point);
	/*!
	 * @brief Position default destructor
	 */
	~Position();
	/*!
	 * @brief Returns The euclidean distance between this position and the provided position
	 * @param position Position to compute the distance
	 * @return Distance to the given position
	 */
	double getDistanceTo(Position* position) const;
	/*!
	 * @brief Returns the relative direction from this position to the provided position
	 * @param position Position to compute the direction
	 * @return Relative direction to the provided position
	 * This method uses the body direction of the source, in consequence, this
	 * method should not be used with Ball objects.  Disclaimer: this method always
	 * returns the direction relative to the body, never to the head.
	 */
	double getDirectionTo(Position* position) const;
	/*!
	 * @brief Returns point primitive created with the absolute positions
	 * @return Absolute point structure for this position
	 */
	Geometry::Point getPoint() const;
	/*!
	 * @brief Multiply by -1 the absolute position in x and y
	 */
	void mirror();
	/*!
	 * @brief Returns the absolute position in x
	 * @return Absolute position in x
	 */
	double getX() const;
	/*!
	 * @brief Returns the absolute position in y
	 * @return Absolute position in y
	 */
	double getY() const;
	/*!
	 * @brief Returns the absolute direction for player objects
	 * @return Absolute direction
	 */
	double getDirection() const;
};

} // End namespace Phoenix
/*! @} */

#endif /* POSITION_HPP_ */
