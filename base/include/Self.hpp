/*
 * Phoenix2D (RoboCup Soccer Simulation 2D League)
 * Copyright (c) 2013 - 2015 Nelson I. Gonzalez
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
 * @file Self.hpp
 *
 * @author Nelson I. Gonzalez
 */

#ifndef SELF_HPP_
#define SELF_HPP_

#include <string>
#include <list>
#include <vector>
#include "Flag.hpp"
#include "Position.hpp"
#include "geometry.hpp"

/*! @addtogroup phoenix_base
 * @{
 */
namespace Phoenix {

class Command;

/*!
 * @brief <STRONG> Self <BR> </STRONG>
 * The Self object stores information about the current status of the agent.  It includes
 * localization and body information.
 */
namespace Self {

	std::string TEAM_NAME;								///< Team name of the agent
	int         UNIFORM_NUMBER;							///< Uniform number of the agent
	std::string SIDE;									///< Assigned side by the server, it could be right of left
	int         ALLOW_MULT_DEFAULT_TYPE;					///< True if the server allow multiple player types
	double      CATCHABLE_AREA_L_STRECH_MAX;				///< Maximum catchable area stretch for the goalie
	double      CATCHABLE_AREA_L_STRECH_MIN;				///< Minimum catchable area stretch for the goalie
	double      DASH_POWER_RATE_DELTA_MAX;				///< Maximum dash power rate delta
	double      DASH_POWER_RATE_DELTA_MIN;				///< Minimum dash power rate delta
	double      EFFORT_MAX_DELTA_FACTOR;					///< Maximum effort delta factor
	double      EFFORT_MIN_DELTA_FACTOR;					///< Minimum effort delta factor
	double      EXTRA_STAMINA_DELTA_MAX;					///< Maximum extra stamina delta
	double      EXTRA_STAMINA_DELTA_MIN;					///< Minimum extra stamina delta
	double      FOUL_DETECT_PROBABILITY_DELTA_FACTOR;	///< Foul detect probability delta factor
	double      INERTIA_MOMENT_DELTA_FACTOR;				///< Inertia moment factor delta
	double      KICK_POWER_RATE_DELTA_MAX;				///< Maximum kick power rate delta
	double      KICK_POWER_RATE_DELTA_MIN;				///< Minimum kick power rate delta
	double      KICK_RAND_DELTA_FACTOR;					///< Kick randomize delta factor
	double      KICKABLE_MARGIN_DELTA_MAX;				///< Maximum kick-able margin delta
	double      KICKABLE_MARGIN_DELTA_MIN;				///< Minimum kick-able margin delta
	double      NEW_DASH_POWER_RATE_DELTA_MAX;			///< Maximum new dash power rate delta
	double      NEW_DASH_POWER_RATE_DELTA_MIN;			///< Minimum new dash power rate delta
	double      NEW_STAMINA_INC_MAX_DELTA_FACTOR;		///< Maximum new stamina increment delta factor
	double      PLAYER_DECAY_DELTA_MAX;					///< Maximum player decay delta
	double      PLAYER_DECAY_DELTA_MIN;					///< Minimum player decay delta
	double      PLAYER_SIZE_DELTA_FACTOR;				///< Player size delta factor
	double      PLAYER_SPEED_MAX_DELTA_MAX;				///< Maximum player maximum speed delta
	double      PLAYER_SPEED_MAX_DELTA_MIN;				///< Minimum player maximum speed delta
	int         PLAYER_TYPES;							///< Amount of player types
	int         PT_MAX;									///< Maximum amount of players allowed with the same player type
	int         RANDOM_SEED;								///< Random seed used to construct player types
	double      STAMINA_INC_MAX_DELTA_FACTOR;			///< Maximum stamina increment delta factor
	int         SUBS_MAX;								///< Maximum substitution in game
	int         TYPE_ID;									///< Current player type id (0 - PLAYER_TYPES)
	double      PLAYER_SPEED_MAX;						///< Maximum player speed
	double      STAMINA_INC_MAX;							///< Maximum stamina increment
	double      PLAYER_DECAY;							///< Player decay (how much the player speed will be decreased every cycle)
	double      INERTIA_MOMENT;							///< Player inertia moment
	double      DASH_POWER_RATE;							///< Dash power rate
	double      PLAYER_SIZE;								///< Player size (radius)
	double      KICKABLE_MARGIN;							///< Kick-able margin
	double      KICK_RAND;								///< Random noise added to the kick command
	double      EXTRA_STAMINA;							///< Player extra stamina
	double      EFFORT_MAX;								///< Player maximum effort
	double      EFFORT_MIN;								///< Player minimum effort
	double      KICK_POWER_RATE;							///< Kick power rate
	double      FOUL_DETECT_PROBABILITY;					///< Foul detect probability
	double      CATCHABLE_AREA_L_STRETCH;				///< Catchable area length stretch for the goalie
	double	   ANGLE_VIEW;								///< View angle for the visual sensor
	std::string VIEW_MODE_WIDTH;							///< Current view width
	/*!
	 * @brief Returns the view width at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	std::string viewModeWidth(unsigned int time = 0);
	std::string VIEW_MODE_QUALITY;						///< Current view quality
	/*!
	 * @brief Returns the view quality at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	std::string viewModeQuality(unsigned int time = 0);
	double      STAMINA;									///< Current player stamina
	/*!
	 * @brief Returns the view quality at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	double      stamina(unsigned int time = 0);
	double      EFFORT;									///< Current player effort
	/*!
	 * @brief Returns the effort at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	double      effort(unsigned int time = 0);
	double      STAMINA_CAPACITY;						///< Current stamina capacity
	/*!
	 * @brief Returns the stamina capacity at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	double      staminaCapacity(unsigned int time = 0);
	double      AMOUNT_OF_SPEED;							///< Current amount of speed
	/*!
	 * @brief Returns the amount of speed at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	double      amountOfSpeed(unsigned int time = 0);
	double      DIRECTION_OF_SPEED;						///< Current relative speed direction
	/*!
	 * @brief Returns the speed direction at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	double      directionOfSpeed(unsigned int time = 0);
	double      HEAD_ANGLE;								///< Current relative player head direction
	/*!
	 * @brief Returns the head angle at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	double      headAngle(unsigned int time = 0);
	int         KICK_COUNT;								///< Kick command executed counter
	/*!
	 * @brief Returns the kick count at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	int         kickCount(unsigned int time = 0);
	int         DASH_COUNT;								///< Dash command executed counter
	/*!
	 * @brief Returns the dash count at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	int         dashCount(unsigned int time = 0);
	int         TURN_COUNT;								///< Turn command executed counter
	/*!
	 * @brief Returns the turn count at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	int         turnCount(unsigned int time = 0);
	int         SAY_COUNT;								///< Say command executed counter
	/*!
	 * @brief Returns the say count at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	int         sayCount(unsigned int time = 0);
	int         TURN_NECK_COUNT;							///< Turn neck command executed counter
	/*!
	 * @brief Returns the turn neck count at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	int         turnNeckCount(unsigned int time = 0);
	int         CATCH_COUNT;								///< Catch command executed counter
	/*!
	 * @brief Returns the catch count at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	int         catchCount(unsigned int time = 0);
	int         MOVE_COUNT;								///< Move command executed counter
	/*!
	 * @brief Returns the move count at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	int         moveCount(unsigned int time = 0);
	int         CHANGE_VIEW_COUNT;						///< Change view command executed counter
	/*!
	 * @brief Returns the change view count at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	int         changeViewCount(unsigned int time = 0);
	int         ARM_MOVABLE;								///< Cycles till the arm is movable again
	/*!
	 * @brief Returns the arm movable at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	int         armMovable(unsigned int time = 0);
	int         ARM_EXPIRES;								///< Cycles till the arm stops pointing
	/*!
	 * @brief Returns the arm expires at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	int         armExpires(unsigned int time = 0);
	double      ARM_DISTANCE;								///< Relative distance the player is pointing to
	/*!
	 * @brief Returns the arm distance at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	double      armDistance(unsigned int time = 0);
	double      ARM_DIRECTION;									///< Relative direction the player is pointing to
	/*!
	 * @brief Returns the arm direction at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	double      armDirection(unsigned int time = 0);
	int         ARM_COUNT;								///< Point to command executed counter
	/*!
	 * @brief Returns the dash count at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	int         armCount(unsigned int time = 0);
	std::string FOCUS_TARGET;							///< Focused target
	/*!
	 * @brief Returns the focus target at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	std::string focusTarget(unsigned int time = 0);
	int         FOCUS_COUNT;								///< Focus command executed counter
	/*!
	 * @brief Returns the focus count at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	int         focusCount(unsigned int time = 0);
	int         TACKLE_EXPIRES;							///< Cycles till the tackle stillness expires
	/*!
	 * @brief Returns the tackle expires at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	int         tackleExpires(unsigned int time = 0);
	int         TACKLE_COUNT;							///< Tackle command executed counter
	/*!
	 * @brief Returns the tackle count at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	int         tackleCount(unsigned int time = 0);
	std::list<std::string> COLLISION;					///< Current player collisions
	/*!
	 * @brief Returns the collisions at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	std::list<std::string> collisions(unsigned int time = 0);
	int         FOUL_CHARGED;							///< Not sure what this is
	/*!
	 * @brief Returns the foul charged at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	int         foulCharged(unsigned int time = 0);
	std::string FOUL_CARD;								///< Current card for the agent
	/*!
	 * @brief Returns the foul card at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	std::string foulCard(unsigned int time = 0);
	/*!
	 * @brief Returns a pointer to the agent current absolute position
	 */
	Position position();
	/*!
	 * @brief Returns a pointer to the agent current absolute velocity
	 */
	Geometry::Vector2D velocity();
	/*!
	 * @brief Informs the object about the last commands sent to the server
	 * @param last_commands_sent List of commands sent
	 */
	void setLastCommandsSet(std::list<Command*> last_commands_sent);
	/*!
	 * @brief Self default constructor
	 * @param player_params Player parameters string received from the server
	 * @param team_name Team name of the agent
	 * @param unum Uniform number assigned to the agent by the server
	 * @param side Side assigned by the server
	 */
	void parsePlayerParams(std::string player_params);
	/*!
	 * @brief Add the player parameters for the given player id
	 * @brief Player type parameters string received from the server
	 */
	void addPlayerType(std::string player_type);
	/*!
	 * @brief Process the sense body sensor
	 * @param sense_body Sense body string received by the sense body sensor from the server
	 */
	void parseSenseBody(std::string sense_body);
	/*!
	 * @brief Changes the current player type
	 * @param type Type id to be changed
	 */
	void changePlayerType(int type);
	/*!
	 * @brief Localize the player using the flags provided by the see sensor
	 * @param flags List of flags seen by the see sensor
	 */
	void localize(std::vector<Flag> flags);

}

} // End namespace Phoenix
/*! @} */

#endif /* SELF_HPP_ */
