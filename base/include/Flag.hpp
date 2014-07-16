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
class Flag {
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
	 * @brief This method initializes the flag absolute positions in the fiel
	 * Since the coordinate axis changes in function of the team assigned side, the
	 * flags must be initialized after the agent connects and the server sends the
	 * corresponding side of the agent
	 */
	static void initializeField();
	/*!
	 * @brief Returns the flag string name
	 * @return Flag name
	 */
	std::string getName();
	/*!
	 * @brief Returns the flag relative distance
	 * @return Relative distance
	 */
	double getDistance();
	/*!
	 * @brief Returns the relative direction
	 * @return Relative direction
	 */
	double getDirection();
	/*!
	 * @brief Returns the absolute flag position in x
	 * @return Absolute position in x
	 */
	double getX();
	/*!
	 * @brief Returns the absolute flag position in y
	 * @return Absolute position in y
	 */
	double getY();
	/*!
	 * @brief Returns the minimum relative distance the flag could have
	 * @return Minimum distance
	 */
	double getMinDistance();
	/*!
	 * @brief Returns the maximum relative distance the flag could have
	 * @return Maximum distance
	 */
	double getMaxDistance();
	/*!
	 * @brief Returns the maximum error in the flag relative distance
	 * @return Distance error
	 */
	double getDistanceError();
	/*!
	 * @brief Returns the minimum relative direction the flag could have
	 * @return Minimum direction
	 */
	double getMinDirection();
	/*!
	 * @brief Returns the maximum relative direction the flag could have
	 * @return Maximum direction
	 */
	double getMaxDirection();
	/*!
	 * @brief Returns the maximum error in the flag relative direction
	 * @return Direction error
	 */
	double getDirectionError();
private:
	std::string name;		///< flag string name received by the see sensor
	double distance;		///< flag relative distance received by the see sensor
	double direction;		///< flag relative direction received by the see sensor
	double x;				///< flag absolute position in x
	double y;				///< flag absolute position in y
	double minDistance;		///< flag minimum relative distance
	double maxDistance;		///< flag maximum relative distance
	double minDirection;	///< flag minimum relative direction
	double maxDirection;	///< flag maximum relative direction
	double error;			///< flag maximum error in the relative distance
	double derror;			///< flag maximum error in the relative direction
	int simulation_time;	///< simulation time the object was created
};

} // End namespace Phoenix
/*! @} */

#endif /* FLAG_HPP_ */
