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
 * @file Self.cpp
 *
 * @author Nelson Ivan Gonzalez
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

int    *types_id;
double *player_speed_max;
double *stamina_inc_max;
double *player_decay;
double *inertia_moment;
double *dash_power_rate;
double *player_size;
double *kickable_margin;
double *kick_rand;
double *extra_stamina;
double *effort_max;
double *effort_min;
double *kick_power_rate;
double *foul_detect_probability;
double *catchable_area_l_stretch;
Filters::PFilter<4> pfilter;
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

bool   positioned = false;
static double x          = 0.0;
static double y          = 0.0;
static double body       = 0.0;
static Position position;
static Geometry::Vector2D velocity;
static std::list<Command*> last_commands_sent;
static boost::circular_buffer<std::string> view_mode_width_buffer(Configs::BUFFER_MAX_HISTORY, "normal");
static boost::circular_buffer<std::string> view_mode_quality_buffer(Configs::BUFFER_MAX_HISTORY, "high");
static boost::circular_buffer<double> stamina_buffer(Configs::BUFFER_MAX_HISTORY, 0.0);
static boost::circular_buffer<double> effort_buffer(Configs::BUFFER_MAX_HISTORY, 0.0);
static boost::circular_buffer<double> stamina_capacity_buffer(Configs::BUFFER_MAX_HISTORY, 0.0);
static boost::circular_buffer<double> amount_of_speed_buffer(Configs::BUFFER_MAX_HISTORY, 0.0);
static boost::circular_buffer<double> direction_of_speed_buffer(Configs::BUFFER_MAX_HISTORY, 0.0);
static boost::circular_buffer<double> head_angle_buffer(Configs::BUFFER_MAX_HISTORY, 0.0);
static boost::circular_buffer<int> kick_count_buffer(Configs::BUFFER_MAX_HISTORY, 0);
static boost::circular_buffer<int> dash_count_buffer(Configs::BUFFER_MAX_HISTORY, 0);
static boost::circular_buffer<int> turn_count_buffer(Configs::BUFFER_MAX_HISTORY, 0);
static boost::circular_buffer<int> say_count_buffer(Configs::BUFFER_MAX_HISTORY, 0);
static boost::circular_buffer<int> turn_neck_count_buffer(Configs::BUFFER_MAX_HISTORY, 0);
static boost::circular_buffer<int> catch_count_buffer(Configs::BUFFER_MAX_HISTORY, 0);
static boost::circular_buffer<int> move_count_buffer(Configs::BUFFER_MAX_HISTORY, 0);
static boost::circular_buffer<int> change_view_count_buffer(Configs::BUFFER_MAX_HISTORY, 0);
static boost::circular_buffer<int> arm_movable_buffer(Configs::BUFFER_MAX_HISTORY, 0);
static boost::circular_buffer<int> arm_expires_buffer(Configs::BUFFER_MAX_HISTORY, 0);
static boost::circular_buffer<double> arm_dist_buffer(Configs::BUFFER_MAX_HISTORY, 0.0);
static boost::circular_buffer<double> arm_dir_buffer(Configs::BUFFER_MAX_HISTORY, 0.0);
static boost::circular_buffer<int> arm_count_buffer(Configs::BUFFER_MAX_HISTORY, 0);
static boost::circular_buffer<std::string> focus_target_buffer(Configs::BUFFER_MAX_HISTORY, "none");
static boost::circular_buffer<int> focus_count_buffer(Configs::BUFFER_MAX_HISTORY, 0);
static boost::circular_buffer<int> tackle_expires_buffer(Configs::BUFFER_MAX_HISTORY, 0);
static boost::circular_buffer<int> tackle_count_buffer(Configs::BUFFER_MAX_HISTORY, 0);
std::list<std::string> empty_vector;
static boost::circular_buffer<std::list<std::string> > collisions_buffer(Configs::BUFFER_MAX_HISTORY, empty_vector);
static boost::circular_buffer<int> foul_charged_buffer(Configs::BUFFER_MAX_HISTORY, 0);
static boost::circular_buffer<std::string> foul_card_buffer(Configs::BUFFER_MAX_HISTORY, "none");

