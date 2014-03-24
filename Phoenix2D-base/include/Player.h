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

#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include <vector>
#include "Position.h"
#include "Vector2D.h"

/*! @addtogroup phoenix_main
 * @{
 */
namespace Phoenix
{

/*!
 * @brief <STRONG> Player <BR> </STRONG>
 * The Player lorem Ipsum
 */
class Player {
	double distance;
	double direction;
	double distChange;
	double dirChange;
	double bodyDirection;
	double headDirection;
	double pointDir;
	double x;
	double y;
	double vx;
	double vy;
	double theta;
	bool body_b;
	bool head_b;
	bool pointing;
	bool kicking;
	bool tackling;
	std::string team;
	int uniform_number;
	int simulation_time;
	bool goalie;
	//Player* bound;
	int player_id;
	bool is_in_sight_range;
	bool is_localized;
	bool is_bounded;
	std::vector<Player*> pretenders;
	Position position;
	Vector2D velocity;
public:
	Player();
	Player(std::string name, std::string position, int simulation_time);
	Player(std::string name, std::string position, int simulation_time, Position player_position, Vector2D player_velocity);
	~Player();
	Position getPosition();
	std::string getTeam();
	int getUniformNumber();
	Vector2D getVelocity();
	bool isGoalie();
	bool isPointing();
	double getPointingDirection();
	bool isKicking();
	bool isTackling();
	void boundTo(Player* player);
	//Player* getBound();
	void setPlayerId(int player_id);
	int getPlayerId();
	void toggleSightRange();
	bool isInSightRange();
	void pretendToBound(Player* player);
	int getPretendersCount();
	Player* getPretenderFront();
	bool localized();
	bool bounded();
	std::string print();
};
} // End namespace Phoenix
/*! @} */

#endif /* PLAYER_H_ */
