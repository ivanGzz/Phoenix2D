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

#ifndef FUNCTIONS_HPP_
#define FUNCTIONS_HPP_

#include <vector>

namespace Math {

/*
 * f(x) = (1 / (stdv * sqrt(2 * PI))) * exp(-0.5 * pow(((x - mu) / stdv), 2.0))
 */
struct Gaussian {
	double mu;
	double stdv;
	Gaussian() : mu(0.0), stdv(1.0) {};
	Gaussian(double mu, double stdv) : mu(mu), stdv(stdv) {};
	double evaluate(double x) {
		if (stdv > 0.0) {
			return (1.0 / (stdv * sqrt(2.0 * PI))) * exp(-0.5 * pow(((x - mu) / stdv), 2.0));
		}
		else {
			return 1.0;
		}
	};
};

/*
 * f(x) =
 * 1       /\
 *        /  \
 *       /    \
 * 0____/      \________
 *     a   b   c
 */
struct Triangular {
	double a;
	double b;
	double c;
	Triangular() : a(-1.0), b(0.0), c(1.0) {};
	Triangular(double a, double b, double c) : a(a), b(b), c(c) {};
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

/*
 * f(x) =
 * 1       _______
 *        /       \
 *       /         \
 * 0____/           \________
 *     a   b     c   d
 */
struct Trapezoidal {
	double a;
	double b;
	double c;
	double d;
	Trapezoidal() : a(-2.0), b(-1.0), c(1.0), d(2.0) {};
	Trapezoidal(double a, double b, double c, double d) : a(a), b(b), c(c), d(d) {};
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

/*
 * f(x) =
 * 1/(a-b)   _________
 *           |       |
 *           |       |
 * 0_________|       |_________
 *           a       b
 */
struct Uniform {
	double a;
	double b;
	Uniform() : a(-1.0), b(1.0) {};
	Uniform(double a, double b) : a(a), b(b) {};
	double evaluate(double x) {
		if (x > a && x < b) {
			return 1.0 / (b - a);
		}
		else {
			return 0.0;
		}
	};
};

/*
 * f(x) =
 * 1        ---------
 *         /
 *        /
 * 0_____/
 *       a   b
 */
struct RampAsc {
	double a;
	double b;
	RampAsc() : a(-1.0), b(1.0) {};
	RampAsc(double a, double b) : a(a), b(b) {};
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

/*
 * f(x) =
 * 1_____
 *       \
 *        \
 * 0       \________
 *      a  b
 */
struct RampDesc {
	double a;
	double b;
	RampDesc() : a(-1.0), b(1.0) {};
	RampDesc(double a, double b) : a(a), b(b) {};
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

/*
 * f(x) = mx + b
 */
struct Linear {
	double m;
	double b;
	Linear() : m(1.0), b(0.0) {};
	Linear(double m, double b) : m(m), b(b) {};
	double evaluate(double x) {
		return m * x + b;
	};
};

/*
 * f(x) = a / (x - b)
 */
struct Inverse {
	double a;
	double b;
	Inverse() : a(1.0), b(0.0) {};
	Inverse(double a, double b) : a(a), b(b) {};
	double evaluate(double x) {
		return a / (x - b);
	}
};

double arcsMean(std::vector<double> arcs) {
	double xs = 0.0;
	double ys = 0.0;
	for (std::vector<double>::iterator it = arcs.begin(); it != arcs.end(); ++it) {
		xs += cos(*it);
		ys += sin(*it);
	}
	if (arcs.size() > 0) {
		xs /= arcs.size();
		ys /= arcs.size();
	}
	return atan2(ys, xs);
}

template <class T>
T min(std::vector<T> values) {
	T min = values.at(0);
	for (typename std::vector<T>::iterator it = values.begin(); it != values.end(); ++it) {
		if (*it < min) {
			min = *it;
		}
	}
	return min;
}

template <class T>
T max(std::vector<T> values) {
	T max = values.at(0);
	for (typename std::vector<T>::iterator it = values.begin(); it != values.end(); ++it) {
		if (*it > max) {
			max = *it;
		}
	}
	return max;
}

}

#endif /* FUNCTIONS_HPP_ */
