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
 * @file functions.hpp
 *
 * @author Nelson I. Gonzalez
 */

#ifndef FUNCTIONS_HPP_
#define FUNCTIONS_HPP_

#include <vector>
#include <cmath>
#include "constants.hpp"

namespace Math {

/*!
 * Base struct
 */
struct Function {
	Function() {};
	virtual ~Function() {};
	virtual double evaluate(double x) = 0;
};

/*!
 * f(x) = (1 / (stdv * sqrt(2 * PI))) * exp(-0.5 * pow(((x - mu) / stdv), 2.0))
 */
struct Gaussian : public Function {
	double mu;
	double stdv;
	Gaussian() : Function(), mu(0.0), stdv(1.0) {};
	Gaussian(double mu, double stdv) : Function(), mu(mu), stdv(stdv) {};
	~Gaussian() {};
	double evaluate(double x) {
		if (stdv > 0.0) {
			return (1.0 / (stdv * sqrt(2.0 * PI))) * exp(-0.5 * pow(((x - mu) / stdv), 2.0));
		}
		else {
			return 1.0;
		}
	};
};

/*!
 * f(x) = exp(-0.5 * pow(((x - mu) / stdv), 2.0))
 */
struct UGaussian : public Function {
	double mu;
	double stdv;
	UGaussian() : Function(), mu(0.0), stdv(1.0) {};
	UGaussian(double mu, double stdv) : Function(), mu(mu), stdv(stdv) {};
	~UGaussian() {};
	double evaluate(double x) {
		if (stdv > 0.0) {
			return exp(-0.5 * pow(((x - mu) / stdv), 2.0));
		}
		else {
			return 1.0;
		}
	};
};

/*!
 * f(x) =
 * 1       /\
 *        /  \
 *       /    \
 * 0____/      \________
 *     a   b   c
 */
struct Triangular : public Function {
	double a;
	double b;
	double c;
	Triangular() : Function(), a(-1.0), b(0.0), c(1.0) {};
	Triangular(double a, double b, double c) : Function(), a(a), b(b), c(c) {};
	~Triangular() {};
	double evaluate(double x) {
		if (x > a && x < b) {
			return (x - a) / (b - a);
		}
		else if (x > b && x < c) {
			return (c - x) / (c - b);
		}
		else if (x == b) {
			return 1.0;
		}
		else {
			return 0.0;
		}
	};
};

/*!
 * f(x) =
 * 1       _______
 *        /       \
 *       /         \
 * 0____/           \________
 *     a   b     c   d
 */
struct Trapezoidal : public Function {
	double a;
	double b;
	double c;
	double d;
	Trapezoidal() : Function(), a(-2.0), b(-1.0), c(1.0), d(2.0) {};
	Trapezoidal(double a, double b, double c, double d) : Function(), a(a), b(b), c(c), d(d) {};
	~Trapezoidal() {};
	double evaluate(double x) {
		if (x > a && x < b) {
			return (x - a) / (b - a);
		}
		else if (x >= b && x <= c) {
			return 1.0;
		}
		else if (x > c && x < d) {
			return (d - x) / (d - c);
		}
		else {
			return 0.0;
		}
	};
};

/*!
 * f(x) =
 * 1/(a-b)   _________
 *           |       |
 *           |       |
 * 0_________|       |_________
 *           a       b
 */
struct Uniform : public Function {
	double a;
	double b;
	Uniform() : Function(), a(-1.0), b(1.0) {};
	Uniform(double a, double b) : Function(), a(a), b(b) {};
	~Uniform() {};
	double evaluate(double x) {
		if (x > a && x < b) {
			return 1.0 / (b - a);
		}
		else {
			return 0.0;
		}
	};
};

/*!
 * f(x) =
 * 1        ---------
 *         /
 *        /
 * 0_____/
 *       a   b
 */
struct RampAsc : public Function {
	double a;
	double b;
	RampAsc() : Function(), a(-1.0), b(1.0) {};
	RampAsc(double a, double b) : Function(), a(a), b(b) {};
	~RampAsc() {};
	double evaluate(double x) {
		if (x < a) {
			return 0.0;
		}
		else if (x > b) {
			return 1.0;
		}
		else {
			return (x - a) / (b - a);
		}
	};
};

/*!
 * f(x) =
 * 1_____
 *       \
 *        \
 * 0       \________
 *      a  b
 */
struct RampDesc : public Function {
	double a;
	double b;
	RampDesc() : Function(), a(-1.0), b(1.0) {};
	RampDesc(double a, double b) : Function(), a(a), b(b) {};
	~RampDesc() {};
	double evaluate(double x) {
		if (x < a) {
			return 1.0;
		}
		else if (x > b) {
			return 0.0;
		}
		else {
			return (b - x) / (b - a);
		}
	};
};

/*!
 * f(x) = mx + b
 */
struct Linear : public Function {
	double m;
	double b;
	Linear() : Function(), m(1.0), b(0.0) {};
	Linear(double m, double b) : Function(), m(m), b(b) {};
	~Linear() {};
	double evaluate(double x) {
		return m * x + b;
	};
};

/*!
 * f(x) = a / (x - b) + c
 */
struct Inverse : public Function {
	double a;
	double b;
	double c;
	Inverse() : Function(), a(1.0), b(0.0), c(0.0) {};
	Inverse(double a, double b, double c) : Function(), a(a), b(b), c(c) {};
	~Inverse() {};
	double evaluate(double x) {
		return a / (x - b) + c;
	}
};

/*!
 * f(x) = a * e^(x - b) + c
 */
struct Exponential : public Function {
	double a;
	double b;
	double c;
	Exponential() : Function(), a(1.0), b(0.0), c(0.0) {};
	Exponential(double a, double b, double c) : Function(), a(a), b(b), c(c) {};
	~Exponential() {};
	double evaluate(double x) {
		return a * exp(x - b) + c;
	}
};

/*!
 *
 */
inline double arcsMean(std::list<double> arcs) {
	double xs = 0.0;
	double ys = 0.0;
	for (std::list<double>::iterator it = arcs.begin(); it != arcs.end(); ++it) {
		xs += cos(*it);
		ys += sin(*it);
	}
	if (arcs.size() > 0) {
		xs /= arcs.size();
		ys /= arcs.size();
	}
	return atan2(ys, xs);
}

/*!
 *
 */
template <class T>
T min(std::list<T> values) {
	T min = values.at(0);
	for (typename std::list<T>::iterator it = values.begin(); it != values.end(); ++it) {
		if (*it < min) {
			min = *it;
		}
	}
	return min;
}

/*!
 *
 */
template <class T>
T max(std::list<T> values) {
	T max = values.at(0);
	for (typename std::list<T>::iterator it = values.begin(); it != values.end(); ++it) {
		if (*it > max) {
			max = *it;
		}
	}
	return max;
}

}

#endif /* FUNCTIONS_HPP_ */
