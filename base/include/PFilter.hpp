// $Id$
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
 *
 * @file ParticleFilter.hpp
 *
 * @author Nelson Iv‡n Gonz‡lez
 *
 */
// $Log$

#ifndef PFILTER_HPP_
#define PFILTER_HPP_

#include "Constants.hpp"
#include <vector>
#include "Flag.hpp"
#include "Position.hpp"

/*!
 * @defgroup phoenix_main Phoenix Library Namespace
 * @brief <STRONG> Phoenix2D Master <BR> </STRONG>
 * The namespace that contains everything related to the Phoenix Library
 * @{
 */
namespace Phoenix {

struct Particle {
	double x;
	double y;
	double direction;
	double weight;
};

/*!
 * @brief <STRONG> ParticleFilter <BR> </STRONG>
 *
 */
class PFilter {
public:
	PFilter();
	~PFilter();
	void initWithBelief(double x, double y, double dir, double x_window, double y_window, double dir_window);
	void update(void(* weight)(Particle &particle));
	void predict(void(* predict)(Particle &particle));
	void resample();
	double mean;
	double variance;
	double x_mean;
	double y_mean;
	double dir_mean;
private:
	Particle set[Filter::PARTICLES];
	void computeParams();
};
/*! @} */
} // End namespace Phoenix
/*! @} */

#endif /* PARTICLEFILTER_HPP_ */
