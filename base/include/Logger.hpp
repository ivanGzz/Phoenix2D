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
 * @file Logger.hpp
 *
 * @author Nelson Ivan Gonzalez
 */

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <string>

/*! @addtogroup phoenix_main
 * @{
 */
namespace Phoenix {
/*!
 * @brief <STRONG> Logger <BR> </STRONG>
 * The Logger object setup the logging feature of a Phoenix2D agent
 */
namespace Logger {

	/*!
	 * @brief Starts the logging feature
	 */
	void startLoggers();
	/*!
	 *
	 */
	void endLoggers();
	std::ofstream commands;
	std::ofstream body;
	std::ofstream see;
	std::ofstream hear;
	std::ofstream fullstate;

}

} // End namespace Phoenix
/*! @} */

#endif /* LOGGER_HPP_ */