std::string Self::TEAM_NAME                            = "Phoenix2D";
int         Self::UNIFORM_NUMBER                       = 1;
std::string Self::SIDE                                 = "l";
int         Self::ALLOW_MULT_DEFAULT_TYPE              = 0;
double      Self::CATCHABLE_AREA_L_STRECH_MAX          = 1.3;
double      Self::CATCHABLE_AREA_L_STRECH_MIN          = 1.0;
double      Self::DASH_POWER_RATE_DELTA_MAX            = 0.0;
double      Self::DASH_POWER_RATE_DELTA_MIN            = 0.0;
double      Self::EFFORT_MAX_DELTA_FACTOR              = -0.004;
double      Self::EFFORT_MIN_DELTA_FACTOR              = -0.004;
double      Self::EXTRA_STAMINA_DELTA_MAX              = 50.0;
double      Self::EXTRA_STAMINA_DELTA_MIN              = 0.0;
double      Self::FOUL_DETECT_PROBABILITY_DELTA_FACTOR = 0.0;
double      Self::INERTIA_MOMENT_DELTA_FACTOR          = 25.0;
double      Self::KICK_POWER_RATE_DELTA_MAX            = 0.0;
double      Self::KICK_POWER_RATE_DELTA_MIN            = 0.0;
double      Self::KICK_RAND_DELTA_FACTOR               = 1.0;
double      Self::KICKABLE_MARGIN_DELTA_MAX            = 0.1;
double      Self::KICKABLE_MARGIN_DELTA_MIN            = -0.1;
double      Self::NEW_DASH_POWER_RATE_DELTA_MAX        = 0.0008;
double      Self::NEW_DASH_POWER_RATE_DELTA_MIN        = -0.0012;
double      Self::NEW_STAMINA_INC_MAX_DELTA_FACTOR     = -6000.0;
double      Self::PLAYER_DECAY_DELTA_MAX               = 0.1;
double      Self::PLAYER_DECAY_DELTA_MIN               = -0.1;
double      Self::PLAYER_SIZE_DELTA_FACTOR             = -100.0;
double      Self::PLAYER_SPEED_MAX_DELTA_MAX           = 0.0;
double      Self::PLAYER_SPEED_MAX_DELTA_MIN           = 0.0;
int         Self::PLAYER_TYPES                         = 18;
int         Self::PT_MAX                               = 1;
int         Self::RANDOM_SEED                          = 1325632690;
double      Self::STAMINA_INC_MAX_DELTA_FACTOR         = 0.0;
int         Self::SUBS_MAX                             = 3;
int         Self::TYPE_ID                              = 0;
double      Self::PLAYER_SPEED_MAX                     = 1.05;
double      Self::STAMINA_INC_MAX                      = 45.0;
double      Self::PLAYER_DECAY                         = 0.4;
double      Self::INERTIA_MOMENT                       = 5.0;
double      Self::DASH_POWER_RATE                      = 0.006;
double      Self::PLAYER_SIZE                          = 0.3;
double      Self::KICKABLE_MARGIN                      = 0.7;
double      Self::KICK_RAND                            = 0.1;
double      Self::EXTRA_STAMINA                        = 50.0;
double      Self::EFFORT_MAX                           = 1.0;
double      Self::EFFORT_MIN                           = 0.6;
double      Self::KICK_POWER_RATE                      = 0.027;
double      Self::FOUL_DETECT_PROBABILITY              = 0.5;
double      Self::CATCHABLE_AREA_L_STRETCH             = 1.0;
std::string Self::VIEW_MODE_WIDTH                      = "high";
std::string Self::VIEW_MODE_QUALITY                    = "normal";
double      Self::STAMINA                              = 8000.0;
double      Self::EFFORT                               = 1.0;
double      Self::STAMINA_CAPACITY                     = 130600.0;
double      Self::AMOUNT_OF_SPEED                      = 0.0;
double      Self::DIRECTION_OF_SPEED                   = 0.0;
double      Self::HEAD_ANGLE                           = 0.0;
int         Self::KICK_COUNT                           = 0;
int         Self::DASH_COUNT                           = 0;
int         Self::TURN_COUNT                           = 0;
int         Self::SAY_COUNT                            = 0;
int         Self::TURN_NECK_COUNT                      = 0;
int         Self::CATCH_COUNT                          = 0;
int         Self::MOVE_COUNT                           = 0;
int         Self::CHANGE_VIEW_COUNT                    = 0;
int         Self::ARM_MOVABLE                          = 0;
int         Self::ARM_EXPIRES                          = 0;
double      Self::ARM_DIST                             = 0.0;
double      Self::ARM_DIR                              = 0.0;
int         Self::ARM_COUNT                            = 0;
std::string Self::FOCUS_TARGET                         = "none";
int         Self::FOCUS_COUNT                          = 0;
int         Self::TACKLE_EXPIRES                       = 0;
int         Self::TACKLE_COUNT                         = 0;
std::list<std::string> Self::COLLISION;              //empty
int         Self::FOUL_CHARGED                         = 0;
std::string Self::FOUL_CARD                            = "none";

