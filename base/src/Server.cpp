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
 * @file Server.cpp
 *
 * @author Nelson I. Gonzalez
 */

#include "Server.hpp"
#include <boost/regex.hpp>
#include <cstdlib>
#include <iostream>

namespace Phoenix {

double      AUDIO_CUT_DIST                 = 50.0;
int         AUTO_MODE                      = 0;
double      BACK_DASH_RATE                 = 0.6;
int         BACK_PASSES                    = 1;
double      BALL_ACCEL_MAX                 = 2.7;
double      BALL_DECAY                     = 0.94;
double      BALL_RAND                      = 0.05;
double      BALL_SIZE                      = 0.085;
double      BALL_SPEED_MAX                 = 3.0;
double      BALL_STUCK_AREA                = 3.0;
double      BALL_WEIGHT                    = 0.2;
int         CATCH_BAN_CYCLE                = 5;
double      CATCH_PROBABILITY              = 1.0;
double      CATCHABLE_AREA_L               = 1.2;
double      CATCHABLE_AREA_W               = 1.0;
double      CKICK_MARGIN                   = 1.0;
int         CLANG_ADVICE_WIN               = 1;
int         CLANG_DEFINE_WIN               = 1;
int         CLANG_DEL_WIN                  = 1;
int         CLANG_INFO_WIN                 = 1;
int         CLANG_MESS_DELAY               = 50;
int         CLANG_MESS_PER_CYCLE           = 1;
int         CLANG_META_WIN                 = 1;
int         CLANG_RULE_WIN                 = 1;
int         CLANG_WIN_SIZE                 = 300;
int         COACH                          = 0;
int         COACH_PORT                     = 6001;
int         COACH_W_REFEREE                = 0;
int         CONNECT_WAIT                   = 300;
double      CONTROL_RADIUS                 = 2.0;
double      DASH_ANGLE_STEP                = 45.0;
double      DASH_POWER_RATE                = 0.006;
int         DROP_BALL_TIME                 = 100;
double      EFFORT_DEC                     = 0.005;
double      EFFORT_DEC_THR                 = 0.3;
double      EFFORT_INC                     = 0.01;
double      EFFORT_INC_THR                 = 0.6;
double      EFFORT_INIT                    = 1.0;
double      EFFORT_MIN                     = 0.6;
int         EXTRA_HALF_TIME                = 100;
int         EXTRA_STAMINA                  = 50;
int         FORBID_KICK_OFF_OFFSIDE        = 1;
int         FOUL_CYCLES                    = 5;
double      FOUL_DETECT_PROBABILITY        = 0.5;
int         FOUL_EXPONENT                  = 10;
int         FREE_KICK_FAULTS               = 1;
int         FREEFORM_SEND_PERIOD           = 20;
int         FREEFORM_WAIT_PERIOD           = 600;
int         FULLSTATE_L                    = 0;
int         FULLSTATE_R                    = 0;
int         GAME_LOG_COMPRESSION           = 0;
int         GAME_LOG_DATED                 = 1;
std::string GAME_LOG_DIR                   = "./";
int         GAME_LOG_FIXED                 = 0;
std::string GAME_LOG_FIXED_NAME            = "rcssserver";
int         GAME_LOG_VERSION               = 5;
int         GAME_LOGGING                   = 1;
int         GAME_OVER_WAIT                 = 100;
double      GOAL_WIDTH                     = 14.02;
int         GOALIE_MAX_MOVES               = 2;
int         GOLDEN_GOAL                    = 0;
int         HALF_TIME                      = 300;
int         HEAR_DECAY                     = 1;
int         HEAR_INC                       = 1;
int         HEAR_MAX                       = 1;
int         INERTIA_MOMENT                 = 5;
int         KEEPAWAY                       = 1;
int         KEEPAWAY_LENGTH                = 20;
int         KEEPAWAY_LOG_DATED             = 1;
std::string KEEPAWAY_LOG_DIR               = "./";
int         KEEPAWAY_LOG_FIXED             = 0;
std::string KEEPAWAY_LOG_FIXED_NAME        = "rcssserver";
int         KEEPAWAY_LOGGING               = 1;
int         KEEPAWAY_START                 = -1;
int         KEEPAWAY_WIDTH                 = 20;
int         KICK_OFF_WAIT                  = 100;
double      KICK_POWER_RATE                = 0.027;
double      KICK_RAND                      = 0.1;
double      KICK_RAND_FACTOR_L             = 1.0;
double      KICK_RAND_FACTOR_R             = 1.0;
double      KICKABLE_MARGIN                = 0.7;
std::string LANDMARK_FILE                  = "~/.rcssserver-landmark.xml";
std::string LOG_DATE_FORMAT                = "%Y%m%d%H%M-";
int         LOG_TIMES                      = 0;
double      MAX_BACK_TACKLE_POWER          = 0.0;
double      MAX_DASH_ANGLE                 = 180.0;
double      MAX_DASH_POWER                 = 100.0;
int         MAX_GOAL_KICKS                 = 3;
double      MAX_TACKLE_POWER               = 100.0;
double      MAXMOMENT                      = 180.0;
double      MAXNECKANG                     = 90.0;
double      MAXNECKMOMENT                  = 180.0;
double      MAXPOWER                       = 100.0;
double      MIN_DASH_ANGLE                 = -180.0;
double      MIN_DASH_POWER                 = -100.0;
double      MINMOMENT                      = -180.0;
double      MINNECKANG                     = -90.0;
double      MINNECKMOMENT                  = -180.0;
double      MINPOWER                       = -100.0;
int         NR_EXTRA_HALFS                 = 2;
int         NR_NORMAL_HALFS                = 2;
double      OFFSIDE_ACTIVE_AREA_SIZE       = 2.5;
double      OFFSIDE_KICK_MARGIN            = 9.15;
int         OLCOACH_PORT                   = 6002;
int         OLD_COACH_HEAR                 = 0;
int         PEN_ALLOW_MULT_KICKS           = 1;
int         PEN_BEFORE_SETUP_WAIT          = 10;
int         PEN_COACH_MOVES_PLAYERS        = 1;
double      PEN_DIST_X                     = 42.5;
int         PEN_MAX_EXTRA_KICKS            = 5;
double      PEN_MAX_GOALIE_DIST_X          = 14.0;
int         PEN_NR_KICKS                   = 5;
double      PEN_RANDOM_WINNER              = 0;
int         PEN_READY_WAIT                 = 10;
int         PEN_SETUP_WAIT                 = 70;
int         PEN_TAKEN_WAIT                 = 150;
int         PENALTY_SHOOT_OUTS             = 1;
double      PLAYER_ACCEL_MAX               = 1.0;
double      PLAYER_DECAY                   = 0.4;
double      PLAYER_RAND                    = 0.1;
double      PLAYER_SIZE                    = 0.3;
double      PLAYER_SPEED_MAX               = 1.05;
double      PLAYER_SPEED_MAX_MIN           = 0.75;
double      PLAYER_WEIGHT                  = 60.0;
int         POINT_TO_BAN                   = 5;
int         POINT_TO_DURATION              = 20;
int         PORT                           = 6000;
double      PRAND_FACTOR_L                 = 1.0;
double      PRAND_FACTOR_R                 = 1.0;
int         PROFILE                        = 0;
int         PROPER_GOAL_KICKS              = 0;
double      QUANTIZE_STEP                  = 0.1;
double      QUANTIZE_STEP_L                = 0.01;
int         RECORD_MESSAGES                = 0;
double      RECOVER_DEC                    = 0.002;
double      RECOVER_DEC_THR                = 0.3;
double      RECOVER_INIT                   = 1.0;
double      RECOVER_MIN                    = 0.5;
int         RECV_STEP                      = 10;
double      RED_CARD_PROBABILITY           = 0.0;
int         SAY_COACH_CNT_MAX              = 128;
int         SAY_COACH_MSG_SIZE             = 128;
int         SAY_MSG_SIZE                   = 10;
int         SEND_COMMS                     = 0;
int         SEND_STEP                      = 150;
int         SEND_VI_STEP                   = 100;
int         SENSE_BODY_STEP                = 100;
double      SIDE_DASH_RATE                 = 0.4;
int         SIMULATOR_STEP                 = 100;
double      SLOW_DOWN_FACTOR               = 1.0;
double      SLOWNESS_ON_TOP_FOR_LEFT_TEAM  = 1.0;
double      SLOWNESS_ON_TOP_FOR_RIGHT_TEAM = 1.0;
int         STAMINA_CAPACITY               = 130600;
int         STAMINA_INC_MAX                = 45;
int         STAMINA_MAX                    = 8000;
int         START_GOAL_L                   = 0;
int         START_GOAL_R                   = 0;
double      STOPPED_BALL_VEL               = 0.01;
int         SYNCH_MICRO_SLEEP              = 1;
int         SYNCH_MODE                     = 0;
int         SYNCH_OFFSET                   = 60;
int         SYNCH_SEE_OFFSET               = 0;
double      TACKLE_BACK_DIST               = 0.0;
int         TACKLE_CYCLES                  = 10;
double      TACKLE_DIST                    = 2.0;
int         TACKLE_EXPONENT                = 6;
double      TACKLE_POWER_RATE              = 0.027;
double      TACKLE_RAND_FACTOR             = 2.0;
double      TACKLE_WIDTH                   = 1.25;
double      TEAM_ACTUATOR_NOISE            = 0.0;
std::string TEAM_L_START                   = "";
std::string TEAM_R_START                   = "";
int         TEXT_LOG_COMPRESSION           = 0;
int         TEXT_LOG_DATED                 = 1;
std::string TEXT_LOG_DIR                   = "./";
int         TEXT_LOG_FIXED                 = 0;
std::string TEXT_LOG_FIXED_NAME            = "rcssserver";
int         TEXT_LOGGING                   = 1;
int         USE_OFFSIDE                    = 1;
int         VERBOSE                        = 0;
double      VISIBLE_ANGLE                  = 90.0;
double      VISIBLE_DISTANCE               = 3.0;
double      WIND_ANG                       = 0.0;
double      WIND_DIR                       = 0.0;
double      WIND_FORCE                     = 0.0;
double      WIND_NONE                      = 0.0;
double      WIND_RAND                      = 0.0;
double      WIND_RANDOM                    = 0.0;

std::string _server_params = "";

Server(std::string server_params) {
	_server_params = server_params;
	AUDIO_CUT_DIST                 = atof((getParameter("audio_cut_dist").c_str()));
	AUTO_MODE                      = atoi((getParameter("auto_mode").c_str()));
	BACK_DASH_RATE                 = atof((getParameter("back_dash_rate").c_str()));
	BACK_PASSES                    = atoi((getParameter("back_passes").c_str()));
	BALL_ACCEL_MAX                 = atof((getParameter("ball_accel_max").c_str()));
	BALL_DECAY                     = atof((getParameter("ball_decay").c_str()));
	BALL_RAND                      = atof((getParameter("ball_rand").c_str()));
	BALL_SIZE                      = atof((getParameter("ball_size").c_str()));
	BALL_SPEED_MAX                 = atof((getParameter("ball_speed_max").c_str()));
	BALL_STUCK_AREA                = atof((getParameter("ball_stuck_area").c_str()));
	BALL_WEIGHT                    = atof((getParameter("ball_weight").c_str()));
	CATCH_BAN_CYCLE                = atoi((getParameter("catch_ban_cycle").c_str()));
	CATCH_PROBABILITY              = atof((getParameter("catch_probability").c_str()));
	CATCHABLE_AREA_L               = atof((getParameter("catchable_area_l").c_str()));
	CATCHABLE_AREA_W               = atof((getParameter("catchable_area_w").c_str()));
	CKICK_MARGIN                   = atof((getParameter("ckick_margin").c_str()));
	CLANG_ADVICE_WIN               = atoi((getParameter("clang_advice_win").c_str()));
	CLANG_DEFINE_WIN               = atoi((getParameter("clang_define_win").c_str()));
	CLANG_DEL_WIN                  = atoi((getParameter("clang_del_win").c_str()));
	CLANG_INFO_WIN                 = atoi((getParameter("clang_info_win").c_str()));
	CLANG_MESS_DELAY               = atoi((getParameter("clang_mess_delay").c_str()));
	CLANG_MESS_PER_CYCLE           = atoi((getParameter("clang_mess_per_cycle").c_str()));
	CLANG_META_WIN                 = atoi((getParameter("clang_meta_win").c_str()));
	CLANG_RULE_WIN                 = atoi((getParameter("clang_rule_win").c_str()));
	CLANG_WIN_SIZE                 = atoi((getParameter("clang_win_size").c_str()));
	COACH                          = atoi((getParameter("coach").c_str()));
	COACH_PORT                     = atoi((getParameter("coach_port").c_str()));
	COACH_W_REFEREE                = atoi((getParameter("coach_w_referee").c_str()));
	CONNECT_WAIT                   = atoi((getParameter("connect_wait").c_str()));
	CONTROL_RADIUS                 = atof((getParameter("control_radius").c_str()));
	DASH_ANGLE_STEP                = atof((getParameter("dash_angle_step").c_str()));
	DASH_POWER_RATE                = atof((getParameter("dash_power_rate").c_str()));
	DROP_BALL_TIME                 = atoi((getParameter("drop_ball_time").c_str()));
	EFFORT_DEC                     = atof((getParameter("effort_dec").c_str()));
	EFFORT_DEC_THR                 = atof((getParameter("effort_dec_thr").c_str()));
	EFFORT_INC                     = atof((getParameter("effort_inc").c_str()));
	EFFORT_INC_THR                 = atof((getParameter("effort_inc_thr").c_str()));
	EFFORT_INIT                    = atof((getParameter("effort_init").c_str()));
	EFFORT_MIN                     = atof((getParameter("effort_min").c_str()));
	EXTRA_HALF_TIME                = atoi((getParameter("extra_half_time").c_str()));
	EXTRA_STAMINA                  = atoi((getParameter("extra_stamina").c_str()));
	FORBID_KICK_OFF_OFFSIDE        = atoi((getParameter("forbid_kick_off_offside").c_str()));
	FOUL_CYCLES                    = atoi((getParameter("foul_cycles").c_str()));
	FOUL_DETECT_PROBABILITY        = atof((getParameter("foul_detect_probability").c_str()));
	FOUL_EXPONENT                  = atoi((getParameter("foul_exponent").c_str()));
	FREE_KICK_FAULTS               = atoi((getParameter("free_kick_faults").c_str()));
	FREEFORM_SEND_PERIOD           = atoi((getParameter("freeform_send_period").c_str()));
	FREEFORM_WAIT_PERIOD           = atoi((getParameter("freeform_wait_period").c_str()));
	FULLSTATE_L                    = atoi((getParameter("fullstate_l").c_str()));
	if (FULLSTATE_L > 0) {
		std::cout << "Using fullstate sensor for left team" << std::endl;
	}
	FULLSTATE_R                    = atoi((getParameter("fullstate_r").c_str()));
	if (FULLSTATE_R > 0) {
		std::cout << "Using fullstate sensor for right team" << std::endl;
	}
	GAME_LOG_COMPRESSION           = atoi((getParameter("game_log_compression").c_str()));
	GAME_LOG_DATED                 = atoi((getParameter("game_log_dated").c_str()));
	GAME_LOG_DIR                   = getParameter("game_log_dir");
	GAME_LOG_FIXED                 = atoi((getParameter("game_log_fixed").c_str()));
	GAME_LOG_FIXED_NAME            = getParameter("game_log_fixed_name");
	GAME_LOG_VERSION               = atoi((getParameter("game_log_version").c_str()));
	GAME_LOGGING                   = atoi((getParameter("game_logging").c_str()));
	GAME_OVER_WAIT                 = atoi((getParameter("game_over_wait").c_str()));
	GOAL_WIDTH                     = atof((getParameter("goal_width").c_str()));
	GOALIE_MAX_MOVES               = atoi((getParameter("goalie_max_moves").c_str()));
	GOLDEN_GOAL                    = atoi((getParameter("golden_goal").c_str()));
	HALF_TIME                      = atoi((getParameter("half_time").c_str()));
	HEAR_DECAY                     = atoi((getParameter("hear_decay").c_str()));
	HEAR_INC                       = atoi((getParameter("hear_inc").c_str()));
	HEAR_MAX                       = atoi((getParameter("hear_max").c_str()));
	INERTIA_MOMENT                 = atoi((getParameter("inertia_moment").c_str()));
	KEEPAWAY                       = atoi((getParameter("keepaway").c_str()));
	KEEPAWAY_LENGTH                = atoi((getParameter("keepaway_length").c_str()));
	KEEPAWAY_LOG_DATED             = atoi((getParameter("keepaway_log_dated").c_str()));
	KEEPAWAY_LOG_DIR               = getParameter("keepaway_log_dir");
	KEEPAWAY_LOG_FIXED             = atoi((getParameter("keepaway_log_fixed").c_str()));
	KEEPAWAY_LOG_FIXED_NAME        = getParameter("keepaway_log_fixed_name");
	KEEPAWAY_LOGGING               = atoi((getParameter("keepaway_logging").c_str()));
	KEEPAWAY_START                 = atoi((getParameter("keepaway_start").c_str()));
	KEEPAWAY_WIDTH                 = atoi((getParameter("keepaway_width").c_str()));
	KICK_OFF_WAIT                  = atoi((getParameter("kick_off_wait").c_str()));
	KICK_POWER_RATE                = atof((getParameter("kick_power_rate").c_str()));
	KICK_RAND                      = atof((getParameter("kick_rand").c_str()));
	KICK_RAND_FACTOR_L             = atof((getParameter("kick_rand_factor_l").c_str()));
	KICK_RAND_FACTOR_R             = atof((getParameter("kick_rand_factor_r").c_str()));
	KICKABLE_MARGIN                = atof((getParameter("kickable_margin").c_str()));
	LANDMARK_FILE                  = getParameter("landmark_file");
	LOG_DATE_FORMAT                = getParameter("log_date_format");
	LOG_TIMES                      = atoi((getParameter("log_times").c_str()));
	MAX_BACK_TACKLE_POWER          = atof((getParameter("max_back_tackle_power").c_str()));
	MAX_DASH_ANGLE                 = atof((getParameter("max_dash_angle").c_str()));
	MAX_DASH_POWER                 = atof((getParameter("max_dash_power").c_str()));
	MAX_GOAL_KICKS                 = atoi((getParameter("max_goal_kicks").c_str()));
	MAX_TACKLE_POWER               = atof((getParameter("max_tackle_power").c_str()));
	MAXMOMENT                      = atof((getParameter("maxmoment").c_str()));
	MAXNECKANG                     = atof((getParameter("maxneckang").c_str()));
	MAXNECKMOMENT                  = atof((getParameter("maxneckmoment").c_str()));
	MAXPOWER                       = atof((getParameter("maxpower").c_str()));
	MIN_DASH_ANGLE                 = atof((getParameter("min_dash_angle").c_str()));
	MIN_DASH_POWER                 = atof((getParameter("min_dash_power").c_str()));
	MINMOMENT                      = atof((getParameter("minmoment").c_str()));
	MINNECKANG                     = atof((getParameter("minneckang").c_str()));
	MINNECKMOMENT                  = atof((getParameter("minneckmoment").c_str()));
	MINPOWER                       = atof((getParameter("minpower").c_str()));
	NR_EXTRA_HALFS                 = atoi((getParameter("nr_extra_halfs").c_str()));
	NR_NORMAL_HALFS                = atoi((getParameter("nr_normal_halfs").c_str()));
	OFFSIDE_ACTIVE_AREA_SIZE       = atof((getParameter("offside_active_area_size").c_str()));
	OFFSIDE_KICK_MARGIN            = atof((getParameter("offside_kick_margin").c_str()));
	OLCOACH_PORT                   = atoi((getParameter("olcoach_port").c_str()));
	OLD_COACH_HEAR                 = atoi((getParameter("old_coach_hear").c_str()));
	PEN_ALLOW_MULT_KICKS           = atoi((getParameter("pen_allow_mult_kicks").c_str()));
	PEN_BEFORE_SETUP_WAIT          = atoi((getParameter("pen_before_setup_wait").c_str()));
	PEN_COACH_MOVES_PLAYERS        = atoi((getParameter("pen_coach_moves_players").c_str()));
	PEN_DIST_X                     = atof((getParameter("pen_dist_x").c_str()));
	PEN_MAX_EXTRA_KICKS            = atoi((getParameter("pen_max_extra_kicks").c_str()));
	PEN_MAX_GOALIE_DIST_X          = atof((getParameter("pen_max_goalie_dist_x").c_str()));
	PEN_NR_KICKS                   = atoi((getParameter("pen_nr_kicks").c_str()));
	PEN_RANDOM_WINNER              = atof((getParameter("pen_random_winner").c_str()));
	PEN_READY_WAIT                 = atoi((getParameter("pen_ready_wait").c_str()));
	PEN_SETUP_WAIT                 = atoi((getParameter("pen_setup_wait").c_str()));
	PEN_TAKEN_WAIT                 = atoi((getParameter("pen_taken_wait").c_str()));
	PENALTY_SHOOT_OUTS             = atoi((getParameter("penalty_shoot_outs").c_str()));
	PLAYER_ACCEL_MAX               = atof((getParameter("player_accel_max").c_str()));
	PLAYER_DECAY                   = atof((getParameter("player_decay").c_str()));
	PLAYER_RAND                    = atof((getParameter("player_rand").c_str()));
	PLAYER_SIZE                    = atof((getParameter("player_size").c_str()));
	PLAYER_SPEED_MAX               = atof((getParameter("player_speed_max").c_str()));
	PLAYER_SPEED_MAX_MIN           = atof((getParameter("player_speed_max_min").c_str()));
	PLAYER_WEIGHT                  = atof((getParameter("player_weight").c_str()));
	POINT_TO_BAN                   = atoi((getParameter("point_to_ban").c_str()));
	POINT_TO_DURATION              = atoi((getParameter("point_to_duration").c_str()));
	PORT                           = atoi((getParameter("port").c_str()));
	PRAND_FACTOR_L                 = atof((getParameter("prand_factor_l").c_str()));
	PRAND_FACTOR_R                 = atof((getParameter("prand_factor_r").c_str()));
	PROFILE                        = atoi((getParameter("profile").c_str()));
	PROPER_GOAL_KICKS              = atoi((getParameter("proper_goal_kicks").c_str()));
	QUANTIZE_STEP                  = atof((getParameter("quantize_step").c_str()));
	QUANTIZE_STEP_L                = atof((getParameter("quantize_step_l").c_str()));
	RECORD_MESSAGES                = atoi((getParameter("record_messages").c_str()));
	RECOVER_DEC                    = atof((getParameter("recover_dec").c_str()));
	RECOVER_DEC_THR                = atof((getParameter("recover_dec_thr").c_str()));
	RECOVER_INIT                   = atof((getParameter("recover_init").c_str()));
	RECOVER_MIN                    = atof((getParameter("recover_min").c_str()));
	RECV_STEP                      = atoi((getParameter("recv_step").c_str()));
	RED_CARD_PROBABILITY           = atof((getParameter("red_card_probability").c_str()));
	SAY_COACH_CNT_MAX              = atoi((getParameter("say_coach_cnt_max").c_str()));
	SAY_COACH_MSG_SIZE             = atoi((getParameter("say_coach_msg_size").c_str()));
	SAY_MSG_SIZE                   = atoi((getParameter("say_msg_size").c_str()));
	SEND_COMMS                     = atoi((getParameter("send_comms").c_str()));
	SEND_STEP                      = atoi((getParameter("send_step").c_str()));
	SEND_VI_STEP                   = atoi((getParameter("send_vi_step").c_str()));
	SENSE_BODY_STEP                = atoi((getParameter("sense_body_step").c_str()));
	SIDE_DASH_RATE                 = atof((getParameter("side_dash_rate").c_str()));
	SIMULATOR_STEP                 = atoi((getParameter("simulator_step").c_str()));
	SLOW_DOWN_FACTOR               = atof((getParameter("slow_down_factor").c_str()));
	SLOWNESS_ON_TOP_FOR_LEFT_TEAM  = atof((getParameter("slowness_on_top_for_left_team").c_str()));
	SLOWNESS_ON_TOP_FOR_RIGHT_TEAM = atof((getParameter("slowness_on_top_for_right_team").c_str()));
	STAMINA_CAPACITY               = atoi((getParameter("stamina_capacity").c_str()));
	STAMINA_INC_MAX                = atoi((getParameter("stamina_inc_max").c_str()));
	STAMINA_MAX                    = atoi((getParameter("stamina_max").c_str()));
	START_GOAL_L                   = atoi((getParameter("start_goal_l").c_str()));
	START_GOAL_R                   = atoi((getParameter("start_goal_r").c_str()));
	STOPPED_BALL_VEL               = atof((getParameter("stopped_ball_vel").c_str()));
	SYNCH_MICRO_SLEEP              = atoi((getParameter("synch_micro_sleep").c_str()));
	SYNCH_MODE                     = atoi((getParameter("synch_mode").c_str()));
	SYNCH_OFFSET                   = atoi((getParameter("synch_offset").c_str()));
	SYNCH_SEE_OFFSET               = atoi((getParameter("synch_see_offset").c_str()));
	TACKLE_BACK_DIST               = atof((getParameter("tackle_back_dist").c_str()));
	TACKLE_CYCLES                  = atoi((getParameter("tackle_cycles").c_str()));
	TACKLE_DIST                    = atof((getParameter("tackle_dist").c_str()));
	TACKLE_EXPONENT                = atoi((getParameter("tackle_exponent").c_str()));
	TACKLE_POWER_RATE              = atof((getParameter("tackle_power_rate").c_str()));
	TACKLE_RAND_FACTOR             = atof((getParameter("tackle_rand_factor").c_str()));
	TACKLE_WIDTH                   = atof((getParameter("tackle_width").c_str()));
	TEAM_ACTUATOR_NOISE            = atof((getParameter("team_actuator_noise").c_str()));
	TEAM_L_START                   = getParameter("team_l_start");
	TEAM_R_START                   = getParameter("team_r_start");
	TEXT_LOG_COMPRESSION           = atoi((getParameter("text_log_compression").c_str()));
	TEXT_LOG_DATED                 = atoi((getParameter("text_log_dated").c_str()));
	TEXT_LOG_DIR                   = getParameter("text_log_dir");
	TEXT_LOG_FIXED                 = atoi((getParameter("text_log_fixed").c_str()));
	TEXT_LOG_FIXED_NAME            = getParameter("text_log_fixed_name");
	TEXT_LOGGING                   = atoi((getParameter("text_logging").c_str()));
	USE_OFFSIDE                    = atoi((getParameter("use_offside").c_str()));
	VERBOSE                        = atoi((getParameter("verbose").c_str()));
	VISIBLE_ANGLE                  = atof((getParameter("visible_angle").c_str()));
	VISIBLE_DISTANCE               = atof((getParameter("visible_distance").c_str()));
	WIND_ANG                       = atof((getParameter("wind_ang").c_str()));
	WIND_DIR                       = atof((getParameter("wind_dir").c_str()));
	WIND_FORCE                     = atof((getParameter("wind_force").c_str()));
	WIND_NONE                      = atof((getParameter("wind_none").c_str()));
	WIND_RAND                      = atof((getParameter("wind_rand").c_str()));
	WIND_RANDOM                    = atof((getParameter("wind_random").c_str()));
}

std::string getParameter(std::string parameter) {
	boost::regex parameter_regex("\\(" + parameter + "\\s+([\\w\\-\\.~%\"/]*)\\)");
	boost::cmatch match;
	if (boost::regex_search(_server_params.c_str(), match, parameter_regex)) {
		return std::string() + match[1];
	} else {
		std::cerr << "Server::getParameter(string) -> search failed miserably for parameter " << parameter << std::endl;
		return "";
	}
}

}
