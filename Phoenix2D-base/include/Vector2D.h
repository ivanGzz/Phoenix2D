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

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <string>

/*! @addtogroup phoenix_main
 * @{
 */
namespace Phoenix
{

 /*!
 * @brief <STRONG> VECTOR_TYPE <BR> </STRONG>
 * The Vector Type lorem Ipsum
 */
enum VECTOR_TYPE {
	EMPTY_V,	///< Empty Type
	V2D			///< Vector 2D
};

 /*!
 * @brief <STRONG> Vector2D <BR> </STRONG>
 * The Vector2D lorem Ipsum
 */
class Vector2D {
	double dx;
	double dy;
	double magnitude;
	double direction;
	VECTOR_TYPE type;
	//Vector2D(double magnitude, double direction);
public:
	Vector2D();
	Vector2D(double x, double y);
	static Vector2D getEmptyVector();
	static Vector2D getVector2DWithXAndY(double dx, double dy);
	static Vector2D getVector2DWithMagnitudeAndDirection(double magnitude, double direction);
	~Vector2D();
	double getXComponent();
	double getYComponent();
	double getMagnitude();
	double getDirection();
	Vector2D operator +(Vector2D vector);
	Vector2D operator *(double scalar);
	std::string toString();
	VECTOR_TYPE getType();
};
} // End namespace Phoenix
/*! @} */

#endif /* VECTOR2D_H_ */
