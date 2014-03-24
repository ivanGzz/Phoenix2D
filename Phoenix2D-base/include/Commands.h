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

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <string>

/*! @addtogroup phoenix_main
 * @{
 */
namespace Phoenix
{

class Connect;

/*! @addtogroup core
 * @{
 */
 
 /*!
 * @brief <STRONG> Commands <BR> </STRONG>
 * The Commans lorem Ipsum
 */
class Commands {
public:
	Commands(Connect *connect);
	~Commands();
	void flush();
	void move(double x, double y);
	void turn(double moment);
	void turnNeck(double moment);
	void dash(double power, double direction);
	void say(std::string message);
	void catchBall(double direction);
	void kick(double power, double direction);
	void tackle(double power, bool willToFoul);
	void pointTo(double distance, double direction);
	void changeView(std::string width);
	void moveObject(std::string object, double x, double y);
	void changeMode(std::string mode);
	void start();
	void recover();
	int sendCommands();
};
/*! @} */
} // End namespace Phoenix
/*! @} */

#endif /* COMMANDS_H_ */
