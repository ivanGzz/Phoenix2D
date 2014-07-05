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
 * @file Reader.hpp
 *
 * @author Nelson Ivan Gonzalez
 */

#ifndef READER_HPP_
#define READER_HPP_

/*! @addtogroup phoenix_base
 * @{
 */
namespace Phoenix {

class Connect;
class Parser;

/*!
 * @brief <STRONG> Reader <BR> </STRONG>
 * The Reader is in charge of read the incoming messages from the Connect object
 * and feed the Parser object with them.
 */
class Reader {
public:
	/*!
	 * @brief Reader default constructor
	 * @param connect Pointer to Connect object
	 * @param parser Pointer to Parser object
	 */
	Reader(Connect *connect, Parser *parser);
	/*!
	 * @brief Reader default destructor
	 */
	~Reader();
	/*!
	 * @brief Return true if the reader thread is running, false otherwise
	 */
	bool isRunning();
	/*!
	 * @brief Starts the reader thread
	 */
	void start();
	/*!
	 * @brief Function to be executed in the reader thread
	 */
	void execute();
	/*!
	 * @brief Stops the reader thread
	 */
	void stop();
};

} // End namespace Phoenix
/*! @} */

#endif /* READER_HPP_ */
