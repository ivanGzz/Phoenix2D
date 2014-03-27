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

#ifndef FLAG_H_
#define FLAG_H_

#include <string>
#include <map>

/*! @addtogroup phoenix_main
 * @{
 */
namespace Phoenix
{
/*!
 * @brief <STRONG> _coordinate <BR> </STRONG>
 * The Coordinate is  just a holder for coordinates
 */
struct _coordinate {
	double x;
	double y;
};

/*!
 * @brief <STRONG> Flag <BR> </STRONG>
 * The Flag lorem Ipsum
 */
class Flag {
	std::string name;
	double distance;
	double direction;
	double x;
	double y;
	double minDistance;
	double maxDistance;
	double error;
	int simulation_time;
	static std::map<std::string, _coordinate> FIELD;
public:
	Flag(std::string name, std::string position, int simulation_time);
	~Flag();
	static void initializeField();
	std::string getName();
	double getDistance();
	double getDirection();
	double getX();
	double getY();
	double getMinDistance();
	double getMaxDistance();
	double getError();
};
} // End namespace Phoenix
/*! @} */

#endif /* FLAG_H_ */
