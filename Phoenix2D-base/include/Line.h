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

#ifndef LINE_H_
#define LINE_H_

#include <string>

/*! @addtogroup phoenix_main
 * @{
 */
namespace Phoenix
{
/*!
 * @brief <STRONG> Line <BR> </STRONG>
 * The Line lorem Ipsum
 */
class Line {
	std::string name;
	int simulation_time;
	double distance;
	double direction;
public:
	Line(std::string name, std::string position, int simulation_time);
	~Line();
	std::string getName();
	double getDistance();
	double getDirection();
};
} // End namespace Phoenix
/*! @} */

#endif /* LINE_H_ */
