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
 * @file server.hpp
 *
 * @author Nelson I. Gonzalez
 */

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <string>

/*! @addtogroup phoenix_base
 * @{
 */
namespace Phoenix {

/*!
 * @brief <STRONG> Server <BR> </STRONG>
 * The Server object stores general information about the server and the current simulation.
 */
namespace Server {

	double      AUDIO_CUT_DIST;					///< Maximum distance a message can be heard by a player
	int         AUTO_MODE;						///< Auto mode
	double      BACK_DASH_RATE;					///< Back dash rate
	int         BACK_PASSES;						///< Back passes
	double      BALL_ACCEL_MAX;					///< Maximum ball acceleration
	double      BALL_DECAY;						///< Ball decay
	double      BALL_RAND;						///< Ball randomizer
	double      BALL_SIZE;						///< Ball size
	double      BALL_SPEED_MAX;					///< Maximum ball speed
	double      BALL_STUCK_AREA;					///< Ball stuck area
	double      BALL_WEIGHT;						///< Ball weight
	int         CATCH_BAN_CYCLE;					///< Catch ban cycles
	double      CATCH_PROBABILITY;				///< Catch probablity for goalies
	double      CATCHABLE_AREA_L;				///< Length of catch able area for goalies
	double      CATCHABLE_AREA_W;				///< Width of catch able area for goalies
	double      CKICK_MARGIN;					///< Margin of corner kicks
	int         CLANG_ADVICE_WIN;				///< Coach language advice message window
	int         CLANG_DEFINE_WIN;				///< Coach language define message window
	int         CLANG_DEL_WIN;					///< Coach language delete message window
	int         CLANG_INFO_WIN;					///< Coach language info message window
	int         CLANG_MESS_DELAY;				///< Coach language messages delay
	int         CLANG_MESS_PER_CYCLE;			///< Maximum coach language messages sent per cycles
	int         CLANG_META_WIN;					///< Coach language meta message window
	int         CLANG_RULE_WIN;					///< Coach language rule message window
	int         CLANG_WIN_SIZE;					///< Coach language window size
	int         COACH;							///< If true the coach can connect to the server
	int         COACH_PORT;						///< Port for the online coach to connect to the server
	int         COACH_W_REFEREE;					///< If true the trainer can be used
	int         CONNECT_WAIT;					///< Connect wait
	double      CONTROL_RADIUS;					///< Control radius
	double      DASH_ANGLE_STEP;					///< Dash direction quantization value
	double      DASH_POWER_RATE;					///< Dash power rate
	int         DROP_BALL_TIME;					///< Drop ball time
	double      EFFORT_DEC;						///< Effort decrement
	double      EFFORT_DEC_THR;					///< Effort decrement threshold
	double      EFFORT_INC;						///< Effort increment
	double      EFFORT_INC_THR;					///< Effort increment threshold
	double      EFFORT_INIT;						///< Initial effort
	double      EFFORT_MIN;						///< Minimum effort
	int         EXTRA_HALF_TIME;					///< If true the game will continue in extra time after a draw
	int         EXTRA_STAMINA;					///< Extra player stamina
	int         FORBID_KICK_OFF_OFFSIDE;			///< Forbid kick off off side
	int         FOUL_CYCLES;						///< Foul cycles
	double      FOUL_DETECT_PROBABILITY;			///< Foul detect probability
	int         FOUL_EXPONENT;					///< Foul exponent
	int         FREE_KICK_FAULTS;				///< Free kick faults
	int         FREEFORM_SEND_PERIOD;			///< Cycles to wait after a free form message is send by the coach
	int         FREEFORM_WAIT_PERIOD;			///< Cycles to wait after a new free form message can be issued by the coach
	int         FULLSTATE_L;						///< If true the server will send the full state sensor to the left team
	int         FULLSTATE_R;						///< If true the server will send the full state sensor to the right team
	int         GAME_LOG_COMPRESSION;			///< Compression level to use for the log files
	int         GAME_LOG_DATED;					///< Game log dated
	std::string GAME_LOG_DIR;					///< Directory to save the game logs
	int         GAME_LOG_FIXED;					///< Game log fixed
	std::string GAME_LOG_FIXED_NAME;				///< Game log fixed name
	int         GAME_LOG_VERSION;				///< Version logging to use
	int         GAME_LOGGING;					///< If true the game will be logged
	int         GAME_OVER_WAIT;					///< Cycles to wait after a game is over
	double      GOAL_WIDTH;						///< Width of the goals
	int         GOALIE_MAX_MOVES;				///< How many times the goalie can use the move command after a catch
	int         GOLDEN_GOAL;						///< If true the server will change to golden goal, after a draw
	int         HALF_TIME;						///< Duration of a half time in cycles
	int         HEAR_DECAY;						///< Hear decay
	int         HEAR_INC;						///< Hear capacity increment per cycle
	int         HEAR_MAX;						///< Maximum amount of messages heard per cycle
	int         INERTIA_MOMENT;					///< Inertia moment
	int         KEEPAWAY;						///< If true the server will play a keep away game
	int         KEEPAWAY_LENGTH;					///< Duration of a keep away game
	int         KEEPAWAY_LOG_DATED;				///< If true the keep away game log will include the date
	std::string KEEPAWAY_LOG_DIR;				///< Directory to save the keep away game log
	int         KEEPAWAY_LOG_FIXED;				///< Keep away fixed
	std::string KEEPAWAY_LOG_FIXED_NAME;			///< Keep away fixed name
	int         KEEPAWAY_LOGGING;				///< If true the server will log the keep away game
	int         KEEPAWAY_START;					///< Keep away start
	int         KEEPAWAY_WIDTH;					///< Keep away width
	int         KICK_OFF_WAIT;					///< Duration of kick off play mode
	double      KICK_POWER_RATE;					///< Kick power rate
	double      KICK_RAND;						///< Kick randomizer
	double      KICK_RAND_FACTOR_L;				///< Kick randomize factor for left team
	double      KICK_RAND_FACTOR_R;				///< Kick randomize factor for right team
	double      KICKABLE_MARGIN;					///< Kick-able margin
	std::string LANDMARK_FILE;					///< Landmark file path
	std::string LOG_DATE_FORMAT;					///< Date format for log files
	int         LOG_TIMES;						///< If true the server will log the time between cycles
	double      MAX_BACK_TACKLE_POWER;			///< Maximum power for backwards tackle
	double      MAX_DASH_ANGLE;					///< Maximum dash direction for dash command
	double      MAX_DASH_POWER;					///< Maximum dash power for dash command
	int         MAX_GOAL_KICKS;					///< Maximum goal kicks
	double      MAX_TACKLE_POWER;				///< Maximum power for tackle command
	double      MAXMOMENT;						///< Maximum turn angle for turn command
	double      MAXNECKANG;						///< Maximum possible head angle
	double      MAXNECKMOMENT;					///< Maximum angle turn for turn neck command
	double      MAXPOWER;						///< Maximum power for dash and kick command
	double      MIN_DASH_ANGLE;					///< Minimum dash direction for dash command
	double      MIN_DASH_POWER;					///< Minimum dash power for dash command
	double      MINMOMENT;						///< Minimum angle turn for turn command
	double      MINNECKANG;						///< Minimum possible head angle
	double      MINNECKMOMENT;					///< Minimum angle turn for turn neck command
	double      MINPOWER;						///< Minimum power for dash and kick command
	int         NR_EXTRA_HALFS;					///< Number of extra halves
	int         NR_NORMAL_HALFS;					///< Number of halves
	double      OFFSIDE_ACTIVE_AREA_SIZE;		///< Off side active area size
	double      OFFSIDE_KICK_MARGIN;				///< Off side kick margin
	int         OLCOACH_PORT;					///< Port for an online coach to connect to the server
	int         OLD_COACH_HEAR;					///< If true the server will send the old coach hear
	int         PEN_ALLOW_MULT_KICKS;			///< True if a player can kick the ball after a penalty
	int         PEN_BEFORE_SETUP_WAIT;			///< Cycles to wait after the first round of penalties
	int         PEN_COACH_MOVES_PLAYERS;			///< Penalty coach moves players
	double      PEN_DIST_X;						///< Distance from the goal to the ball in a penalty
	int         PEN_MAX_EXTRA_KICKS;				///< Maximum kicks after first round of penalties
	double      PEN_MAX_GOALIE_DIST_X;			///< Maximum distance allowed for a goalie in a penalty
	int         PEN_NR_KICKS;					///< Penalties for first round
	double      PEN_RANDOM_WINNER;				///< Penalty random winner
	int         PEN_READY_WAIT;					///< Cycles to wait once the player is ready for a penalty
	int         PEN_SETUP_WAIT;					///< Cycles to wait before a penalty
	int         PEN_TAKEN_WAIT;					///< Cycles to wait after a penalty
	int         PENALTY_SHOOT_OUTS;				///< Penalty shoot outs
	double      PLAYER_ACCEL_MAX;				///< Player maximum acceleration
	double      PLAYER_DECAY;					///< Player decay
	double      PLAYER_RAND;						///< Player randomizer
	double      PLAYER_SIZE;						///< Player size (radius)
	double      PLAYER_SPEED_MAX;				///< Player maximum maximum speed
	double      PLAYER_SPEED_MAX_MIN;			///< Player minimum maximum speed
	double      PLAYER_WEIGHT;					///< Player weight
	int         POINT_TO_BAN;					///< Stillness of a point to command
	int         POINT_TO_DURATION;				///< Duration of point to command
	int         PORT;							///< Server port for players to connect
	double      PRAND_FACTOR_L;					///< Player randomize factor for left team
	double      PRAND_FACTOR_R;					///< Player randomize factor for right team
	int         PROFILE;							///< Profile
	int         PROPER_GOAL_KICKS;				///< Proper goal kicks
	double      QUANTIZE_STEP;					///< Quantization value for dynamic objects
	double      QUANTIZE_STEP_L;					///< Quantization value for objects
	int         RECORD_MESSAGES;					///< Record messages
	double      RECOVER_DEC;						///< Recovery decrement
	double      RECOVER_DEC_THR;					///< Recovery decrement threshold
	double      RECOVER_INIT;					///< Initial recovery
	double      RECOVER_MIN;						///< Minimum recovery
	int         RECV_STEP;						///< Commands process frequency
	double      RED_CARD_PROBABILITY;			///< Red card probability
	int         SAY_COACH_CNT_MAX;				///< Maximum coach messages
	int         SAY_COACH_MSG_SIZE;				///< Maximum say coach message size
	int         SAY_MSG_SIZE;					///< Maximum say message size
	int         SEND_COMMS;						///< Monitor data sending frequency
	int         SEND_STEP;						///< See sensor update frequency
	int         SEND_VI_STEP;					///< See global sensor update frequency
	int         SENSE_BODY_STEP;					///< Sense body sensor update frequency
	double      SIDE_DASH_RATE;					///< Side dash rate
	int         SIMULATOR_STEP;					///< Duration of a simulation cycle
	double      SLOW_DOWN_FACTOR;				///< Slow down factor
	double      SLOWNESS_ON_TOP_FOR_LEFT_TEAM;	///< Slowness on top for the left team
	double      SLOWNESS_ON_TOP_FOR_RIGHT_TEAM;	///< Slowness on top for the right team
	int         STAMINA_CAPACITY;				///< Stamina capacity for the players
	int         STAMINA_INC_MAX;					///< Maximum stamina increment
	int         STAMINA_MAX;						///< Maximum stamina
	int         START_GOAL_L;					///< Start goals for the left team
	int         START_GOAL_R;					///< start goals for the right team
	double      STOPPED_BALL_VEL;				///< Stopped ball velocity
	int         SYNCH_MICRO_SLEEP;				///< Sleeping microseconds for the server in synchronized mode
	int         SYNCH_MODE;						///< True if the server is in synchronized mode
	int         SYNCH_OFFSET;					///< Offset in synchronized mode
	int         SYNCH_SEE_OFFSET;				///< Offset of the see sensor in synchronized mode
	double      TACKLE_BACK_DIST;				///< Tackle back distance
	int         TACKLE_CYCLES;					///< Tackle cycles
	double      TACKLE_DIST;						///< Tackle distance
	int         TACKLE_EXPONENT;					///< Exponent of tackle equation
	double      TACKLE_POWER_RATE;				///< Tackle power rate
	double      TACKLE_RAND_FACTOR;				///< Tackle randomize factor
	double      TACKLE_WIDTH;					///< Tackle width
	double      TEAM_ACTUATOR_NOISE;				///< Team actuator noise
	std::string TEAM_L_START;					///< Left team start
	std::string TEAM_R_START;					///< Right team start
	int         TEXT_LOG_COMPRESSION;			///< True if the log is compressed
	int         TEXT_LOG_DATED;					///< True if the date is appended to the log name
	std::string TEXT_LOG_DIR;					///< Directory for the log files
	int         TEXT_LOG_FIXED;					///< Text log fixed
	std::string TEXT_LOG_FIXED_NAME;				///< Text log fixed name
	int         TEXT_LOGGING;					///< True if the server logs the game
	int         USE_OFFSIDE;						///< True if the off sides are marked
	int         VERBOSE;							///< True if the server works in verbose mode
	double      VISIBLE_ANGLE;					///< Visible angle aperture
	double      VISIBLE_DISTANCE;				///< Visible distance for objects behind the agent
	double      WIND_ANG;						///< Wind angle
	double      WIND_DIR;						///< Wind direction
	double      WIND_FORCE;						///< Wind force
	double      WIND_NONE;						///< Wind none
	double      WIND_RAND;						///< Wind randomize
	double      WIND_RANDOM;						///< Widn randomize
	/*!
	 *
	 */
	void parseServerParams(std::string params);
};

} // End namespace Phoenix
/*! @} */

#endif /* SERVER_HPP_ */