std::string getPlayerTypeParameter(const std::string &player_type, std::string parameter) {
	boost::regex parameter_regex("\\(" + parameter + "\\s+([\\w\\-\\.]+)\\)");
	boost::cmatch match;
	if (boost::regex_search(player_type.c_str(), match, parameter_regex)) {
		std::string param = std::string() + match[1];
		return param;
	} else {
		std::cerr << "Self::getParameter(string, string) -> search failed miserably for parameter " << parameter << std::endl;
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
		std::cerr << "Self::getParameter(string) -> search failed miserably for parameter " << parameter << std::endl;
		return "";
	}
}

Self::Self(std::string player_params, std::string team_name, int unum, std::string side) {
	Self::TEAM_NAME = team_name;
	Self::UNIFORM_NUMBER = unum;
	Self::SIDE = side;
	Self::ALLOW_MULT_DEFAULT_TYPE              = atoi((getPlayerParameter(player_params, "allow_mult_default_type")).c_str());
	Self::CATCHABLE_AREA_L_STRECH_MAX          = atof((getPlayerParameter(player_params, "catchable_area_l_stretch_max")).c_str());
	Self::CATCHABLE_AREA_L_STRECH_MIN          = atof((getPlayerParameter(player_params, "catchable_area_l_stretch_min")).c_str());
	Self::DASH_POWER_RATE_DELTA_MAX            = atof((getPlayerParameter(player_params, "dash_power_rate_delta_max")).c_str());
	Self::DASH_POWER_RATE_DELTA_MIN            = atof((getPlayerParameter(player_params, "dash_power_rate_delta_min")).c_str());
	Self::EFFORT_MAX_DELTA_FACTOR              = atof((getPlayerParameter(player_params, "effort_max_delta_factor")).c_str());
	Self::EFFORT_MIN_DELTA_FACTOR              = atof((getPlayerParameter(player_params, "effort_min_delta_factor")).c_str());
	Self::EXTRA_STAMINA_DELTA_MAX              = atof((getPlayerParameter(player_params, "extra_stamina_delta_max")).c_str());
	Self::EXTRA_STAMINA_DELTA_MIN              = atof((getPlayerParameter(player_params, "extra_stamina_delta_min")).c_str());
	Self::FOUL_DETECT_PROBABILITY_DELTA_FACTOR = atof((getPlayerParameter(player_params, "foul_detect_probability_delta_factor")).c_str());
	Self::INERTIA_MOMENT_DELTA_FACTOR          = atof((getPlayerParameter(player_params, "inertia_moment_delta_factor")).c_str());
	Self::KICK_POWER_RATE_DELTA_MAX            = atof((getPlayerParameter(player_params, "kick_power_rate_delta_max")).c_str());
	Self::KICK_POWER_RATE_DELTA_MIN            = atof((getPlayerParameter(player_params, "kick_power_rate_delta_min")).c_str());
	Self::KICK_RAND_DELTA_FACTOR               = atof((getPlayerParameter(player_params, "kick_rand_delta_factor")).c_str());
	Self::KICKABLE_MARGIN_DELTA_MAX            = atof((getPlayerParameter(player_params, "kickable_margin_delta_max")).c_str());
	Self::KICKABLE_MARGIN_DELTA_MIN            = atof((getPlayerParameter(player_params, "kickable_margin_delta_min")).c_str());
	Self::NEW_DASH_POWER_RATE_DELTA_MAX        = atof((getPlayerParameter(player_params, "new_dash_power_rate_delta_max")).c_str());
	Self::NEW_DASH_POWER_RATE_DELTA_MIN        = atof((getPlayerParameter(player_params, "new_dash_power_rate_delta_min")).c_str());
	Self::NEW_STAMINA_INC_MAX_DELTA_FACTOR     = atof((getPlayerParameter(player_params, "new_stamina_inc_max_delta_factor")).c_str());
	Self::PLAYER_DECAY_DELTA_MAX               = atof((getPlayerParameter(player_params, "player_decay_delta_max")).c_str());
	Self::PLAYER_DECAY_DELTA_MIN               = atof((getPlayerParameter(player_params, "player_decay_delta_min")).c_str());
	Self::PLAYER_SIZE_DELTA_FACTOR             = atof((getPlayerParameter(player_params, "player_size_delta_factor")).c_str());
	Self::PLAYER_SPEED_MAX_DELTA_MAX           = atof((getPlayerParameter(player_params, "player_speed_max_delta_max")).c_str());
	Self::PLAYER_SPEED_MAX_DELTA_MIN           = atof((getPlayerParameter(player_params, "player_speed_max_delta_min")).c_str());
	Self::PLAYER_TYPES                         = atoi((getPlayerParameter(player_params, "player_types")).c_str());
	Self::PT_MAX                               = atoi((getPlayerParameter(player_params, "pt_max")).c_str());
	Self::RANDOM_SEED                          = atoi((getPlayerParameter(player_params, "random_seed")).c_str());
	Self::STAMINA_INC_MAX_DELTA_FACTOR         = atof((getPlayerParameter(player_params, "stamina_inc_max_delta_factor")).c_str());
	Self::SUBS_MAX                             = atoi((getPlayerParameter(player_params, "subs_max")).c_str());
	types_id = new int[Self::PLAYER_TYPES];
	player_speed_max = new double[Self::PLAYER_TYPES];
	stamina_inc_max = new double[Self::PLAYER_TYPES];
	player_decay = new double[Self::PLAYER_TYPES];
	inertia_moment = new double[Self::PLAYER_TYPES];
	dash_power_rate = new double[Self::PLAYER_TYPES];
	player_size = new double[Self::PLAYER_TYPES];
	kickable_margin = new double[Self::PLAYER_TYPES];
	kick_rand = new double[Self::PLAYER_TYPES];
	extra_stamina = new double[Self::PLAYER_TYPES];
	effort_max = new double[Self::PLAYER_TYPES];
	effort_min = new double[Self::PLAYER_TYPES];
	kick_power_rate = new double[Self::PLAYER_TYPES];
	foul_detect_probability = new double[Self::PLAYER_TYPES];
	catchable_area_l_stretch = new double[Self::PLAYER_TYPES];
	if (side.compare("r") == 0) {
		body = 180.0;
	}
	Flag::initializeField();
}

