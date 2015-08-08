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
 * @file Flag.hpp
 *
 * @author Nelson Ivan Gonzalez
 */

#ifndef FLAG_HPP_
#define FLAG_HPP_

#include "Position.hpp"
#include <string>

/*! @addtogroup phoenix_base
 * @{
 */
namespace Phoenix {

/*!
 * @brief <STRONG> Flag <BR> </STRONG>
 * A Flag object stores information about a flag seen in the visual sensor for a
 * given simulation cycle.  It is used by the localization method.
 */
class Flag : public Object {
public:
	/*!
	 * @brief Flag default constructor
	 * @param name Name string for the flag received in the see sensor
	 * @param position String received in the see sensor
	 * @param simulation_time Simulation time the flag was seen
	 */
	Flag(std::string name, std::string position, int simulation_time);
	/*!
	 * @brief Flag default destructor
	 */
	~Flag();
	/*!
	 *
	 */
	std::string name();
	/*!
	 *
	 */
	double distance();
	/*!
	 *
	 */
	double direction();
	/*!
	 * @brief Returns the maximum error in the flag relative distance
	 * @return Distance error
	 */
	double distanceError();
	/*!
	 * @brief Returns the maximum error in the flag relative direction
	 * @return Direction error
	 */
	double directionError();
	double min_distance;		///< flag minimum relative distance
	double max_distance;		///< flag maximum relative distance
	double min_direction;	///< flag minimum relative direction
	double max_direction;	///< flag maximum relative direction
private:
	std::string _name;		///< flag string name received by the see sensor
	double _distance;		///< flag relative distance received by the see sensor
	double _direction;		///< flag relative direction received by the see sensor
	double _distance_error;			///< flag maximum error in the relative distance
	double _direction_error;			///< flag maximum error in the relative direction
	int _simulation_time;	///< simulation time the object was created
};

void initField();

} // End namespace Phoenix
/*! @} */

#endif /* FLAG_HPP_ */
