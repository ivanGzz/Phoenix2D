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
 * @file server.hpp
 *
 * @author Nelson Ivan Gonzalez
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
class Server {
public:
	static double      AUDIO_CUT_DIST;					///< Maximum distance a message can be heard by a player
	static int         AUTO_MODE;						///< Auto mode
	static double      BACK_DASH_RATE;					///< Back dash rate
	static int         BACK_PASSES;						///< Back passes
	static double      BALL_ACCEL_MAX;					///< Maximum ball acceleration
	static double      BALL_DECAY;						///< Ball decay
	static double      BALL_RAND;						///< Ball randomizer
	static double      BALL_SIZE;						///< Ball size
	static double      BALL_SPEED_MAX;					///< Maximum ball speed
	static double      BALL_STUCK_AREA;					///< Ball stuck area
	static double      BALL_WEIGHT;						///< Ball weight
	static int         CATCH_BAN_CYCLE;					///< Catch ban cycles
	static double      CATCH_PROBABILITY;				///< Catch probablity for goalies
	static double      CATCHABLE_AREA_L;				///< Length of catch able area for goalies
	static double      CATCHABLE_AREA_W;				///< Width of catch able area for goalies
	static double      CKICK_MARGIN;					///< Margin of corner kicks
	static int         CLANG_ADVICE_WIN;				///< Coach language advice message window
	static int         CLANG_DEFINE_WIN;				///< Coach language define message window
	static int         CLANG_DEL_WIN;					///< Coach language delete message window
	static int         CLANG_INFO_WIN;					///< Coach language info message window
	static int         CLANG_MESS_DELAY;				///< Coach language messages delay
	static int         CLANG_MESS_PER_CYCLE;			///< Maximum coach language messages sent per cycles
	static int         CLANG_META_WIN;					///< Coach language meta message window
	static int         CLANG_RULE_WIN;					///< Coach language rule message window
	static int         CLANG_WIN_SIZE;					///< Coach language window size
	static int         COACH;							///< If true the coach can connect to the server
	static int         COACH_PORT;						///< Port for the online coach to connect to the server
	static int         COACH_W_REFEREE;					///< If true the trainer can be used
	static int         CONNECT_WAIT;					///< Connect wait
	static double      CONTROL_RADIUS;					///< Control radius
	static double      DASH_ANGLE_STEP;					///< Dash direction quantization value
	static double      DASH_POWER_RATE;					///< Dash power rate
	static int         DROP_BALL_TIME;					///< Drop ball time
	static double      EFFORT_DEC;						///< Effort decrement
	static double      EFFORT_DEC_THR;					///< Effort decrement threshold
	static double      EFFORT_INC;						///< Effort increment
	static double      EFFORT_INC_THR;					///< Effort increment threshold
	static double      EFFORT_INIT;						///< Initial effort
	static double      EFFORT_MIN;						///< Minimum effort
	static int         EXTRA_HALF_TIME;					///< If true the game will continue in extra time after a draw
	static int         EXTRA_STAMINA;					///< Extra player stamina
	static int         FORBID_KICK_OFF_OFFSIDE;			///< Forbid kick off off side
	static int         FOUL_CYCLES;						///< Foul cycles
	static double      FOUL_DETECT_PROBABILITY;			///< Foul detect probability
	static int         FOUL_EXPONENT;					///< Foul exponent
	static int         FREE_KICK_FAULTS;				///< Free kick faults
	static int         FREEFORM_SEND_PERIOD;			///< Cycles to wait after a free form message is send by the coach
	static int         FREEFORM_WAIT_PERIOD;			///< Cycles to wait after a new free form message can be issued by the coach
	static int         FULLSTATE_L;						///< If true the server will send the full state sensor to the left team
	static int         FULLSTATE_R;						///< If true the server will send the full state sensor to the right team
	static int         GAME_LOG_COMPRESSION;			///< Compression level to use for the log files
	static int         GAME_LOG_DATED;					///< Game log dated
	static std::string GAME_LOG_DIR;					///< Directory to save the game logs
	static int         GAME_LOG_FIXED;					///< Game log fixed
	static std::string GAME_LOG_FIXED_NAME;				///< Game log fixed name
	static int         GAME_LOG_VERSION;				///< Version logging to use
	static int         GAME_LOGGING;					///< If true the game will be logged
	static int         GAME_OVER_WAIT;					///< Cycles to wait after a game is over
	static double      GOAL_WIDTH;						///< Width of the goals
	static int         GOALIE_MAX_MOVES;				///< How many times the goalie can use the move command after a catch
	static int         GOLDEN_GOAL;						///< If true the server will change to golden goal, after a draw
	static int         HALF_TIME;						///< Duration of a half time in cycles
	static int         HEAR_DECAY;						///< Hear decay
	static int         HEAR_INC;						///< Hear capacity increment per cycle
	static int         HEAR_MAX;						///< Maximum amount of messages heard per cycle
	static int         INERTIA_MOMENT;					///< Inertia moment
	static int         KEEPAWAY;						///< If true the server will play a keep away game
	static int         KEEPAWAY_LENGTH;					///< Duration of a keep away game
	static int         KEEPAWAY_LOG_DATED;				///< If true the keep away game log will include the date
	static std::string KEEPAWAY_LOG_DIR;				///< Directory to save the keep away game log
	static int         KEEPAWAY_LOG_FIXED;				///< Keep away fixed
	static std::string KEEPAWAY_LOG_FIXED_NAME;			///< Keep away fixed name
	static int         KEEPAWAY_LOGGING;				///< If true the server will log the keep away game
	static int         KEEPAWAY_START;					///< Keep away start
	static int         KEEPAWAY_WIDTH;					///< Keep away width
	static int         KICK_OFF_WAIT;					///< Duration of kick off play mode
	static double      KICK_POWER_RATE;					///< Kick power rate
	static double      KICK_RAND;						///< Kick randomizer
	static double      KICK_RAND_FACTOR_L;				///< Kick randomize factor for left team
	static double      KICK_RAND_FACTOR_R;				///< Kick randomize factor for right team
	static double      KICKABLE_MARGIN;					///< Kick-able margin
	static std::string LANDMARK_FILE;					///< Landmark file path
	static std::string LOG_DATE_FORMAT;					///< Date format for log files
	static int         LOG_TIMES;						///< If true the server will log the time between cycles
	static double      MAX_BACK_TACKLE_POWER;			///< Maximum power for backwards tackle
	static double      MAX_DASH_ANGLE;					///< Maximum dash direction for dash command
	static double      MAX_DASH_POWER;					///< Maximum dash power for dash command
	static int         MAX_GOAL_KICKS;					///< Maximum goal kicks
	static double      MAX_TACKLE_POWER;				///< Maximum power for tackle command
	static double      MAXMOMENT;						///< Maximum turn angle for turn command
	static double      MAXNECKANG;						///< Maximum possible head angle
	static double      MAXNECKMOMENT;					///< Maximum angle turn for turn neck command
	static double      MAXPOWER;						///< Maximum power for dash and kick command
	static double      MIN_DASH_ANGLE;					///< Minimum dash direction for dash command
	static double      MIN_DASH_POWER;					///< Minimum dash power for dash command
	static double      MINMOMENT;						///< Minimum angle turn for turn command
	static double      MINNECKANG;						///< Minimum possible head angle
	static double      MINNECKMOMENT;					///< Minimum angle turn for turn neck command
	static double      MINPOWER;						///< Minimum power for dash and kick command
	static int         NR_EXTRA_HALFS;					///< Number of extra halves
	static int         NR_NORMAL_HALFS;					///< Number of halves
	static double      OFFSIDE_ACTIVE_AREA_SIZE;		///< Off side active area size
	static double      OFFSIDE_KICK_MARGIN;				///< Off side kick margin
	static int         OLCOACH_PORT;					///< Port for an online coach to connect to the server
	static int         OLD_COACH_HEAR;					///< If true the server will send the old coach hear
	static int         PEN_ALLOW_MULT_KICKS;			///< True if a player can kick the ball after a penalty
	static int         PEN_BEFORE_SETUP_WAIT;			///< Cycles to wait after the first round of penalties
	static int         PEN_COACH_MOVES_PLAYERS;			///< Penalty coach moves players
	static double      PEN_DIST_X;						///< Distance from the goal to the ball in a penalty
	static int         PEN_MAX_EXTRA_KICKS;				///< Maximum kicks after first round of penalties
	static double      PEN_MAX_GOALIE_DIST_X;			///< Maximum distance allowed for a goalie in a penalty
	static int         PEN_NR_KICKS;					///< Penalties for first round
	static double      PEN_RANDOM_WINNER;				///< Penalty random winner
	static int         PEN_READY_WAIT;					///< Cycles to wait once the player is ready for a penalty
	static int         PEN_SETUP_WAIT;					///< Cycles to wait before a penalty
	static int         PEN_TAKEN_WAIT;					///< Cycles to wait after a penalty
	static int         PENALTY_SHOOT_OUTS;				///< Penalty shoot outs
	static double      PLAYER_ACCEL_MAX;				///< Player maximum acceleration
	static double      PLAYER_DECAY;					///< Player decay
	static double      PLAYER_RAND;						///< Player randomizer
	static double      PLAYER_SIZE;						///< Player size (radius)
	static double      PLAYER_SPEED_MAX;				///< Player maximum maximum speed
	static double      PLAYER_SPEED_MAX_MIN;			///< Player minimum maximum speed
	static double      PLAYER_WEIGHT;					///< Player weight
	static int         POINT_TO_BAN;					///< Stillness of a point to command
	static int         POINT_TO_DURATION;				///< Duration of point to command
	static int         PORT;							///< Server port for players to connect
	static double      PRAND_FACTOR_L;					///< Player randomize factor for left team
	static double      PRAND_FACTOR_R;					///< Player randomize factor for right team
	static int         PROFILE;							///< Profile
	static int         PROPER_GOAL_KICKS;				///< Proper goal kicks
	static double      QUANTIZE_STEP;					///< Quantization value for dynamic objects
	static double      QUANTIZE_STEP_L;					///< Quantization value for static objects
	static int         RECORD_MESSAGES;					///< Record messages
	static double      RECOVER_DEC;						///< Recovery decrement
	static double      RECOVER_DEC_THR;					///< Recovery decrement threshold
	static double      RECOVER_INIT;					///< Initial recovery
	static double      RECOVER_MIN;						///< Minimum recovery
	static int         RECV_STEP;						///< Commands process frequency
	static double      RED_CARD_PROBABILITY;			///< Red card probability
	static int         SAY_COACH_CNT_MAX;				///< Maximum coach messages
	static int         SAY_COACH_MSG_SIZE;				///< Maximum say coach message size
	static int         SAY_MSG_SIZE;					///< Maximum say message size
	static int         SEND_COMMS;						///< Monitor data sending frequency
	static int         SEND_STEP;						///< See sensor update frequency
	static int         SEND_VI_STEP;					///< See global sensor update frequency
	static int         SENSE_BODY_STEP;					///< Sense body sensor update frequency
	static double      SIDE_DASH_RATE;					///< Side dash rate
	static int         SIMULATOR_STEP;					///< Duration of a simulation cycle
	static double      SLOW_DOWN_FACTOR;				///< Slow down factor
	static double      SLOWNESS_ON_TOP_FOR_LEFT_TEAM;	///< Slowness on top for the left team
	static double      SLOWNESS_ON_TOP_FOR_RIGHT_TEAM;	///< Slowness on top for the right team
	static int         STAMINA_CAPACITY;				///< Stamina capacity for the players
	static int         STAMINA_INC_MAX;					///< Maximum stamina increment
	static int         STAMINA_MAX;						///< Maximum stamina
	static int         START_GOAL_L;					///< Start goals for the left team
	static int         START_GOAL_R;					///< start goals for the right team
	static double      STOPPED_BALL_VEL;				///< Stopped ball velocity
	static int         SYNCH_MICRO_SLEEP;				///< Sleeping microseconds for the server in synchronized mode
	static int         SYNCH_MODE;						///< True if the server is in synchronized mode
	static int         SYNCH_OFFSET;					///< Offset in synchronized mode
	static int         SYNCH_SEE_OFFSET;				///< Offset of the see sensor in synchronized mode
	static double      TACKLE_BACK_DIST;				///< Tackle back distance
	static int         TACKLE_CYCLES;					///< Tackle cycles
	static double      TACKLE_DIST;						///< Tackle distance
	static int         TACKLE_EXPONENT;					///< Exponent of tackle equation
	static double      TACKLE_POWER_RATE;				///< Tackle power rate
	static double      TACKLE_RAND_FACTOR;				///< Tackle randomize factor
	static double      TACKLE_WIDTH;					///< Tackle width
	static double      TEAM_ACTUATOR_NOISE;				///< Team actuator noise
	static std::string TEAM_L_START;					///< Left team start
	static std::string TEAM_R_START;					///< Right team start
	static int         TEXT_LOG_COMPRESSION;			///< True if the log is compressed
	static int         TEXT_LOG_DATED;					///< True if the date is appended to the log name
	static std::string TEXT_LOG_DIR;					///< Directory for the log files
	static int         TEXT_LOG_FIXED;					///< Text log fixed
	static std::string TEXT_LOG_FIXED_NAME;				///< Text log fixed name
	static int         TEXT_LOGGING;					///< True if the server logs the game
	static int         USE_OFFSIDE;						///< True if the off sides are marked
	static int         VERBOSE;							///< True if the server works in verbose mode
	static double      VISIBLE_ANGLE;					///< Visible angle aperture
	static double      VISIBLE_DISTANCE;				///< Visible distance for objects behind the agent
	static double      WIND_ANG;						///< Wind angle
	static double      WIND_DIR;						///< Wind direction
	static double      WIND_FORCE;						///< Wind force
	static double      WIND_NONE;						///< Wind none
	static double      WIND_RAND;						///< Wind randomize
	static double      WIND_RANDOM;						///< Widn randomize
	/*!
	 * @brief Server default constructor
	 * @param server_params Server parameters received from the server
	 */
	Server(std::string server_params);
	/*!
	 * @brief Server default destructor
	 */
	~Server();
private:
	std::string server_params;							///< Server parameters received from the server
	/*!
	 * @brief Returns the value for the given parameter
	 * @param parameter Parameter to be searched
	 */
	std::string getParameter(std::string parameter);
};

} // End namespace Phoenix
/*! @} */

#endif /* SERVER_HPP_ */