Self::~Self() {
	if (Configs::VERBOSE) std::cout << "Self out" << std::endl;
	if (types_id)                 delete[] types_id;
	if (player_speed_max)         delete[] player_speed_max;
	if (stamina_inc_max)          delete[] stamina_inc_max;
	if (player_decay)             delete[] player_decay;
	if (inertia_moment)           delete[] inertia_moment;
	if (dash_power_rate)          delete[] dash_power_rate;
	if (player_size)              delete[] player_size;
	if (kickable_margin)          delete[] kickable_margin;
	if (kick_rand)                delete[] kick_rand;
	if (extra_stamina)            delete[] extra_stamina;
	if (effort_max)               delete[] effort_max;
	if (effort_min)               delete[] effort_min;
	if (kick_power_rate)          delete[] kick_power_rate;
	if (foul_detect_probability)  delete[] foul_detect_probability;
	if (catchable_area_l_stretch) delete[] catchable_area_l_stretch;
}

void Self::addPlayerType(std::string player_type) {
	int id = atoi((getPlayerTypeParameter(player_type, "id")).c_str());
	types_id[id]                 = id;
	player_speed_max[id]         = atof((getPlayerTypeParameter(player_type, "player_speed_max")).c_str());
	stamina_inc_max[id]          = atof((getPlayerTypeParameter(player_type, "stamina_inc_max")).c_str());
	player_decay[id]             = atof((getPlayerTypeParameter(player_type, "player_decay")).c_str());
	inertia_moment[id]           = atof((getPlayerTypeParameter(player_type, "inertia_moment")).c_str());
	dash_power_rate[id]          = atof((getPlayerTypeParameter(player_type, "dash_power_rate")).c_str());
	player_size[id]              = atof((getPlayerTypeParameter(player_type, "player_size")).c_str());
	kickable_margin[id]          = atof((getPlayerTypeParameter(player_type, "player_size")).c_str());
	kick_rand[id]                = atof((getPlayerTypeParameter(player_type, "kick_rand")).c_str());
	extra_stamina[id]            = atof((getPlayerTypeParameter(player_type, "extra_stamina")).c_str());
	effort_max[id]               = atof((getPlayerTypeParameter(player_type, "effort_max")).c_str());
	effort_min[id]               = atof((getPlayerTypeParameter(player_type, "effort_min")).c_str());
	kick_power_rate[id]          = atof((getPlayerTypeParameter(player_type, "kick_power_rate")).c_str());
	foul_detect_probability[id]  = atof((getPlayerTypeParameter(player_type, "foul_detect_probability")).c_str());
	catchable_area_l_stretch[id] = atof((getPlayerTypeParameter(player_type, "catchable_area_l_stretch")).c_str());
}

