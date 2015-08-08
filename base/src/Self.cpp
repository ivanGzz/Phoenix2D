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
 * @file Self.cpp
 *
 * @author Nelson I. Gonzalez
 */

#include <cstdlib>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <boost/regex.hpp>
#include <boost/circular_buffer.hpp>
#include <ctime>
#include <boost/random.hpp>
#include <limits>
#include "constants.hpp"
#include "Command.hpp"
#include "Configs.hpp"
#include "Self.hpp"
#include "Server.hpp"
#include "Game.hpp"
#include "PFilter.hpp"
#include "functions.hpp"

namespace Phoenix {

namespace Self {

std::vector<int>    types_id;
std::vector<double> player_speed_max;
std::vector<double> stamina_inc_max;
std::vector<double> player_decay;
std::vector<double> inertia_moment;
std::vector<double> dash_power_rate;
std::vector<double> player_size;
std::vector<double> kickable_margin;
std::vector<double> kick_rand;
std::vector<double> extra_stamina;
std::vector<double> effort_max;
std::vector<double> effort_min;
std::vector<double> kick_power_rate;
std::vector<double> foul_detect_probability;
std::vector<double> catchable_area_l_stretch;
Filters::PFilter<4, 100> pfilter;
double d_min = std::numeric_limits<double>::min();

double u[3] = {0.0, 0.0, 0.0}; //{dash_power, dash_direction, turn_moment}

boost::regex sense_body_regex("^\\(sense_body\\s+\\d+\\s+"
		"\\(view_mode\\s+(\\w+)\\s+(\\w+)\\)\\s*" //group 1 group 2
		"\\(stamina\\s+([\\d\\.\\-e]+)\\s+([\\d\\.\\-e]+)\\s+([\\d\\.\\-e]+)\\)\\s*" //\\-\\d+|\\d+\\.\\d+ //group 3 group 4 group 5
		"\\(speed\\s+([\\d\\.\\-e]+)\\s+([\\d\\.\\-e]+)\\)\\s*" //group 6 group 7
		"\\(head_angle\\s+([\\d\\.\\-e]+)\\)\\s*" //group 8
		"\\(kick\\s+(\\d+)\\)\\s*" //group 9
		"\\(dash\\s+(\\d+)\\)\\s*" //group 10
		"\\(turn\\s+(\\d+)\\)\\s*" //group 11
		"\\(say\\s+(\\d+)\\)\\s*" //group 12
		"\\(turn_neck\\s+(\\d+)\\)\\s*" //group 13
		"\\(catch\\s+(\\d+)\\)\\s*" //group 14
		"\\(move\\s+(\\d+)\\)\\s*" //group 15
		"\\(change_view\\s+(\\d+)\\)\\s*" //group 16
		"\\(arm\\s+"
			"\\(movable\\s+(\\d+)\\)\\s*" //group 17
			"\\(expires\\s+(\\d+)\\)\\s*" //group 18
			"\\(target\\s+([\\d\\.\\-e]+)\\s+([\\d\\.\\-e]+)\\)\\s*" //group 19 20
			"\\(count\\s+(\\d+)\\)\\s*" //group 21
		"\\)\\s*"
		"\\(focus\\s+"
			"\\(target\\s+(none|[lr]\\s+\\d+)\\)\\s*" //group 22
			"\\(count\\s+(\\d+)\\)\\s*" //group 23
		"\\)\\s*"
		"\\(tackle\\s+"
				"\\(expires\\s+(\\d+)\\)\\s*" //group 24
				"\\(count\\s+(\\d+)\\)\\s*" //group 25
			"\\)\\s*"
			"\\(collision\\s+(none|\\(ball\\)|\\(player\\)|\\(post\\)|\\s)+\\)\\s*" //group 26
			"\\(foul\\s+"
				"\\(charged\\s+(\\d+)\\)\\s*" //group 27
				"\\(card\\s+(none|yellow|red)\\)\\s*" //group 28
			"\\)\\s*"
"\\)$");

bool   _positioned = false;
double _x          = 0.0;
double _y          = 0.0;
double _body       = 0.0;
std::list<Command*> last_commands_sent;
boost::circular_buffer<std::string> view_mode_width_buffer(Configs::BUFFER_MAX_HISTORY, "normal");
boost::circular_buffer<std::string> view_mode_quality_buffer(Configs::BUFFER_MAX_HISTORY, "high");
boost::circular_buffer<double>      stamina_buffer(Configs::BUFFER_MAX_HISTORY, 0.0);
boost::circular_buffer<double>      effort_buffer(Configs::BUFFER_MAX_HISTORY, 0.0);
boost::circular_buffer<double>      stamina_capacity_buffer(Configs::BUFFER_MAX_HISTORY, 0.0);
boost::circular_buffer<double>      amount_of_speed_buffer(Configs::BUFFER_MAX_HISTORY, 0.0);
boost::circular_buffer<double>      direction_of_speed_buffer(Configs::BUFFER_MAX_HISTORY, 0.0);
boost::circular_buffer<double>      head_angle_buffer(Configs::BUFFER_MAX_HISTORY, 0.0);
boost::circular_buffer<int>         kick_count_buffer(Configs::BUFFER_MAX_HISTORY, 0);
boost::circular_buffer<int>         dash_count_buffer(Configs::BUFFER_MAX_HISTORY, 0);
boost::circular_buffer<int>         turn_count_buffer(Configs::BUFFER_MAX_HISTORY, 0);
boost::circular_buffer<int>         say_count_buffer(Configs::BUFFER_MAX_HISTORY, 0);
boost::circular_buffer<int>         turn_neck_count_buffer(Configs::BUFFER_MAX_HISTORY, 0);
boost::circular_buffer<int>         catch_count_buffer(Configs::BUFFER_MAX_HISTORY, 0);
boost::circular_buffer<int> move_count_buffer(Configs::BUFFER_MAX_HISTORY, 0);
boost::circular_buffer<int> change_view_count_buffer(Configs::BUFFER_MAX_HISTORY, 0);
boost::circular_buffer<int> arm_movable_buffer(Configs::BUFFER_MAX_HISTORY, 0);
boost::circular_buffer<int> arm_expires_buffer(Configs::BUFFER_MAX_HISTORY, 0);
boost::circular_buffer<double> arm_dist_buffer(Configs::BUFFER_MAX_HISTORY, 0.0);
boost::circular_buffer<double> arm_dir_buffer(Configs::BUFFER_MAX_HISTORY, 0.0);
boost::circular_buffer<int> arm_count_buffer(Configs::BUFFER_MAX_HISTORY, 0);
boost::circular_buffer<std::string> focus_target_buffer(Configs::BUFFER_MAX_HISTORY, "none");
boost::circular_buffer<int> focus_count_buffer(Configs::BUFFER_MAX_HISTORY, 0);
boost::circular_buffer<int> tackle_expires_buffer(Configs::BUFFER_MAX_HISTORY, 0);
boost::circular_buffer<int> tackle_count_buffer(Configs::BUFFER_MAX_HISTORY, 0);
std::list<std::string> empty_vector;
boost::circular_buffer<std::list<std::string> > collisions_buffer(Configs::BUFFER_MAX_HISTORY, empty_vector);
boost::circular_buffer<int> foul_charged_buffer(Configs::BUFFER_MAX_HISTORY, 0);
boost::circular_buffer<std::string> foul_card_buffer(Configs::BUFFER_MAX_HISTORY, "none");

std::string TEAM_NAME                            = "Phoenix2D";
int         UNIFORM_NUMBER                       = 1;
std::string SIDE                                 = "l";
int         ALLOW_MULT_DEFAULT_TYPE              = 0;
double      CATCHABLE_AREA_L_STRECH_MAX          = 1.3;
double      CATCHABLE_AREA_L_STRECH_MIN          = 1.0;
double      DASH_POWER_RATE_DELTA_MAX            = 0.0;
double      DASH_POWER_RATE_DELTA_MIN            = 0.0;
double      EFFORT_MAX_DELTA_FACTOR              = -0.004;
double      EFFORT_MIN_DELTA_FACTOR              = -0.004;
double      EXTRA_STAMINA_DELTA_MAX              = 50.0;
double      EXTRA_STAMINA_DELTA_MIN              = 0.0;
double      FOUL_DETECT_PROBABILITY_DELTA_FACTOR = 0.0;
double      INERTIA_MOMENT_DELTA_FACTOR          = 25.0;
double      KICK_POWER_RATE_DELTA_MAX            = 0.0;
double      KICK_POWER_RATE_DELTA_MIN            = 0.0;
double      KICK_RAND_DELTA_FACTOR               = 1.0;
double      KICKABLE_MARGIN_DELTA_MAX            = 0.1;
double      KICKABLE_MARGIN_DELTA_MIN            = -0.1;
double      NEW_DASH_POWER_RATE_DELTA_MAX        = 0.0008;
double      NEW_DASH_POWER_RATE_DELTA_MIN        = -0.0012;
double      NEW_STAMINA_INC_MAX_DELTA_FACTOR     = -6000.0;
double      PLAYER_DECAY_DELTA_MAX               = 0.1;
double      PLAYER_DECAY_DELTA_MIN               = -0.1;
double      PLAYER_SIZE_DELTA_FACTOR             = -100.0;
double      PLAYER_SPEED_MAX_DELTA_MAX           = 0.0;
double      PLAYER_SPEED_MAX_DELTA_MIN           = 0.0;
int         PLAYER_TYPES                         = 18;
int         PT_MAX                               = 1;
int         RANDOM_SEED                          = 1325632690;
double      STAMINA_INC_MAX_DELTA_FACTOR         = 0.0;
int         SUBS_MAX                             = 3;
int         TYPE_ID                              = 0;
double      PLAYER_SPEED_MAX                     = 1.05;
double      STAMINA_INC_MAX                      = 45.0;
double      PLAYER_DECAY                         = 0.4;
double      INERTIA_MOMENT                       = 5.0;
double      DASH_POWER_RATE                      = 0.006;
double      PLAYER_SIZE                          = 0.3;
double      KICKABLE_MARGIN                      = 0.7;
double      KICK_RAND                            = 0.1;
double      EXTRA_STAMINA                        = 50.0;
double      EFFORT_MAX                           = 1.0;
double      EFFORT_MIN                           = 0.6;
double      KICK_POWER_RATE                      = 0.027;
double      FOUL_DETECT_PROBABILITY              = 0.5;
double      CATCHABLE_AREA_L_STRETCH             = 1.0;
double      ANGLE_VIEW 						     = 120.0;
std::string VIEW_MODE_WIDTH                      = "high";
std::string VIEW_MODE_QUALITY                    = "normal";
double      STAMINA                              = 8000.0;
double      EFFORT                               = 1.0;
double      STAMINA_CAPACITY                     = 130600.0;
double      AMOUNT_OF_SPEED                      = 0.0;
double      DIRECTION_OF_SPEED                   = 0.0;
double      HEAD_ANGLE                           = 0.0;
int         KICK_COUNT                           = 0;
int         DASH_COUNT                           = 0;
int         TURN_COUNT                           = 0;
int         SAY_COUNT                            = 0;
int         TURN_NECK_COUNT                      = 0;
int         CATCH_COUNT                          = 0;
int         MOVE_COUNT                           = 0;
int         CHANGE_VIEW_COUNT                    = 0;
int         ARM_MOVABLE                          = 0;
int         ARM_EXPIRES                          = 0;
double      ARM_DIST                             = 0.0;
double      ARM_DIR                              = 0.0;
int         ARM_COUNT                            = 0;
std::string FOCUS_TARGET                         = "none";
int         FOCUS_COUNT                          = 0;
int         TACKLE_EXPIRES                       = 0;
int         TACKLE_COUNT                         = 0;
std::list<std::string> COLLISION;              //empty
int         FOUL_CHARGED                         = 0;
std::string FOUL_CARD                            = "none";

std::string getPlayerTypeParameter(const std::string &player_type, std::string parameter) {
	boost::regex parameter_regex("\\(" + parameter + "\\s+([\\w\\-\\.]+)\\)");
	boost::cmatch match;
	if (boost::regex_search(player_type.c_str(), match, parameter_regex)) {
		std::string param = std::string() + match[1];
		return param;
	} else {
		std::cerr << "getParameter(string, string) -> search failed miserably for parameter " << parameter << std::endl;
		return "";
	}
}

std::string getPlayerParameter(const std::string &player_params, std::string parameter) {
	boost::regex parameter_regex("\\(" + parameter + "\\s+([\\w\\-\\.]+)\\)");
	boost::cmatch match;
	if (boost::regex_search(player_params.c_str(), match, parameter_regex)) {
		std::string param = std::string() + match[1];
		return param;
	} else {
		std::cerr << "getParameter(string) -> search failed miserably for parameter " << parameter << std::endl;
		return "";
	}
}

void parseServerParams(std::string player_params) {
	ALLOW_MULT_DEFAULT_TYPE              = atoi((getPlayerParameter(player_params, "allow_mult_default_type")).c_str());
	CATCHABLE_AREA_L_STRECH_MAX          = atof((getPlayerParameter(player_params, "catchable_area_l_stretch_max")).c_str());
	CATCHABLE_AREA_L_STRECH_MIN          = atof((getPlayerParameter(player_params, "catchable_area_l_stretch_min")).c_str());
	DASH_POWER_RATE_DELTA_MAX            = atof((getPlayerParameter(player_params, "dash_power_rate_delta_max")).c_str());
	DASH_POWER_RATE_DELTA_MIN            = atof((getPlayerParameter(player_params, "dash_power_rate_delta_min")).c_str());
	EFFORT_MAX_DELTA_FACTOR              = atof((getPlayerParameter(player_params, "effort_max_delta_factor")).c_str());
	EFFORT_MIN_DELTA_FACTOR              = atof((getPlayerParameter(player_params, "effort_min_delta_factor")).c_str());
	EXTRA_STAMINA_DELTA_MAX              = atof((getPlayerParameter(player_params, "extra_stamina_delta_max")).c_str());
	EXTRA_STAMINA_DELTA_MIN              = atof((getPlayerParameter(player_params, "extra_stamina_delta_min")).c_str());
	FOUL_DETECT_PROBABILITY_DELTA_FACTOR = atof((getPlayerParameter(player_params, "foul_detect_probability_delta_factor")).c_str());
	INERTIA_MOMENT_DELTA_FACTOR          = atof((getPlayerParameter(player_params, "inertia_moment_delta_factor")).c_str());
	KICK_POWER_RATE_DELTA_MAX            = atof((getPlayerParameter(player_params, "kick_power_rate_delta_max")).c_str());
	KICK_POWER_RATE_DELTA_MIN            = atof((getPlayerParameter(player_params, "kick_power_rate_delta_min")).c_str());
	KICK_RAND_DELTA_FACTOR               = atof((getPlayerParameter(player_params, "kick_rand_delta_factor")).c_str());
	KICKABLE_MARGIN_DELTA_MAX            = atof((getPlayerParameter(player_params, "kickable_margin_delta_max")).c_str());
	KICKABLE_MARGIN_DELTA_MIN            = atof((getPlayerParameter(player_params, "kickable_margin_delta_min")).c_str());
	NEW_DASH_POWER_RATE_DELTA_MAX        = atof((getPlayerParameter(player_params, "new_dash_power_rate_delta_max")).c_str());
	NEW_DASH_POWER_RATE_DELTA_MIN        = atof((getPlayerParameter(player_params, "new_dash_power_rate_delta_min")).c_str());
	NEW_STAMINA_INC_MAX_DELTA_FACTOR     = atof((getPlayerParameter(player_params, "new_stamina_inc_max_delta_factor")).c_str());
	PLAYER_DECAY_DELTA_MAX               = atof((getPlayerParameter(player_params, "player_decay_delta_max")).c_str());
	PLAYER_DECAY_DELTA_MIN               = atof((getPlayerParameter(player_params, "player_decay_delta_min")).c_str());
	PLAYER_SIZE_DELTA_FACTOR             = atof((getPlayerParameter(player_params, "player_size_delta_factor")).c_str());
	PLAYER_SPEED_MAX_DELTA_MAX           = atof((getPlayerParameter(player_params, "player_speed_max_delta_max")).c_str());
	PLAYER_SPEED_MAX_DELTA_MIN           = atof((getPlayerParameter(player_params, "player_speed_max_delta_min")).c_str());
	PLAYER_TYPES                         = atoi((getPlayerParameter(player_params, "player_types")).c_str());
	PT_MAX                               = atoi((getPlayerParameter(player_params, "pt_max")).c_str());
	RANDOM_SEED                          = atoi((getPlayerParameter(player_params, "random_seed")).c_str());
	STAMINA_INC_MAX_DELTA_FACTOR         = atof((getPlayerParameter(player_params, "stamina_inc_max_delta_factor")).c_str());
	SUBS_MAX                             = atoi((getPlayerParameter(player_params, "subs_max")).c_str());
	if (side[0] == 'r') {
		body = 180.0;
	}
}

void addPlayerType(std::string player_type) {
	types_id.push_back(atoi((getPlayerTypeParameter(player_type, "id")).c_str()));
	player_speed_max.push_back(atof((getPlayerTypeParameter(player_type, "player_speed_max")).c_str()));
	stamina_inc_max.push_back(atof((getPlayerTypeParameter(player_type, "stamina_inc_max")).c_str()));
	player_decay.push_back(atof((getPlayerTypeParameter(player_type, "player_decay")).c_str()));
	inertia_moment.push_back(atof((getPlayerTypeParameter(player_type, "inertia_moment")).c_str()));
	dash_power_rate.push_back(atof((getPlayerTypeParameter(player_type, "dash_power_rate")).c_str()));
	player_size.push_back(atof((getPlayerTypeParameter(player_type, "player_size")).c_str()));
	kickable_margin.push_back(atof((getPlayerTypeParameter(player_type, "player_size")).c_str()));
	kick_rand.push_back(atof((getPlayerTypeParameter(player_type, "kick_rand")).c_str()));
	extra_stamina.push_back(atof((getPlayerTypeParameter(player_type, "extra_stamina")).c_str()));
	effort_max.push_back(atof((getPlayerTypeParameter(player_type, "effort_max")).c_str()));
	effort_min.push_back(atof((getPlayerTypeParameter(player_type, "effort_min")).c_str()));
	kick_power_rate.push_back(atof((getPlayerTypeParameter(player_type, "kick_power_rate")).c_str()));
	foul_detect_probability.push_back(atof((getPlayerTypeParameter(player_type, "foul_detect_probability")).c_str()));
	catchable_area_l_stretch.push_back(atof((getPlayerTypeParameter(player_type, "catchable_area_l_stretch")).c_str()));
}

void parseSenseBody(std::string sense_body) {
	u[0] = u[1] = u[2] = 0.0;
	boost::cmatch match;
	if (boost::regex_match(sense_body.c_str(), match, sense_body_regex)) {
		Command* kick_ptr = 0;
		Command* dash_ptr = 0;
		Command* turn_ptr = 0;
		Command* say_ptr = 0;
		Command* turn_neck_ptr = 0;
		Command* catch_ptr = 0;
		Command* move_ptr = 0;
		Command* change_view_ptr = 0;
		Command* point_to_ptr = 0;
		Command* tackle_ptr = 0;
		for (std::list<Command*>::iterator it = last_commands_sent.begin(); it != last_commands_sent.end(); ++it) {
			switch ((*it)->commandType()) {
			case KICK:
				kick_ptr = *it;
				break;
			case DASH:
				dash_ptr = *it;
				break;
			case TURN:
				turn_ptr = *it;
				break;
			case SAY:
				say_ptr = *it;
				break;
			case TURN_NECK:
				turn_neck_ptr = *it;
				break;
			case CATCH:
				catch_ptr = *it;
				break;
			case MOVE:
				move_ptr = *it;
				break;
			case CHANGE_VIEW:
				change_view_ptr = *it;
				break;
			case POINT:
				point_to_ptr = *it;
				break;
			case TACKLE:
				tackle_ptr = *it;
				break;
			default:
				break;
			}
		}
		//view_mode_quality
		VIEW_MODE_QUALITY = match[1];
		view_mode_quality_buffer.push_front(VIEW_MODE_QUALITY);
		//view_mode_width
		VIEW_MODE_WIDTH = match[2];
		view_mode_width_buffer.push_front(VIEW_MODE_WIDTH);
		if (VIEW_MODE_WIDTH[1] == 'a') { // narrow
			ANGLE_VIEW = 60.0;
		} else if (VIEW_MODE_WIDTH[1] == 'o') { // normal
			ANGLE_VIEW = 120.0;
		} else { // wide
			ANGLE_VIEW = 180.0;
		}
		//stamina
		STAMINA = atof((std::string() + match[3]).c_str());
		stamina_buffer.push_front(STAMINA);
		//effort
		EFFORT = atof((std::string() + match[4]).c_str());
		effort_buffer.push_front(EFFORT);
		//stamina_capacity
		STAMINA_CAPACITY = atof((std::string() + match[5]).c_str());
		stamina_capacity_buffer.push_front(STAMINA_CAPACITY);
		//amount_of_speed
		AMOUNT_OF_SPEED = atof((std::string() + match[6]).c_str());
		amount_of_speed_buffer.push_front(AMOUNT_OF_SPEED);
		//direction_of_speed
		DIRECTION_OF_SPEED = atof((std::string() + match[7]).c_str());
		direction_of_speed_buffer.push_front(DIRECTION_OF_SPEED);
		//velocity = Geometry::Vector2D(AMOUNT_OF_SPEED, DIRECTION_OF_SPEED, true);
		//head_angle
		HEAD_ANGLE = atof((std::string() + match[8]).c_str());
		head_angle_buffer.push_front(HEAD_ANGLE);
		//kick_count
		KICK_COUNT = atoi((std::string() + match[9]).c_str());
		if (KICK_COUNT > kickCount(0)) {
			if (kick_ptr) kick_ptr->setStatus(EXECUTED);
		}
		kick_count_buffer.push_front(KICK_COUNT);
		//dash_count
		DASH_COUNT = atoi((std::string() + match[10]).c_str());
		if (DASH_COUNT > dashCount(0)) {
			if (dash_ptr) {
				u[0] = dash_ptr->dashPower();
				u[1] = dash_ptr->dashDirection();
				dash_ptr->setStatus(EXECUTED);
			}
		}
		dash_count_buffer.push_front(DASH_COUNT);
		//turn_count
		TURN_COUNT = atoi((std::string() + match[11]).c_str());
		if (TURN_COUNT > turnCount(0)) {
			if (turn_ptr) {
				u[2] = turn_ptr->turnMoment();
				turn_ptr->setStatus(EXECUTED);
			}
		}
		turn_count_buffer.push_front(TURN_COUNT);
		//say_count
		SAY_COUNT = atoi((std::string() + match[12]).c_str());
		if (SAY_COUNT > sayCount(0)) {
			if (say_ptr) say_ptr->setStatus(EXECUTED);
		}
		say_count_buffer.push_front(SAY_COUNT);
		//turn_neck_count
		TURN_NECK_COUNT = atoi((std::string() + match[13]).c_str());
		if (TURN_NECK_COUNT > turnNeckCount(0)) {
			if (turn_neck_ptr) turn_neck_ptr->setStatus(EXECUTED);
		}
		turn_neck_count_buffer.push_front(TURN_NECK_COUNT);
		//catch_count
		CATCH_COUNT = atoi((std::string() + match[14]).c_str());
		if (CATCH_COUNT > catchCount(0)) {
			if (catch_ptr) catch_ptr->setStatus(EXECUTED);
		}
		catch_count_buffer.push_front(CATCH_COUNT);
		//move_count
		MOVE_COUNT = atoi((std::string() + match[15]).c_str());
		if (MOVE_COUNT > moveCount(0)) {
			if (move_ptr) {
				x = move_ptr->moveX();
				y = move_ptr->moveY();
//				pfilter.initWithBelief(x, y, theta, 5.0, 5.0, 10.0);
				if (Configs::LOCALIZATION.compare("particlefilter") == 0) {
					std::cout << "Initializing pfilter" << std::endl;
					double mus[4];
					mus[0] = x;
					mus[1] = y;
					double dir_x = cos(body * Math::PI / 180.0);
					double dir_y = sin(body * Math::PI / 180.0);
					//std::cout << x << " " << y << " " << dir_x << " " << dir_y << std::endl;
					mus[2] = dir_x;
					mus[3] = dir_y;
					double devs[] = {5.0, 5.0, 0.2, 0.2};
					pfilter.initWithBelief(mus, devs);
				}
				positioned = true;
				move_ptr->setStatus(EXECUTED);
			}
		}
		move_count_buffer.push_front(MOVE_COUNT);
		//change_view_count
		CHANGE_VIEW_COUNT = atoi((std::string() + match[16]).c_str());
		if (CHANGE_VIEW_COUNT > changeViewCount(0)) {
			if (change_view_ptr) change_view_ptr->setStatus(EXECUTED);
		}
		change_view_count_buffer.push_front(CHANGE_VIEW_COUNT);
		//arm_movable
		ARM_MOVABLE = atoi((std::string() + match[17]).c_str());
		arm_movable_buffer.push_front(ARM_MOVABLE);
		//arm_expires
		ARM_EXPIRES = atoi((std::string() + match[18]).c_str());
		arm_expires_buffer.push_front(ARM_EXPIRES);
		//arm_dist
		ARM_DIST = atof((std::string() + match[19]).c_str());
		arm_dist_buffer.push_front(ARM_DIST);
		//arm_dir
		ARM_DIR = atof((std::string() + match[20]).c_str());
		arm_dir_buffer.push_front(ARM_DIR);
		//arm_count
		ARM_COUNT = atoi((std::string() + match[21]).c_str());
		if (ARM_COUNT > armCount(0)) {
			if (point_to_ptr) point_to_ptr->setStatus(EXECUTED);
		}
		arm_count_buffer.push_front(ARM_COUNT);
		//focus_target
		FOCUS_TARGET = match[22];
		focus_target_buffer.push_front(FOCUS_TARGET);
		//focus_count
		FOCUS_COUNT = atoi((std::string() + match[23]).c_str());
		focus_count_buffer.push_front(FOCUS_COUNT);
		//tackle_expires
		TACKLE_EXPIRES = atoi((std::string() + match[24]).c_str());
		tackle_expires_buffer.push_front(TACKLE_EXPIRES);
		//tackle_count
		TACKLE_COUNT = atoi((std::string() + match[25]).c_str());
		if (TACKLE_COUNT > tackleCount(0)) {
			if (tackle_ptr) tackle_ptr->setStatus(EXECUTED);
		}
		tackle_count_buffer.push_front(TACKLE_COUNT);
		//collisions
		std::string stream = std::string() + match[26];
		std::stringstream ss(stream);
		std::string token;
		std::list<std::string> collisions;
		while(std::getline(ss, token, ' ')) {
			collisions.push_back(token);
		}
		COLLISION = collisions;
		collisions_buffer.push_front(COLLISION);
		//foul_charged
		FOUL_CHARGED = atoi((std::string() + match[27]).c_str());
		foul_charged_buffer.push_front(FOUL_CHARGED);
		//foul_card
		FOUL_CARD = match[28];
		foul_card_buffer.push_front(FOUL_CARD);
	} else {
		std::cerr << "processSenseBody(string) -> failed to match " << sense_body << std::endl;
	}
}

void changePlayerType(int type) {
	if (type < PLAYER_TYPES) {
		PLAYER_SPEED_MAX         = player_speed_max[type];
		STAMINA_INC_MAX          = stamina_inc_max[type];
		PLAYER_DECAY             = player_decay[type];
		INERTIA_MOMENT           = inertia_moment[type];
		DASH_POWER_RATE          = dash_power_rate[type];
		PLAYER_SIZE              = player_size[type];
		KICKABLE_MARGIN          = kickable_margin[type];
		KICK_RAND                = kick_rand[type];
		EXTRA_STAMINA            = extra_stamina[type];
		EFFORT_MAX               = effort_max[type];
		EFFORT_MIN               = effort_min[type];
		KICK_POWER_RATE          = kick_power_rate[type];
		FOUL_DETECT_PROBABILITY  = foul_detect_probability[type];
		CATCHABLE_AREA_L_STRETCH = catchable_area_l_stretch[type];
	}
}

/**
 * (x - x0)^2 + (y - y0)^2 = d0
 * (x - x1)^2 + (y - y1)^2 = d1
 * Being:
 * k0 = d0^2 - x0^2 - y1^2
 * k1 = d1^2 - x1^2 - y1^2
 */
bool flagsTriangulation(Flag* flag0, Flag* flag1, double &x_t, double &y_t, double &theta_t, double &error_d) {
	double k0 = pow(flag0->distance(), 2.0) - pow(flag0->x(), 2.0) - pow(flag0->y(), 2.0);
	double k1 = pow(flag1->distance(), 2.0) - pow(flag1->x(), 2.0) - pow(flag1->y(), 2.0);
	double x0, x1, y0, y1, B, C;
	if (flag0->x() == flag1->x()) {
		double y = (k0 - k1) / (2.0 * (flag1->y() - flag0->y()));
		y0 = y;
		y1 = y;
		B = -2.0 * flag0->x();
		C = pow(y, 2.0) - 2.0 * y * flag0->y() - k0;
		if (pow(B, 2.0) - 4.0 * C > 0) {
			x0 = (-B + sqrt(pow(B, 2.0) - 4.0 * C)) / 2.0;
			x1 = (-B - sqrt(pow(B, 2.0) - 4.0 * C)) / 2.0;
		} else {
			return false;
		}
	} else if (flag0->y() == flag1->y()) {
		double x = (k0 - k1) / (2.0 * (flag1->x() - flag0->x()));
		x0 = x;
		x1 = x;
		B = -2.0 * flag0->y();
		C = pow(x, 2.0) - 2.0 * x * flag0->x() - k0;
		if (pow(B, 2.0) - 4.0 * C > 0) {
			y0 = (-B + sqrt(pow(B, 2.0) - 4.0 * C)) / 2.0;
			y1 = (-B - sqrt(pow(B, 2.0) - 4.0 * C)) / 2.0;
		} else {
			return false;
		}
	} else {
		double M = (k1 - k0) / (2.0 * (flag0->x() - flag1->x()));
		double N = (flag0->y() - flag1->y()) / (flag1->x() - flag0->x());
		B = (2.0 * (M * N - N * flag0->x() - flag0->y())) / (pow(N, 2.0) + 1.0);
		C = (pow(M, 2.0) - 2.0 * M * flag0->x() - k0) / (pow(N, 2.0) + 1.0);
		if (pow(B, 2.0) - 4.0 * C > 0) {
			y0 = (-B + sqrt(pow(B, 2.0) - 4.0 * C)) / 2.0;
			x0 = M + y0 * N;
			y1 = (-B - sqrt(pow(B, 2.0) - 4.0 * C)) / 2.0;
			x1 = M + y1 * N;
		} else {
			return false;
		}
	}
	double d0 = sqrt(pow(x0 - x, 2.0) + pow(y0 - y, 2.0));
	double d1 = sqrt(pow(x1 - x, 2.0) + pow(y1 - y, 2.0));
	double gamma0, gamma1;
	if (d0 < d1) {
		x_t = x0;
		y_t = y0;
	} else {
		x_t = x1;
		y_t = y1;
	}
	gamma0 = 180 * atan2(flag0->y() - y_t, flag0->x() - x_t) / Math::PI - flag0->direction();
	gamma1 = 180 * atan2(flag1->y() - y_t, flag1->x() - x_t) / Math::PI - flag1->direction();
	if (gamma0 >= 180.0) {
		gamma0 -= 360.0;
	} else if (gamma0 < -180.0) {
		gamma0 += 360.0;
	}
	if (gamma1 >= 180.0) {
		gamma1 -= 360.0;
	} else if (gamma1 < -180.0) {
		gamma1 += 360.0;
	}
	double x_m = (cos(Math::PI * gamma0 / 180.0) + cos(Math::PI * gamma1 / 180.0)) / 2.0;
	double y_m = (sin(Math::PI * gamma0 / 180.0) + sin(Math::PI * gamma1 / 180.0)) / 2.0;
	theta_t = 180.0 * atan2(y_m, x_m) / Math::PI;
	error_d = flag0->distanceError() + flag1->distanceError();
	return true;
}

double velc = 0.0;
double dire = 0.0;
double turn = 0.0;
std::vector<Flag> current_flags;
boost::mt19937 rngc(time(0));
boost::uniform_real<> distc(0.0, 2.0);

void predict(Filters::Particle<4> &particle) {
	double rdp = u[0] * (1.0 + Server::PLAYER_RAND * (-1.0 + distc(rngc)));
	double rtm = u[2] * (1.0 + Server::PLAYER_RAND * (-1.0 + distc(rngc)));
	double p_velc = amountOfSpeed(1) + effort(1) * DASH_POWER_RATE * rdp;
	if (p_velc > PLAYER_SPEED_MAX) {
		p_velc = PLAYER_SPEED_MAX;
	}
	double p_turn = rtm / (1.0 + Server::INERTIA_MOMENT * p_velc);
	double direction = 180.0 * atan2(particle.dimension[3], particle.dimension[2]) / Math::PI;
	particle.dimension[0] += p_velc * cos(Math::PI * direction / 180.0);
	particle.dimension[1] += p_velc * sin(Math::PI * direction / 180.0);
	direction += p_turn;
	if (direction > 180.0) {
		direction -= 360.0;
	} else if (direction < -180.0) {
		direction += 360.0;
	}
	particle.dimension[2] = cos(Math::PI * direction / 180.0);
	particle.dimension[3] = sin(Math::PI * direction / 180.0);
}

void update(Filters::Particle<4> &particle) {
	double pd = 180.0 * atan2(particle.dimension[3], particle.dimension[2]) / Math::PI;
	particle.weight = 1.0;
	for (std::vector<Flag>::iterator it = current_flags.begin(); it != current_flags.end(); ++it) {
		double x = sqrt(pow(particle.dimension[0] - it->x(), 2.0) + pow(particle.dimension[1] - it->y(), 2.0));
		double fd = 180.0 * atan2(it->y() - particle.dimension[1], it->x() - particle.dimension[0]) / Math::PI;
		double dir = fd - pd;
		if (dir > 180.0) {
			dir -= 360.0;
		} else if (dir < -180.0) {
			dir += 360.0;
		}
		double a = (it->max_distance + it->min_distance / 2.0;
		double b = 2.0 * it->distanceError();
		Math::Gaussian n(a, b);
		a = (it->max_direction + it->min_direction / 2.0;
		b = 4.0 * it->directionError();
		Math::Gaussian nd(a, b);
		particle.weight *= n.evaluate(x) * nd.evaluate(dir); //Math::uniform(u, x);
	}
	if (particle.weight == 0.0) {
		particle.weight = d_min;
	}
	//std::cout << particle.dimension[0] << " " << particle.dimension[1] << " " << pd << ": ";
	//std::cout << particle.weight << std::endl;
}

void triangulation(std::vector<Flag> flags) {
	std::vector<double> ds;
	double xt = 0.0, yt = 0.0;
	int counter = 0;
	for (std::vector<Flag>::iterator it_i = flags.begin(); it_i != flags.end() - 1; ++it_i) {
		for (std::vector<Flag>::iterator it_j = it_i + 1; it_j != flags.end(); ++it_j) {
			double x, y ,d, e;
			if (flagsTriangulation(&(*it_i), &(*it_j), x, y, d, e)) {
				ds.push_back(Geometry::toRadians(d));
				xt += x;
				yt += y;
				counter++;
			}
		}
	}
	if (counter > 0) {
		_x = xt / (double)counter;
		_y = yt / (double)counter;
		_body = Geometry::toDegrees(Math::arcsMean(ds)) - HEAD_ANGLE; //theta = angleMean(ds);
	} else {
		_body += turn;
		if (_body > 180.0) {
			_body -= 360.0;
		} else if (_body < -180.0) {
			_body += 360.0;
		}
		_x += velc * cos(Math::PI * _body / 180.0);
		_y += velc * sin(Math::PI * _body / 180.0);
	}
}

void lowpassfilter(std::vector<Flag> flags) {
	if (flags.size() == 0) {
		_body += turn;
		if (_body > 180.0) {
			_body -= 360.0;
		} else if (_body < -180.0) {
			_body += 360.0;
		}
		_x += velc * cos(Math::PI * body / 180.0);
		_y += velc * sin(Math::PI * body / 180.0);
		return;
	}
	std::vector<double> thetas;
	double x_e = _x;
	double y_e = _y;
	double tao = 0.6;
	switch (flags.size()) {
	case 1:
		tao = 0.3;
		break;
	case 2:
		tao = 0.4;
		break;
	case 3:
		tao = 0.5;
		break;
	default:
		break;
	}
	for (std::vector<Flag>::iterator it_flag = flags.begin(); it_flag != flags.end(); ++it_flag) {
		double dir = atan2(y_e - it_flag->y(), x_e - it_flag->x());
		double x_i = it_flag->x() + cos(dir) * it_flag->distance();
		double y_i = it_flag->y() + sin(dir) * it_flag->distance();
		x_e = tao * x_e + (1 - tao) * x_i;
		y_e = tao * y_e + (1 - tao) * y_i;
		double gamma = 180 * atan2(it_flag->y() - y_e, it_flag->x() - x_e) / Math::PI - it_flag->direction();
		thetas.push_back(Geometry::toRadians(gamma));
	}
	_x = x_e;
	_y = y_e;
	_body = Geometry::toDegrees(Math::arcsMean(thetas)) - HEAD_ANGLE; //theta = angleMean(thetas);
}

void particlefilter(std::vector<Flag> flags) {
	pfilter.predict(predict);
	if (flags.size() > 0) {
		current_flags = flags;
		pfilter.update(update);
		//std::cout << pfilter.getFit() << std::endl;
	}
	pfilter.resample();
	pfilter.computeParameters();
	_x = pfilter.getMean(0);
	_y = pfilter.getMean(1);
	_body = 180.0 * atan2(pfilter.getMean(3), pfilter.getMean(2)) / Math::PI - HEAD_ANGLE;
}

void localize(std::vector<Flag> flags) {
	if (!positioned) return;
	velc = amountOfSpeed(1) + effort(1) * DASH_POWER_RATE * u[0];
	if (velc > PLAYER_SPEED_MAX) {
		velc = PLAYER_SPEED_MAX;
	}
	turn = u[2] / (1.0 + INERTIA_MOMENT * velc);
	current_flags = flags;
	if (Configs::LOCALIZATION.compare("particlefilter") == 0) {
		particlefilter(flags);
	} else if (Configs::LOCALIZATION.compare("triangulation") == 0) {
		triangulation(flags);
	} else {
		lowpassfilter(flags);
	}
}

Position position() {
	return Position(_x, _y, _body, HEAD_ANGLE); //&position;
}

Geometry::Vector2D velocity() {
	return Geometry::Vector2D(AMOUNT_OF_SPEED, DIRECTION_OF_SPEED, true); //&velocity; //Vector2D::getVector2DWithMagnitudeAndDirection(AMOUNT_OF_SPEED, DIRECTION_OF_SPEED);
}

void setLastCommandsSet(std::list<Command*> last_commands_sent_t) {
	last_commands_sent.swap(last_commands_sent_t);
}

std::string viewModeWidth(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? view_mode_width_buffer[time] : "";
}

std::string viewModeQuality(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? view_mode_quality_buffer[time] : "";
}

double stamina(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? stamina_buffer[time] : 0.0;
}

double effort(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? effort_buffer[time] : 0.0;
}

double staminaCapacity(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? stamina_capacity_buffer[time] : 0.0;
}

double amountOfSpeed(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? amount_of_speed_buffer[time] : 0.0;
}

double directionOfSpeed(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? direction_of_speed_buffer[time] : 0.0;
}

int kickCount(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? kick_count_buffer[time] : 0;
}

int dashCount(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? dash_count_buffer[time] : 0;
}

int turnCount(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? turn_count_buffer[time] : 0;
}

int sayCount(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? say_count_buffer[time] : 0;
}

int turnNeckCount(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? turn_neck_count_buffer[time] : 0;
}

int catchCount(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? catch_count_buffer[time] : 0;
}

int moveCount(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? move_count_buffer[time] : 0;
}

int changeViewCount(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? change_view_count_buffer[time] : 0;
}

int armMovable(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? arm_movable_buffer[time] : 0;
}

int armExpires(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? arm_expires_buffer[time] : 0;
}

double armDistance(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? arm_dist_buffer[time] : 0.0;
}

double armDirection(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? arm_dir_buffer[time] : 0.0;
}

int armCount(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? arm_count_buffer[time] : 0;
}

std::string focusTarget(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? focus_target_buffer[time] : "";
}

int focusCount(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? focus_count_buffer[time] : 0;
}

int tackleExpires(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? tackle_expires_buffer[time] : 0;
}

int tackleCount(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? tackle_count_buffer[time] : 0;
}

std::list<std::string> collisions(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? collisions_buffer[time] : empty_vector;
}

int foulCharged(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? foul_charged_buffer[time] : 0;
}

std::string foulCard(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? foul_card_buffer[time] : "";
}

}

}
