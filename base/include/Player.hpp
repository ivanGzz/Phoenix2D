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

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <string>
#include <vector>
#include "Position.hpp"
#include "Vector2D.hpp"

/*! @addtogroup phoenix_main
 * @{
 */
namespace Phoenix {

/*!
 * @brief <STRONG> Player <BR> </STRONG>
 * The Player lorem Ipsum
 */
class Player {
public:
	Player();
	~Player();
	void initForPlayer(std::string name, std::string data, Position player_position, Vector2D player_velocity);
	void initForCoach(std::string name, std::string data);
	void initForFullstate(std::string team, int unum, double x, double y, double vx, double vy, double b, double n);
	Position* getPosition();
	std::string getTeam();
	int getUniformNumber();
	Vector2D* getVelocity();
	bool isGoalie();
	bool isPointing();
	double getPointingDirection();
	bool isKicking();
	bool isTackling();
	void setPlayerId(int player_id);
	int getPlayerId();
	void toggleSightRange();
	bool isInSightRange();
private:
	double distance;
	double direction;
	double distChange;
	double dirChange;
	double bodyDirection;
	double headDirection;
	double pointDir;
	double x;
	double y;
	double body;
	double head;
	double vx;
	double vy;
	bool has_body;
	bool has_head;
	bool pointing;
	bool kicking;
	bool tackling;
	std::string team;
	int uniform_number;
	bool goalie;
	int player_id;
	bool is_in_sight_range;
	bool is_localized;
	Position position;
	Vector2D velocity;
};

} // End namespace Phoenix
/*! @} */

#endif /* PLAYER_HPP_ */
