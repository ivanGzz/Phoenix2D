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
 * @file Self.hpp
 *
 * @author Nelson Ivan Gonzalez
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
class Self {
public:
	static std::string TEAM_NAME;								///< Team name of the agent
	static int         UNIFORM_NUMBER;							///< Uniform number of the agent
	static std::string SIDE;									///< Assigned side by the server, it could be right of left
	static int         ALLOW_MULT_DEFAULT_TYPE;					///< True if the server allow multiple player types
	static double      CATCHABLE_AREA_L_STRECH_MAX;				///< Maximum catchable area stretch for the goalie
	static double      CATCHABLE_AREA_L_STRECH_MIN;				///< Minimum catchable area stretch for the goalie
	static double      DASH_POWER_RATE_DELTA_MAX;				///< Maximum dash power rate delta
	static double      DASH_POWER_RATE_DELTA_MIN;				///< Minimum dash power rate delta
	static double      EFFORT_MAX_DELTA_FACTOR;					///< Maximum effort delta factor
	static double      EFFORT_MIN_DELTA_FACTOR;					///< Minimum effort delta factor
	static double      EXTRA_STAMINA_DELTA_MAX;					///< Maximum extra stamina delta
	static double      EXTRA_STAMINA_DELTA_MIN;					///< Minimum extra stamina delta
	static double      FOUL_DETECT_PROBABILITY_DELTA_FACTOR;	///< Foul detect probability delta factor
	static double      INERTIA_MOMENT_DELTA_FACTOR;				///< Inertia moment factor delta
	static double      KICK_POWER_RATE_DELTA_MAX;				///< Maximum kick power rate delta
	static double      KICK_POWER_RATE_DELTA_MIN;				///< Minimum kick power rate delta
	static double      KICK_RAND_DELTA_FACTOR;					///< Kick randomize delta factor
	static double      KICKABLE_MARGIN_DELTA_MAX;				///< Maximum kick-able margin delta
	static double      KICKABLE_MARGIN_DELTA_MIN;				///< Minimum kick-able margin delta
	static double      NEW_DASH_POWER_RATE_DELTA_MAX;			///< Maximum new dash power rate delta
	static double      NEW_DASH_POWER_RATE_DELTA_MIN;			///< Minimum new dash power rate delta
	static double      NEW_STAMINA_INC_MAX_DELTA_FACTOR;		///< Maximum new stamina increment delta factor
	static double      PLAYER_DECAY_DELTA_MAX;					///< Maximum player decay delta
	static double      PLAYER_DECAY_DELTA_MIN;					///< Minimum player decay delta
	static double      PLAYER_SIZE_DELTA_FACTOR;				///< Player size delta factor
	static double      PLAYER_SPEED_MAX_DELTA_MAX;				///< Maximum player maximum speed delta
	static double      PLAYER_SPEED_MAX_DELTA_MIN;				///< Minimum player maximum speed delta
	static int         PLAYER_TYPES;							///< Amount of player types
	static int         PT_MAX;									///< Maximum amount of players allowed with the same player type
	static int         RANDOM_SEED;								///< Random seed used to construct player types
	static double      STAMINA_INC_MAX_DELTA_FACTOR;			///< Maximum stamina increment delta factor
	static int         SUBS_MAX;								///< Maximum substitution in game
	static int         TYPE_ID;									///< Current player type id (0 - PLAYER_TYPES)
	static double      PLAYER_SPEED_MAX;						///< Maximum player speed
	static double      STAMINA_INC_MAX;							///< Maximum stamina increment
	static double      PLAYER_DECAY;							///< Player decay (how much the player speed will be decreased every cycle)
	static double      INERTIA_MOMENT;							///< Player inertia moment
	static double      DASH_POWER_RATE;							///< Dash power rate
	static double      PLAYER_SIZE;								///< Player size (radius)
	static double      KICKABLE_MARGIN;							///< Kick-able margin
	static double      KICK_RAND;								///< Random noise added to the kick command
	static double      EXTRA_STAMINA;							///< Player extra stamina
	static double      EFFORT_MAX;								///< Player maximum effort
	static double      EFFORT_MIN;								///< Player minimum effort
	static double      KICK_POWER_RATE;							///< Kick power rate
	static double      FOUL_DETECT_PROBABILITY;					///< Foul detect probability
	static double      CATCHABLE_AREA_L_STRETCH;				///< Catchable area length stretch for the goalie
	static std::string VIEW_MODE_WIDTH;							///< Current view width
	/*!
	 * @brief Returns the view width at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static std::string getViewModeWidthAtTime(unsigned int time);
	static std::string VIEW_MODE_QUALITY;						///< Current view quality
	/*!
	 * @brief Returns the view quality at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static std::string getViewModeQualityAtTime(unsigned int time);
	static double      STAMINA;									///< Current player stamina
	/*!
	 * @brief Returns the view quality at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static double      getStaminaAtTime(unsigned int time);
	static double      EFFORT;									///< Current player effort
	/*!
	 * @brief Returns the effort at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static double      getEffortAtTime(unsigned int time);
	static double      STAMINA_CAPACITY;						///< Current stamina capacity
	/*!
	 * @brief Returns the stamina capacity at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static double      getStaminaCapacityAtTime(unsigned int time);
	static double      AMOUNT_OF_SPEED;							///< Current amount of speed
	/*!
	 * @brief Returns the amount of speed at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static double      getAmountOfSpeedAtTime(unsigned int time);
	static double      DIRECTION_OF_SPEED;						///< Current relative speed direction
	/*!
	 * @brief Returns the speed direction at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static double      getDirectionOfSpeedAtTime(unsigned int time);
	static double      HEAD_ANGLE;								///< Current relative player head direction
	/*!
	 * @brief Returns the head angle at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static double      getHeadAngleAtTime(unsigned int time);
	static int         KICK_COUNT;								///< Kick command executed counter
	/*!
	 * @brief Returns the kick count at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static int         getKickCountAtTime(unsigned int time);
	static int         DASH_COUNT;								///< Dash command executed counter
	/*!
	 * @brief Returns the dash count at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static int         getDashCountAtTime(unsigned int time);
	static int         TURN_COUNT;								///< Turn command executed counter
	/*!
	 * @brief Returns the turn count at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static int         getTurnCountAtTime(unsigned int time);
	static int         SAY_COUNT;								///< Say command executed counter
	/*!
	 * @brief Returns the say count at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static int         getSayCountAtTime(unsigned int time);
	static int         TURN_NECK_COUNT;							///< Turn neck command executed counter
	/*!
	 * @brief Returns the turn neck count at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static int         getTurnNeckCountAtTime(unsigned int time);
	static int         CATCH_COUNT;								///< Catch command executed counter
	/*!
	 * @brief Returns the catch count at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static int         getCatchCountAtTime(unsigned int time);
	static int         MOVE_COUNT;								///< Move command executed counter
	/*!
	 * @brief Returns the move count at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static int         getMoveCountAtTime(unsigned int time);
	static int         CHANGE_VIEW_COUNT;						///< Change view command executed counter
	/*!
	 * @brief Returns the change view count at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static int         getChangeViewCountAtTime(unsigned int time);
	static int         ARM_MOVABLE;								///< Cycles till the arm is movable again
	/*!
	 * @brief Returns the arm movable at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static int         getArmMovableAtTime(unsigned int time);
	static int         ARM_EXPIRES;								///< Cycles till the arm stops pointing
	/*!
	 * @brief Returns the arm expires at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static int         getArmExpiresAtTime(unsigned int time);
	static double      ARM_DIST;								///< Relative distance the player is pointing to
	/*!
	 * @brief Returns the arm distance at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static double      getArmDistAtTime(unsigned int time);
	static double      ARM_DIR;									///< Relative direction the player is pointing to
	/*!
	 * @brief Returns the arm direction at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static double      getArmDirAtTime(unsigned int time);
	static int         ARM_COUNT;								///< Point to command executed counter
	/*!
	 * @brief Returns the dash count at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static int         getArmCountAtTime(unsigned int time);
	static std::string FOCUS_TARGET;							///< Focused target
	/*!
	 * @brief Returns the focus target at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static std::string getFocusTargetAtTime(unsigned int time);
	static int         FOCUS_COUNT;								///< Focus command executed counter
	/*!
	 * @brief Returns the focus count at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static int         getFocusCountAtTime(unsigned int time);
	static int         TACKLE_EXPIRES;							///< Cycles till the tackle stillness expires
	/*!
	 * @brief Returns the tackle expires at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static int         getTackleExpiresAtTime(unsigned int time);
	static int         TACKLE_COUNT;							///< Tackle command executed counter
	/*!
	 * @brief Returns the tackle count at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static int         getTackleCountAtTime(unsigned int time);
	static std::list<std::string> COLLISION;					///< Current player collisions
	/*!
	 * @brief Returns the collisions at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static std::list<std::string> getCollisionsAtTime(unsigned int time);
	static int         FOUL_CHARGED;							///< Not sure what this is
	/*!
	 * @brief Returns the foul charged at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static int         getFoulChargedAtTime(unsigned int time);
	static std::string FOUL_CARD;								///< Current card for the agent
	/*!
	 * @brief Returns the foul card at time Game::SIMULATION_TIME - time
	 * @param time The time delay
	 */
	static std::string getFoulCardAtTime(unsigned int time);
	/*!
	 * @brief Returns a pointer to the agent current absolute position
	 */
	static const Position* getPosition();
	/*!
	 * @brief Returns a pointer to the agent current absolute velocity
	 */
	static const Geometry::Vector2D* getVelocity();
	/*!
	 * @brief Informs the object about the last commands sent to the server
	 * @param last_commands_sent List of commands sent
	 */
	static void setLastCommandsSet(std::list<Command*> last_commands_sent);
	/*!
	 * @brief Self default constructor
	 * @param player_params Player parameters string received from the server
	 * @param team_name Team name of the agent
	 * @param unum Uniform number assigned to the agent by the server
	 * @param side Side assigned by the server
	 */
	Self(std::string player_params, std::string team_name, int unum, std::string side);
	/*!
	 * @brief Self default destructor
	 */
	~Self();
	/*!
	 * @brief Add the player parameters for the given player id
	 * @brief Player type parameters string received from the server
	 */
	void addPlayerType(std::string player_type);
	/*!
	 * @brief Process the sense body sensor
	 * @param sense_body Sense body string received by the sense body sensor from the server
	 */
	void processSenseBody(std::string sense_body);
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
};

} // End namespace Phoenix
/*! @} */

#endif /* SELF_HPP_ */
