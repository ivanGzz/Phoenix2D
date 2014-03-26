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

#ifndef PLAYON_H_
#define PLAYON_H_

#include "PlayMode.h"
#include "WorldModel.h"
#include <string>

/*! @addtogroup phoenix_main
 * @{
 */
namespace Phoenix
{

class Commands;
class Actions;
/*! @addtogroup PlayModes
 * @{
 */
/*!
 * @brief <STRONG> PlayOn <BR> </STRONG>
 * The PlayOn lorem Ipsum
 */
class PlayOn : public PlayMode 
{
	Actions* actions;
public:
	PlayOn(Commands* commands, Actions* actions);
	~PlayOn();
	void setup(WorldModel world);
	void onPlayerExecute(WorldModel world);
	void onGoalieExecute(WorldModel world);
	void onCoachExecute(WorldModel world);
	void onMessageReceived(std::string message, int sender);
};
/*! @} */
} // End namespace Phoenix
/*! @} */

#endif /* PLAYON_H_ */
