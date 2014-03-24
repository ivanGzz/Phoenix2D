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

#ifndef SERVER_H_
#define SERVER_H_

#include <string>

/*! @addtogroup phoenix_main
 * @{
 */
namespace Phoenix
{
/*! @addtogroup core
 * @{
 */
/*!
 * @brief <STRONG> Server <BR> </STRONG>
 * The Server lorem Ipsum
 */
class Server {
	std::string server_params;
	std::string getParameter(std::string parameter);
public:
	static double      AUDIO_CUT_DIST;
	static int         AUTO_MODE;
	static double      BACK_DASH_RATE;
	static int         BACK_PASSES;
	static double      BALL_ACCEL_MAX;
	static double      BALL_DECAY;
	static double      BALL_RAND;
	static double      BALL_SIZE;
	static double      BALL_SPEED_MAX;
	static double      BALL_STUCK_AREA;
	static double      BALL_WEIGHT;
	static int         CATCH_BAN_CYCLE;
	static double      CATCH_PROBABILITY;
	static double      CATCHABLE_AREA_L;
	static double      CATCHABLE_AREA_W;
	static double      CKICK_MARGIN;
	static int         CLANG_ADVICE_WIN;
	static int         CLANG_DEFINE_WIN;
	static int         CLANG_DEL_WIN;
	static int         CLANG_INFO_WIN;
	static int         CLANG_MESS_DELAY;
	static int         CLANG_MESS_PER_CYCLE;
	static int         CLANG_META_WIN;
	static int         CLANG_RULE_WIN;
	static int         CLANG_WIN_SIZE;
	static int         COACH;
	static int         COACH_PORT;
	static int         COACH_W_REFEREE;
	static int         CONNECT_WAIT;
	static double      CONTROL_RADIUS;
	static double      DASH_ANGLE_STEP;
	static double      DASH_POWER_RATE;
	static int         DROP_BALL_TIME;
	static double      EFFORT_DEC;
	static double      EFFORT_DEC_THR;
	static double      EFFORT_INC;
	static double      EFFORT_INC_THR;
	static double      EFFORT_INIT;
	static double      EFFORT_MIN;
	static int         EXTRA_HALF_TIME;
	static int         EXTRA_STAMINA;
	static int         FORBID_KICK_OFF_OFFSIDE;
	static int         FOUL_CYCLES;
	static double      FOUL_DETECT_PROBABILITY;
	static int         FOUL_EXPONENT;
	static int         FREE_KICK_FAULTS;
	static int         FREEFORM_SEND_PERIOD;
	static int         FREEFORM_WAIT_PERIOD;
	static int         FULLSTATE_L;
	static int         FULLSTATE_R;
	static int         GAME_LOG_COMPRESSION;
	static int         GAME_LOG_DATED;
	static std::string GAME_LOG_DIR;
	static int         GAME_LOG_FIXED;
	static std::string GAME_LOG_FIXED_NAME;
	static int         GAME_LOG_VERSION;
	static int         GAME_LOGGING;
	static int         GAME_OVER_WAIT;
	static double      GOAL_WIDTH;
	static int         GOALIE_MAX_MOVES;
	static int         GOLDEN_GOAL;
	static int         HALF_TIME;
	static int         HEAR_DECAY;
	static int         HEAR_INC;
	static int         HEAR_MAX;
	static int         INERTIA_MOMENT;
	static int         KEEPAWAY;
	static int         KEEPAWAY_LENGTH;
	static int         KEEPAWAY_LOG_DATED;
	static std::string KEEPAWAY_LOG_DIR;
	static int         KEEPAWAY_LOG_FIXED;
	static std::string KEEPAWAY_LOG_FIXED_NAME;
	static int         KEEPAWAY_LOGGING;
	static int         KEEPAWAY_START;
	static int         KEEPAWAY_WIDTH;
	static int         KICK_OFF_WAIT;
	static double      KICK_POWER_RATE;
	static double      KICK_RAND;
	static double      KICK_RAND_FACTOR_L;
	static double      KICK_RAND_FACTOR_R;
	static double      KICKABLE_MARGIN;
	static std::string LANDMARK_FILE;
	static std::string LOG_DATE_FORMAT;
	static int         LOG_TIMES;
	static double      MAX_BACK_TACKLE_POWER;
	static double      MAX_DASH_ANGLE;
	static double      MAX_DASH_POWER;
	static int         MAX_GOAL_KICKS;
	static double      MAX_TACKLE_POWER;
	static double      MAXMOMENT;
	static double      MAXNECKANG;
	static double      MAXNECKMOMENT;
	static double      MAXPOWER;
	static double      MIN_DASH_ANGLE;
	static double      MIN_DASH_POWER;
	static double      MINMOMENT;
	static double      MINNECKANG;
	static double      MINNECKMOMENT;
	static double      MINPOWER;
	static int         NR_EXTRA_HALFS;
	static int         NR_NORMAL_HALFS;
	static double      OFFSIDE_ACTIVE_AREA_SIZE;
	static double      OFFSIDE_KICK_MARGIN;
	static int         OLCOACH_PORT;
	static int         OLD_COACH_HEAR;
	static int         PEN_ALLOW_MULT_KICKS;
	static int         PEN_BEFORE_SETUP_WAIT;
	static int         PEN_COACH_MOVES_PLAYERS;
	static double      PEN_DIST_X;
	static int         PEN_MAX_EXTRA_KICKS;
	static double      PEN_MAX_GOALIE_DIST_X;
	static int         PEN_NR_KICKS;
	static double      PEN_RANDOM_WINNER;
	static int         PEN_READY_WAIT;
	static int         PEN_SETUP_WAIT;
	static int         PEN_TAKEN_WAIT;
	static int         PENALTY_SHOOT_OUTS;
	static double      PLAYER_ACCEL_MAX;
	static double      PLAYER_DECAY;
	static double      PLAYER_RAND;
	static double      PLAYER_SIZE;
	static double      PLAYER_SPEED_MAX;
	static double      PLAYER_SPEED_MAX_MIN;
	static double      PLAYER_WEIGHT;
	static int         POINT_TO_BAN;
	static int         POINT_TO_DURATION;
	static int         PORT;
	static double      PRAND_FACTOR_L;
	static double      PRAND_FACTOR_R;
	static int         PROFILE;
	static int         PROPER_GOAL_KICKS;
	static double      QUANTIZE_STEP;
	static double      QUANTIZE_STEP_L;
	static int         RECORD_MESSAGES;
	static double      RECOVER_DEC;
	static double      RECOVER_DEC_THR;
	static double      RECOVER_INIT;
	static double      RECOVER_MIN;
	static int         RECV_STEP;
	static double      RED_CARD_PROBABILITY;
	static int         SAY_COACH_CNT_MAX;
	static int         SAY_COACH_MSG_SIZE;
	static int         SAY_MSG_SIZE;
	static int         SEND_COMMS;
	static int         SEND_STEP;
	static int         SEND_VI_STEP;
	static int         SENSE_BODY_STEP;
	static double      SIDE_DASH_RATE;
	static int         SIMULATOR_STEP;
	static double      SLOW_DOWN_FACTOR;
	static double      SLOWNESS_ON_TOP_FOR_LEFT_TEAM;
	static double      SLOWNESS_ON_TOP_FOR_RIGHT_TEAM;
	static int         STAMINA_CAPACITY;
	static int         STAMINA_INC_MAX;
	static int         STAMINA_MAX;
	static int         START_GOAL_L;
	static int         START_GOAL_R;
	static double      STOPPED_BALL_VEL;
	static int         SYNCH_MICRO_SLEEP;
	static int         SYNCH_MODE;
	static int         SYNCH_OFFSET;
	static int         SYNCH_SEE_OFFSET;
	static double      TACKLE_BACK_DIST;
	static int         TACKLE_CYCLES;
	static double      TACKLE_DIST;
	static int         TACKLE_EXPONENT;
	static double      TACKLE_POWER_RATE;
	static double      TACKLE_RAND_FACTOR;
	static double      TACKLE_WIDTH;
	static double      TEAM_ACTUATOR_NOISE;
	static std::string TEAM_L_START;
	static std::string TEAM_R_START;
	static int         TEXT_LOG_COMPRESSION;
	static int         TEXT_LOG_DATED;
	static std::string TEXT_LOG_DIR;
	static int         TEXT_LOG_FIXED;
	static std::string TEXT_LOG_FIXED_NAME;
	static int         TEXT_LOGGING;
	static int         USE_OFFSIDE;
	static int         VERBOSE;
	static double      VISIBLE_ANGLE;
	static double      VISIBLE_DISTANCE;
	static double      WIND_ANG;
	static double      WIND_DIR;
	static double      WIND_FORCE;
	static double      WIND_NONE;
	static double      WIND_RAND;
	static double      WIND_RANDOM;
	Server(std::string server_params);
	~Server();
};
/*! @} */
} // End namespace Phoenix
/*! @} */

#endif /* SERVER_H_ */
