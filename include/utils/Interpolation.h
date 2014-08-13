#ifndef __INTERPOLATION_H__
#define __INTERPOLATION_H__

#include <cmath>

namespace Bipedal
{

/*
 * Linear interpolation of S in period time T
 */
inline double linearInterpolation(double t, double T, double S)
{
	return (t/T) * S;
}

inline double spline(double t, double x1, double x2, double y1, double y2, double k1, double k2)
{
	const double dx = (x2-x1);
	const double dy = (y2-y1);
	const double a =  k1 * dx - dy;
	const double b = -k2 * dx + dy;
	return ((1-t) * y1 + t * y2 + t*(1-t)*(a*(1-t) + b*t));
}

inline double splineDerivation(double t, double x1, double x2, double y1, double y2, double k1, double k2)
{
	const double dx = (x2-x1);
	const double dy = (y2-y1);
	const double a =  k1 * dx - dy;
	const double b = -k2 * dx + dy;
	return dy/dx + (1-2*t) * (a*(1-t) + b*t)/dx + t*(1-t)*(b - a)/dx;
}

/*
 * Cubic spline interpolation of S in period time T.
 * This should give constant jerk and linear accelerations.
 */
inline double splinePositionInterpolation(double t, double T, double S, double v0, double v1)
{
	double y = spline(t/T, 0, T, 0, S, v0, v1);
	return y;
}

inline double splineVelocityInterpolation(double t, double T, double S, double v0, double v1)
{
	double y = splineDerivation(t/T, 0, T, 0, S, v0, v1);
	return y;
}

/**
 * Derived from a polynom with degree 5 using position/velocity/acceleration constrains for the end-points
 */
inline double polyPositionInterpolation(double t, double T, double S, double v0, double v1, double a0, double a1)
{
	const double x = t;
	return (x*(pow(T, 5)*(a0*x + 2*v0) + pow(T, 2)*pow(x, 2)*(20*S + pow(T, 2)*(-3*a0 + a1) - 4*T*(3*v0 + 2*v1)) + T*pow(x, 3)*(-30*S + pow(T, 2)*(3*a0 - 2*a1) + 2*T*(8*v0 + 7*v1)) + pow(x, 4)*(12*S + pow(T, 2)*(-a0 + a1) - 6*T*(v0 + v1)))/(2*pow(T, 5)));
}

/**
 * Derived from a polynom with degree 5 using position/velocity/acceleration constrains for the end-points
 */
inline double polyVelocityInterpolation(double t, double T, double S, double v0, double v1, double a0, double a1)
{
	const double x = t;
	return (a0*x + v0 + pow(x, 4)*(30*S/pow(x, 5) - 5*a0/(2*pow(x, 3)) + 5*a1/(2*pow(x, 3)) - 15*v0/pow(x, 4) - 15*v1/pow(x, 4)) + pow(x, 3)*(-60*S/pow(x, 4) + 6*a0/pow(x, 2) - 4*a1/pow(x, 2) + 32*v0/pow(x, 3) + 28*v1/pow(x, 3)) + pow(x, 2)*(30*S/pow(x, 3) - 9*a0/(2*T) + 3*a1/(2*T) - 18*v0/pow(x, 2) - 12*v1/pow(x, 2)));
}

}

#endif