void Self::processSenseBody(std::string sense_body) {
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
			switch ((*it)->getCommandType()) {
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
		Self::VIEW_MODE_QUALITY = match[1];
		view_mode_quality_buffer.push_front(Self::VIEW_MODE_QUALITY);
		//view_mode_width
		Self::VIEW_MODE_WIDTH = match[2];
		view_mode_width_buffer.push_front(Self::VIEW_MODE_WIDTH);
		//stamina
		Self::STAMINA = atof((std::string() + match[3]).c_str());
		stamina_buffer.push_front(Self::STAMINA);
		//effort
		Self::EFFORT = atof((std::string() + match[4]).c_str());
		effort_buffer.push_front(Self::EFFORT);
		//stamina_capacity
		Self::STAMINA_CAPACITY = atof((std::string() + match[5]).c_str());
		stamina_capacity_buffer.push_front(Self::STAMINA_CAPACITY);
		//amount_of_speed
		Self::AMOUNT_OF_SPEED = atof((std::string() + match[6]).c_str());
		amount_of_speed_buffer.push_front(Self::AMOUNT_OF_SPEED);
		//direction_of_speed
		Self::DIRECTION_OF_SPEED = atof((std::string() + match[7]).c_str());
		direction_of_speed_buffer.push_front(Self::DIRECTION_OF_SPEED);
		velocity = Geometry::Vector2D(AMOUNT_OF_SPEED, DIRECTION_OF_SPEED, true);
		//head_angle
		Self::HEAD_ANGLE = atof((std::string() + match[8]).c_str());
		head_angle_buffer.push_front(Self::HEAD_ANGLE);
		//kick_count
		Self::KICK_COUNT = atoi((std::string() + match[9]).c_str());
		if (Self::KICK_COUNT > Self::getKickCountAtTime(0)) {
			if (kick_ptr) kick_ptr->changeStatusTo(EXECUTED);
		}
		kick_count_buffer.push_front(Self::KICK_COUNT);
		//dash_count
		Self::DASH_COUNT = atoi((std::string() + match[10]).c_str());
		if (Self::DASH_COUNT > Self::getDashCountAtTime(0)) {
			if (dash_ptr) {
				u[0] = dash_ptr->getDashPower();
				u[1] = dash_ptr->getDashDirection();
				dash_ptr->changeStatusTo(EXECUTED);
			}
		}
		dash_count_buffer.push_front(Self::DASH_COUNT);
		//turn_count
		Self::TURN_COUNT = atoi((std::string() + match[11]).c_str());
		if (Self::TURN_COUNT > Self::getTurnCountAtTime(0)) {
			if (turn_ptr) {
				u[2] = turn_ptr->getTurnMoment();
				turn_ptr->changeStatusTo(EXECUTED);
			}
		}
		turn_count_buffer.push_front(Self::TURN_COUNT);
		//say_count
		Self::SAY_COUNT = atoi((std::string() + match[12]).c_str());
		if (Self::SAY_COUNT > Self::getSayCountAtTime(0)) {
			if (say_ptr) say_ptr->changeStatusTo(EXECUTED);
		}
		say_count_buffer.push_front(Self::SAY_COUNT);
		//turn_neck_count
		Self::TURN_NECK_COUNT = atoi((std::string() + match[13]).c_str());
		if (Self::TURN_NECK_COUNT > Self::getTurnNeckCountAtTime(0)) {
			if (turn_neck_ptr) turn_neck_ptr->changeStatusTo(EXECUTED);
		}
		turn_neck_count_buffer.push_front(Self::TURN_NECK_COUNT);
		//catch_count
		Self::CATCH_COUNT = atoi((std::string() + match[14]).c_str());
		if (Self::CATCH_COUNT > Self::getCatchCountAtTime(0)) {
			if (catch_ptr) catch_ptr->changeStatusTo(EXECUTED);
		}
		catch_count_buffer.push_front(Self::CATCH_COUNT);
		//move_count
		Self::MOVE_COUNT = atoi((std::string() + match[15]).c_str());
		if (Self::MOVE_COUNT > Self::getMoveCountAtTime(0)) {
			if (move_ptr) {
				x = move_ptr->getMoveX();
				y = move_ptr->getMoveY();
				position = Position(x, y, body);
//				pfilter.initWithBelief(x, y, theta, 5.0, 5.0, 10.0);
				if (Configs::LOCALIZATION.compare("particlefilter") == 0) {
					std::cout << "Initializing pfilter" << std::endl;
					double mus[4];
					mus[0] = x;
					mus[1] = y;
					double dir_x = cos(body * Math::PI / 180.0);
					double dir_y = sin(body * Math::PI / 180.0);
					std::cout << x << " " << y << " " << dir_x << " " << dir_y << std::endl;
					mus[2] = dir_x;
					mus[3] = dir_y;
					double devs[] = {5.0, 5.0, 0.2, 0.2};
					pfilter.initWithBelief(mus, devs);
				}
				positioned = true;
				move_ptr->changeStatusTo(EXECUTED);
			}
		}
		move_count_buffer.push_front(Self::MOVE_COUNT);
		//change_view_count
		Self::CHANGE_VIEW_COUNT = atoi((std::string() + match[16]).c_str());
		if (Self::CHANGE_VIEW_COUNT > Self::getChangeViewCountAtTime(0)) {
			if (change_view_ptr) change_view_ptr->changeStatusTo(EXECUTED);
		}
		change_view_count_buffer.push_front(Self::CHANGE_VIEW_COUNT);
		//arm_movable
		Self::ARM_MOVABLE = atoi((std::string() + match[17]).c_str());
		arm_movable_buffer.push_front(Self::ARM_MOVABLE);
		//arm_expires
		Self::ARM_EXPIRES = atoi((std::string() + match[18]).c_str());
		arm_expires_buffer.push_front(Self::ARM_EXPIRES);
		//arm_dist
		Self::ARM_DIST = atof((std::string() + match[19]).c_str());
		arm_dist_buffer.push_front(Self::ARM_DIST);
		//arm_dir
		Self::ARM_DIR = atof((std::string() + match[20]).c_str());
		arm_dir_buffer.push_front(Self::ARM_DIR);
		//arm_count
		Self::ARM_COUNT = atoi((std::string() + match[21]).c_str());
		if (Self::ARM_COUNT > Self::getArmCountAtTime(0)) {
			if (point_to_ptr) point_to_ptr->changeStatusTo(EXECUTED);
		}
		arm_count_buffer.push_front(Self::ARM_COUNT);
		//focus_target
		Self::FOCUS_TARGET = match[22];
		focus_target_buffer.push_front(Self::FOCUS_TARGET);
		//focus_count
		Self::FOCUS_COUNT = atoi((std::string() + match[23]).c_str());
		focus_count_buffer.push_front(Self::FOCUS_COUNT);
		//tackle_expires
		Self::TACKLE_EXPIRES = atoi((std::string() + match[24]).c_str());
		tackle_expires_buffer.push_front(Self::TACKLE_EXPIRES);
		//tackle_count
		Self::TACKLE_COUNT = atoi((std::string() + match[25]).c_str());
		if (Self::TACKLE_COUNT > Self::getTackleCountAtTime(0)) {
			if (tackle_ptr) tackle_ptr->changeStatusTo(EXECUTED);
		}
		tackle_count_buffer.push_front(Self::TACKLE_COUNT);
		//collisions
		std::string stream = std::string() + match[26];
		std::stringstream ss(stream);
		std::string token;
		std::list<std::string> collisions;
		while(std::getline(ss, token, ' ')) {
			collisions.push_back(token);
		}
		Self::COLLISION = collisions;
		collisions_buffer.push_front(Self::COLLISION);
		//foul_charged
		Self::FOUL_CHARGED = atoi((std::string() + match[27]).c_str());
		foul_charged_buffer.push_front(Self::FOUL_CHARGED);
		//foul_card
		Self::FOUL_CARD = match[28];
		foul_card_buffer.push_front(Self::FOUL_CARD);
	} else {
		std::cerr << "Self::processSenseBody(string) -> failed to match " << sense_body << std::endl;
	}
}

