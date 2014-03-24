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

#ifndef PLAYMODE_H_
#define PLAYMODE_H_

#include "WorldModel.h"

/*! @addtogroup phoenix_main
 * @{
 */
namespace Phoenix
{

class Commands;

/*!
 * @defgroup PlayModes Phoenix Play Modes
 * @brief <STRONG> Phoenix2D Play Modes <BR> </STRONG>
 * These are the behaviors you may define for a player:<BR>
 * 	<ul>
 *    <li>BefforeKickOff</li>
 * 	  <li>CornerKickL</li>
 * 	  <li>CornerKickR</li>
 * 	  <li>FreeKickL</li>
 * 	  <li>FreeKickR</li>
 * 	  <li>GoalKickL</li>
 * 	  <li>GoalKickR</li>
 * 	  <li>KickInL</li>
 * 	  <li>KickInR</li>
 * 	  <li>KickOffL</li>
 * 	  <li>KickOffR</li>
 * 	  <li>PlayOn</li>
 *	</ul> 
 * @{
 */

/*!
 * @brief <STRONG> PlayMode <BR> </STRONG>
 * The PlayMode lorem Ipsum
 */
class PlayMode {
protected:
	Commands *commands;
public:
	PlayMode(Commands *commands);
	virtual ~PlayMode();
	void onStart();
	virtual void setup(WorldModel world) = 0;
	void onPreExecute();
	virtual void onPlayerExecute(WorldModel world) = 0;
	virtual void onGoalieExecute(WorldModel world) = 0;
	virtual void onCoachExecute(WorldModel world) = 0;
	virtual void onMessageReceived(std::string message, int sender) = 0;
	void onPostExecute();
	void onEnd();
};
/*! @} */
} // End namespace Phoenix
/*! @} */

#endif /* PLAYMODE_H_ */
