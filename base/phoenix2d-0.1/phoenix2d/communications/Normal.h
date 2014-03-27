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

#ifndef NORMAL_H_
#define NORMAL_H_

#include <list>

/*! @addtogroup phoenix_main
 * @{
 */
namespace Phoenix
{
/*!
 * @brief <STRONG> Normal <BR> </STRONG>
 * The Normal lorem Ipsum
 */
class Normal {
	double mean;
	double deviation;
public:
	Normal(double mean, double deviation);
	Normal(std::list<double> data, bool circular = false);
	Normal(std::list<double> data, std::list<int> multipliers, bool circular = false);
	~Normal();
	double getLower5();
	double getUpper5();
	double getMean();
	double getStdDeviation();
};
} // End namespace Phoenix
/*! @} */

#endif /* NORMAL_H_ */