void Self::changePlayerType(int type) {
	if (type < Self::PLAYER_TYPES) {
		Self::PLAYER_SPEED_MAX         = player_speed_max[type];
		Self::STAMINA_INC_MAX          = stamina_inc_max[type];
		Self::PLAYER_DECAY             = player_decay[type];
		Self::INERTIA_MOMENT           = inertia_moment[type];
		Self::DASH_POWER_RATE          = dash_power_rate[type];
		Self::PLAYER_SIZE              = player_size[type];
		Self::KICKABLE_MARGIN          = kickable_margin[type];
		Self::KICK_RAND                = kick_rand[type];
		Self::EXTRA_STAMINA            = extra_stamina[type];
		Self::EFFORT_MAX               = effort_max[type];
		Self::EFFORT_MIN               = effort_min[type];
		Self::KICK_POWER_RATE          = kick_power_rate[type];
		Self::FOUL_DETECT_PROBABILITY  = foul_detect_probability[type];
		Self::CATCHABLE_AREA_L_STRETCH = catchable_area_l_stretch[type];
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
	double k0 = pow(flag0->getDistance(), 2.0) - pow(flag0->getX(), 2.0) - pow(flag0->getY(), 2.0);
	double k1 = pow(flag1->getDistance(), 2.0) - pow(flag1->getX(), 2.0) - pow(flag1->getY(), 2.0);
	double x0, x1, y0, y1, B, C;
	if (flag0->getX() == flag1->getX()) {
		double y = (k0 - k1) / (2.0 * (flag1->getY() - flag0->getY()));
		y0 = y;
		y1 = y;
		B = -2.0 * flag0->getX();
		C = pow(y, 2.0) - 2.0 * y * flag0->getY() - k0;
		if (pow(B, 2.0) - 4.0 * C > 0) {
			x0 = (-B + sqrt(pow(B, 2.0) - 4.0 * C)) / 2.0;
			x1 = (-B - sqrt(pow(B, 2.0) - 4.0 * C)) / 2.0;
		} else {
			return false;
		}
	} else if (flag0->getY() == flag1->getY()) {
		double x = (k0 - k1) / (2.0 * (flag1->getX() - flag0->getX()));
		x0 = x;
		x1 = x;
		B = -2.0 * flag0->getY();
		C = pow(x, 2.0) - 2.0 * x * flag0->getX() - k0;
		if (pow(B, 2.0) - 4.0 * C > 0) {
			y0 = (-B + sqrt(pow(B, 2.0) - 4.0 * C)) / 2.0;
			y1 = (-B - sqrt(pow(B, 2.0) - 4.0 * C)) / 2.0;
		} else {
			return false;
		}
	} else {
		double M = (k1 - k0) / (2.0 * (flag0->getX() - flag1->getX()));
		double N = (flag0->getY() - flag1->getY()) / (flag1->getX() - flag0->getX());
		B = (2.0 * (M * N - N * flag0->getX() - flag0->getY())) / (pow(N, 2.0) + 1.0);
		C = (pow(M, 2.0) - 2.0 * M * flag0->getX() - k0) / (pow(N, 2.0) + 1.0);
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
	gamma0 = 180 * atan2(flag0->getY() - y_t, flag0->getX() - x_t) / Math::PI - flag0->getDirection();
	gamma1 = 180 * atan2(flag1->getY() - y_t, flag1->getX() - x_t) / Math::PI - flag1->getDirection();
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
	error_d = flag0->getDistanceError() + flag1->getDistanceError();
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
	double p_velc = Self::getAmountOfSpeedAtTime(1) + Self::getEffortAtTime(1) * Self::DASH_POWER_RATE * rdp;
	if (p_velc > Self::PLAYER_SPEED_MAX) {
		p_velc = Self::PLAYER_SPEED_MAX;
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
		double x = sqrt(pow(particle.dimension[0] - it->getX(), 2.0) + pow(particle.dimension[1] - it->getY(), 2.0));
		double fd = 180.0 * atan2(it->getY() - particle.dimension[1], it->getX() - particle.dimension[0]) / Math::PI;
		double dir = fd - pd;
		if (dir > 180.0) {
			dir -= 360.0;
		} else if (dir < -180.0) {
			dir += 360.0;
		}
		double a = (it->getMaxDistance() + it->getMinDistance()) / 2.0;
		double b = 4.0 * it->getDistanceError();
		Math::UGaussian n(a, b);
		a = (it->getMaxDirection() + it->getMinDirection()) / 2.0;
		b = 4.0 * it->getDirectionError();
		Math::UGaussian nd(a, b);
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
		x = xt / (double)counter;
		y = yt / (double)counter;
		body = Geometry::toDegrees(Math::arcsMean(ds)) - Self::HEAD_ANGLE; //theta = angleMean(ds);
	} else {
		body += turn;
		if (body > 180.0) {
			body -= 360.0;
		} else if (body < -180.0) {
			body += 360.0;
		}
		x += velc * cos(Math::PI * body / 180.0);
		y += velc * sin(Math::PI * body / 180.0);
	}
}

void lowpassfilter(std::vector<Flag> flags) {
	if (flags.size() == 0) {
		body += turn;
		if (body > 180.0) {
			body -= 360.0;
		} else if (body < -180.0) {
			body += 360.0;
		}
		x += velc * cos(Math::PI * body / 180.0);
		y += velc * sin(Math::PI * body / 180.0);
		return;
	}
	std::vector<double> thetas;
	double x_e = x;
	double y_e = y;
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
		double dir = atan2(y_e - it_flag->getY(), x_e - it_flag->getX());
		double x_i = it_flag->getX() + cos(dir) * it_flag->getDistance();
		double y_i = it_flag->getY() + sin(dir) * it_flag->getDistance();
		x_e = tao * x_e + (1 - tao) * x_i;
		y_e = tao * y_e + (1 - tao) * y_i;
		double gamma = 180 * atan2(it_flag->getY() - y_e, it_flag->getX() - x_e) / Math::PI - it_flag->getDirection();
		thetas.push_back(Geometry::toRadians(gamma));
	}
	x = x_e;
	y = y_e;
	body = Geometry::toDegrees(Math::arcsMean(thetas)) - Self::HEAD_ANGLE; //theta = angleMean(thetas);
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
	x = pfilter.getMean(0);
	y = pfilter.getMean(1);
	body = 180.0 * atan2(pfilter.getMean(3), pfilter.getMean(2)) / Math::PI - Self::HEAD_ANGLE;
}

void Self::localize(std::vector<Flag> flags) {
	if (!positioned) return;
	velc = getAmountOfSpeedAtTime(1) + getEffortAtTime(1) * DASH_POWER_RATE * u[0];
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
	position = Position(x, y, body, Self::HEAD_ANGLE);
}

const Position* Self::getPosition() {
	return &position;
}

const Geometry::Vector2D* Self::getVelocity() {
	return &velocity; //Vector2D::getVector2DWithMagnitudeAndDirection(Self::AMOUNT_OF_SPEED, Self::DIRECTION_OF_SPEED);
}

void Self::setLastCommandsSet(std::list<Command*> last_commands_sent_t) {
	last_commands_sent.swap(last_commands_sent_t);
}

std::string Self::getViewModeWidthAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? view_mode_width_buffer[time] : "";
}

