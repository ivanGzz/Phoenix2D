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

#ifndef ACTIONS_H_
#define ACTIONS_H_

#include "Position.h"

/*! @addtogroup phoenix_main
 * @{
 */
namespace Phoenix
{

class Commands;

 /*!
 * @brief <STRONG> Actions <BR> </STRONG>
 * The Actions lorem Ipsum
 */
class Actions {
public:
	enum ACTION {
		GO_TO,
		DRIBBLE_TO,
		HOLD_POSITION,
		PASS_TO_SECTION,
		ATTACK_SECTION
	};
	Commands *commands;
	Actions(Commands *commands);
	~Actions();
	bool goTo(Position position);
	void dribbleTo(Position position);
	void holdPosition(Position position);
	void passToSection(Position position);
	void attackSection(Position position);
};

} // End namespace Phoenix
/*! @} */


#endif /* ACTIONS_H_ */
