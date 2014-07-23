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
 * @file World.cpp
 *
 * @author Nelson Ivan Gonzalez
 */

#include <cmath>
#include <iostream>
#include <set>
#include <string>
#include <map>
#include "World.hpp"
#include "Game.hpp"
#include "Configs.hpp"
#include "Self.hpp"
#include "Controller.hpp"
#include "Server.hpp"
#include "functions.hpp"
#include "PFilter.hpp"

namespace Phoenix {

static std::vector<Player> players;
static Ball ball;
static std::vector<Player> fs_players;
static Ball fs_ball;
static int next_player_id = 0;
static std::map<int, Filters::PFilter<4> > filters;

struct _cell {
	int t; // 0: both uniform numbers and teams are equal, 1: teams are equal, 2: other case
	Filters::PFilter<4> filter;
	double i;
	double d;
	double v;
	double h;
	int row;
	int column;
	bool dominated;
	_cell() : t(2), i(0.0), d(0.0), v(0.0), h(0.0), row(-1), column(-1), dominated(false) {};
	void computeH() {
		if (i < 1.0) {
			h = i * d * v;
		} else {
			h = 1.0;
		}
	};
};

World::World() {

}

World::~World() {
	if (Configs::VERBOSE) std::cout << "World out" << std::endl;
}

/*
 * This methods test the hypothesis that the past player is near the current player.
 * This method assumes the past player is no longer in the visual range.
 * If it is near than the distance error for the current player then it is not copied
 * in the new World Model.  The sum of the distance errors of both players is
 * used as the standard deviation assuming the errors behave as a normal distribution
 */
bool testHypothesisFor(Player* past, Player* current) {
	Position* pp = past->getPosition();
	Position* cp = current->getPosition();
	double stdv = current->getDistanceError() + past->getDistanceError();
	double x = cp->getDistanceTo(pp) / stdv;
	// Using a 90% confidence interval
	if (x < 1.64) {
		return true;
	} else {
		return false;
	}
}

bool compare(_cell* c0, _cell* c1) {
	return c0->h > c1->h;
}

/*
 * Based on:
 * 	Comparison of a New Qualifier Method for Multiple Object Tracking in RoboCup 2D Simulation League
 * 	Nelson Ivan Gonzalez & Leonardo Garrido
 * 	IBERAMIA 2014
 * Description:
 *	We need this method to be part of the class since the World class is friend of Player class
 */
void World::matchPlayers(std::vector<Player> &past_players, std::vector<Player> &new_players) {
	std::vector<std::vector<_cell> > hv(past_players.size(), std::vector<_cell>(new_players.size()));
	bool (*fn_pt)(_cell*, _cell*) = compare;
	std::multiset<_cell*, bool(*)(_cell*, _cell*)> hso(fn_pt);
	int column = 0;
	int row = 0;
	for (std::vector<Player>::iterator p = past_players.begin(); p != past_players.end(); ++p) {
		column = 0;
		double dt = 0.0; // total euclidean distance
		int nt = 0; // total of players with same teams
		int mt = 0; // total of players with undefined teams
		Math::Gaussian g(0.0, 90.0);
		bool exact = false; // true if one of the new players is the same player (same team and same uniform number)
		for (std::vector<Player>::iterator n = new_players.begin(); n != new_players.end(); ++n) {
			hv[row][column].row = row;
			hv[row][column].column = column;
			// We assume that an observer cannot known the uniform number without knowing the team
			std::string pteam = p->getTeam();
			std::string nteam = n->getTeam();
			if (pteam.compare("undefined") == 0 || nteam.compare("undefined") == 0) {
				// at least one of the player teams is undefined
				mt++;
				hv[row][column].t = 2;
			} else if (pteam.compare(nteam) == 0) {
				// both teams are equal and not undefined
				if (p->uniform_number == 0 || n->uniform_number == 0) {
					// at least one of the player uniform number is 0
					nt++;
					hv[row][column].t = 1;
				} else if (p->uniform_number == n->uniform_number) {
					// both uniform numbers are equal
					hv[row][column].t = 0;
					hv[row][column].i = 1.0;
					exact = true;
				}
			}
			Position p_n = n->position;
			Position p_p = p->position;
			double d = sqrt(pow(p_n.getX() - p_p.getX(), 2.0) + pow(p_n.getY() - p_p.getY(), 2.0));
			if (d < 0.1) d = 0.1;
			dt += 1.0 / d;
			hv[row][column].d = 1.0 / d;
			if (p->has_body) {
				double a = 0.0;
				if (p_n.getX() != p_p.getX() || p_n.getY() != p_p.getY()) {
					a = fabs(p_p.getDirection() - Geometry::toDegrees(atan2(p_n.getY() - p_p.getY(), p_n.getX() - p_p.getX())));
				}
				hv[row][column].v = g.evaluate(a);
			} else {
				hv[row][column].v = 1.0 / new_players.size();
			}
			column++;
		}
		if (!exact) {
			// If there is no player with the same id
			double pi = 1.0 / (2.0 * nt + mt);
			for (int i = 0; i < new_players.size(); ++i) {
				hv[row][i].i = (hv[row][i].t == 1) ? (2.0 * pi) : pi;
				hv[row][i].d /= dt;
				hv[row][i].computeH();
				hso.insert(&hv[row][i]);
			}
		} else {
			// There is a player with the same id
			for (int i = 0; i < new_players.size(); ++i) {
				hv[row][i].computeH();
				hso.insert(&hv[row][i]);
			}
		}
		row++;
	}
	int min = new_players.size();
	if (past_players.size() < min) {
		min = past_players.size();
	}
	int counter = 0;
	for (std::multiset<_cell*>::iterator it = hso.begin(); it != hso.end(); ++it) {
		if (counter <= min) {
			// The cell is dominated after a player in its row or column has been matched
			if ((*it)->dominated) {
				continue;
			} else {
				// The players are matched
				Player* np = &new_players[(*it)->column];
				Player* pp = &past_players[(*it)->row];
				double dx = np->getPosition()->getX() - pp->getPosition()->getX();
				double dy = np->getPosition()->getY() - pp->getPosition()->getY();
				double d = sqrt(dx * dx + dy * dy);
				if (d > (pp->getDistanceError() + np->getDistanceError()) * Configs::TRACKING_THRESHOLD) {
					// If the distance between the two players is greater than theirs errors plus the threshold we do not accept the tracking
					std::cout << Game::GAME_TIME << ": reject match with value " << (*it)->h << std::endl;
					continue;
				}
				// We infer physical characteristics
				if (!np->vel) {
					Geometry::Vector2D new_vel(dx, dy);
					if (new_vel.getMagnitude() > Self::PLAYER_SPEED_MAX && new_vel.getMagnitude() > 0.0) {
						new_vel.scale(Self::PLAYER_SPEED_MAX / new_vel.getMagnitude());
					}
					np->velocity = new_vel;
				}
				if (!np->has_body) {
					np->body = Geometry::toDegrees(atan2(dy, dx));
				}
				// We update id information
				if (pp->team.compare("undefined") != 0) {
					np->team = pp->team;
					if (pp->uniform_number != 0) {
						np->uniform_number = pp->uniform_number;
					}
				}
				np->player_id = pp->player_id;
				pp->tracked = true;
				int i;
				for (i = 0; i < new_players.size(); ++i) {
					hv[(*it)->row][i].dominated = true;
				}
				for (i = 0; i < past_players.size(); ++i) {
					hv[i][(*it)->column].dominated = true;
				}
				np->match = (*it)->h;
				counter++;
			}
		} else {
			// We already matched all possible players
			break;
		}
	}
	// Players not matched are given a new id
	for (std::vector<Player>::iterator it = new_players.begin(); it != new_players.end(); ++it) {
		if (it->player_id == -1) {
			it->player_id = next_player_id++;
		}
	}
}

static double dash = 0.0;
//static double turn = 0.0;
static Player* _player = 0;

void updateForWorld(Filters::Particle<4> &p) {
	double dx = p.dimension[0] - _player->getPosition()->getX();
	double dy = p.dimension[1] - _player->getPosition()->getY();
	double d = sqrt(dx * dx + dy * dy);
	if (d < 0.1) d = 0.1;
	p.weight = 1.0 / d;
}

void predictForWorld(Filters::Particle<4> &p) {
	double dir = atan2(p.dimension[3], p.dimension[2]);
	p.dimension[0] = dash * cos(dir);
	p.dimension[1] = dash * sin(dir);
//	dir = Geometry::toDegrees(dir);
//	dir = Geometry::toRadians(dir + turn);
//	p.dimension[2] = cos(dir);
//	p.dimension[3] = sin(dir);
}

void World::matchPlayersPF(std::vector<Player> &new_players) {
	std::vector<std::vector<_cell> > hv(players.size(), std::vector<_cell>(new_players.size()));
	bool (*fn_pt)(_cell*, _cell*) = compare;
	std::multiset<_cell*, bool(*)(_cell*, _cell*)> hso(fn_pt);
	int column = 0;
	int row = 0;
	for (std::vector<Player>::iterator p = players.begin(); p != players.end(); ++p) {
		column = 0;
		for (std::vector<Player>::iterator n = new_players.begin(); n != new_players.end(); ++n) {
			hv[row][column].row = row;
			hv[row][column].column = column;
//			turn = 0.0;
			_player = &(*n);
			Filters::PFilter<4> pfilter = filters[p->player_id];
			dash = p->getPosition()->getDistanceTo(_player->getPosition());
			pfilter.predict(predictForWorld);
			pfilter.update(updateForWorld);
			pfilter.resample();
			hv[row][column].filter = pfilter;
			hv[row][column].h = pfilter.getFit();
			hso.insert(&hv[row][column]);
			column++;
		}
		row++;
	}
	// We perform the match, this is practically the same that for the previous method
	int min = new_players.size();
		if (players.size() < min) {
			min = players.size();
		}
		int counter = 0;
		for (std::multiset<_cell*>::iterator it = hso.begin(); it != hso.end(); ++it) {
			if (counter <= min) {
				// The cell is dominated after a player in its row or column has been matched
				if ((*it)->dominated) {
					continue;
				} else {
					// The players are matched
					Player* np = &new_players[(*it)->column];
					Player* pp = &players[(*it)->row];
					double dx = np->getPosition()->getX() - pp->getPosition()->getX();
					double dy = np->getPosition()->getY() - pp->getPosition()->getY();
					double d = sqrt(dx * dx + dy * dy);
					if (d > (pp->getDistanceError() + np->getDistanceError()) * Configs::TRACKING_THRESHOLD) {
						// If the distance between the two players is greater than theirs errors plus the threshold we do not accept the tracking
						std::cout << Game::GAME_TIME << ": reject match with value " << (*it)->h << std::endl;
						continue;
					}
					// We infer physical characteristics
					if (!np->vel) {
						Geometry::Vector2D new_vel(dx, dy);
						if (new_vel.getMagnitude() > Self::PLAYER_SPEED_MAX && new_vel.getMagnitude() > 0.0) {
							new_vel.scale(Self::PLAYER_SPEED_MAX / new_vel.getMagnitude());
						}
						np->velocity = new_vel;
					}
					if (!np->has_body) {
						np->body = Geometry::toDegrees(atan2(dy, dx));
					}
					// We update id information
					if (pp->team.compare("undefined") != 0) {
						np->team = pp->team;
						if (pp->uniform_number != 0) {
							np->uniform_number = pp->uniform_number;
						}
					}
					np->player_id = pp->player_id;
					pp->tracked = true;
					int i;
					for (i = 0; i < new_players.size(); ++i) {
						hv[(*it)->row][i].dominated = true;
					}
					for (i = 0; i < players.size(); ++i) {
						hv[i][(*it)->column].dominated = true;
					}
					np->match = (*it)->h;
					// Finally, we update the particle filter in the map
					filters[np->player_id] = (*it)->filter;
					counter++;
				}
			} else {
				// We already matched all possible players
				break;
			}
		}
	// Players not matched are given a new id and are assigned a new particle filter
	for (std::vector<Player>::iterator it = new_players.begin(); it != new_players.end(); ++it) {
		if (it->player_id == -1) {
			it->player_id = next_player_id++;
			double mus[4];
			double devs[4];
			mus[0] = it->getPosition()->getX();
			devs[0] = it->getDistanceError();
			mus[1] = it->getPosition()->getY();
			devs[1] = it->getDistanceError();
			if (it->has_body) {
				mus[2] = cos(it->getPosition()->getDirection());
				devs[2] = 0.2;
				mus[3] = sin(it->getPosition()->getDirection());
				devs[3] = 0.2;
			} else {
				mus[2] = 0.0;
				devs[2] = 1.0;
				mus[3] = 0.0;
				devs[3] = 1.0;
			}
			Filters::PFilter<4> pfilter;
			pfilter.initWithBelief(mus, devs);
			filters[it->player_id] = pfilter;
		}
	}
}

void World::updateWorld(std::vector<Player> new_players, Ball new_ball, std::vector<Player> new_fs_players, Ball new_fs_ball) {
	if (Controller::AGENT_TYPE == 'p' || Controller::AGENT_TYPE == 'g') {
		fs_players = new_fs_players;
		fs_ball = new_fs_ball;
		if (Configs::PLAYER_HISTORY) {
			double vision_angle = 180.0;
			if (Self::VIEW_MODE_WIDTH.compare("narrow") == 0) {
				vision_angle = 60.0;
			}
			else if (Self::VIEW_MODE_WIDTH.compare("normal") == 0) {
				vision_angle = 120.0;
			}
			if (Configs::PLAYER_TRACKING) {
				matchPlayers(players, new_players);
			}
			for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it) {
				// If the past player has been already tracked, it must not be included in the new world model
				if (it->tracked) continue;
				// We update first the new position for each player in the last cycle
				Geometry::Point new_position = it->getPosition()->getPoint() + it->velocity;
				it->position = Position(new_position);
				it->velocity.scale(Server::PLAYER_DECAY);
				// If the player is out of the sight range, we could add the last position of the object
				if (fabs(Self::getPosition()->getDirectionTo(it->getPosition())) > vision_angle / 2.0) {
					// But first we must check if the object is a "resonance" of another player
					bool add = true;
					for (std::vector<Player>::iterator it_c = new_players.begin(); it_c != new_players.end(); ++it_c) {
						if (testHypothesisFor(&(*it), &(*it_c))) {
							// If the hypothesis is true then it is probable that the past player is the same current player
							add = false;
							break;
						}
					}
					if (add && it->ttl < Configs::PLAYER_MAX_HISTORY) {
						if (it->isInSightRange()) {
							it->toggleSightRange();
						}
						it->ttl++;
						new_players.push_back(*it);
					} else {
						// If we do not add the past player, then we remove the filter
						filters.erase(it->player_id);
					}
				} else {
					// If the player was not tracked and it is in the visual range, we remove its filter
					filters.erase(it->player_id);
				}
			}
		}
	}
	// If the agent is trainer or coach then it is just needed to copy the players vector and ball
	players = new_players;
	ball = new_ball;
}

WorldModel World::getWorldModel() {
	return WorldModel(players, ball, fs_players, fs_ball);
}

}
