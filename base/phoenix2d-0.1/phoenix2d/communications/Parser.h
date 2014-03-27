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

#ifndef PARSER_H_
#define PARSER_H_

#include <string>

/*! @addtogroup phoenix_main
 * @{
 */
namespace Phoenix
{

class Self;
class World;
class PlayMode;
class Trainer;

/*! @addtogroup core
 * @{
 */
 /*!
 * @brief <STRONG> Parser <BR> </STRONG>
 * The Parser lorem Ipsum
 */
class Parser {
public:
	Parser(Self *self, World *world);
	~Parser();
	void parseMessage(std::string message);
	static void registerPlayMode(PlayMode* play_mode);
	static void registerTrainer(Trainer* trainer);
};
/*! @} */
} // End namespace Phoenix
/*! @} */

#endif /* PARSER_H_ */