std::string Self::getViewModeQualityAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? view_mode_quality_buffer[time] : "";
}

double Self::getStaminaAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? stamina_buffer[time] : 0.0;
}

double Self::getEffortAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? effort_buffer[time] : 0.0;
}

double Self::getStaminaCapacityAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? stamina_capacity_buffer[time] : 0.0;
}

double Self::getAmountOfSpeedAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? amount_of_speed_buffer[time] : 0.0;
}

double Self::getDirectionOfSpeedAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? direction_of_speed_buffer[time] : 0.0;
}

int Self::getKickCountAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? kick_count_buffer[time] : 0;
}

int Self::getDashCountAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? dash_count_buffer[time] : 0;
}

int Self::getTurnCountAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? turn_count_buffer[time] : 0;
}

int Self::getSayCountAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? say_count_buffer[time] : 0;
}

int Self::getTurnNeckCountAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? turn_neck_count_buffer[time] : 0;
}

int Self::getCatchCountAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? catch_count_buffer[time] : 0;
}

int Self::getMoveCountAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? move_count_buffer[time] : 0;
}

int Self::getChangeViewCountAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? change_view_count_buffer[time] : 0;
}

int Self::getArmMovableAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? arm_movable_buffer[time] : 0;
}

int Self::getArmExpiresAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? arm_expires_buffer[time] : 0;
}

double Self::getArmDistAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? arm_dist_buffer[time] : 0.0;
}

double Self::getArmDirAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? arm_dir_buffer[time] : 0.0;
}

int Self::getArmCountAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? arm_count_buffer[time] : 0;
}

std::string Self::getFocusTargetAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? focus_target_buffer[time] : "";
}

int Self::getFocusCountAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? focus_count_buffer[time] : 0;
}

int Self::getTackleExpiresAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? tackle_expires_buffer[time] : 0;
}

int Self::getTackleCountAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? tackle_count_buffer[time] : 0;
}

std::list<std::string> Self::getCollisionsAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? collisions_buffer[time] : empty_vector;
}

int Self::getFoulChargedAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? foul_charged_buffer[time] : 0;
}

std::string Self::getFoulCardAtTime(unsigned int time) {
	return (time < Configs::BUFFER_MAX_HISTORY) ? foul_card_buffer[time] : "";
}

}
