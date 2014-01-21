/*
MINX - A C++ Graphics and Input Wrapper Library
Copyright (C) 2014  MINX Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef MINX_MATH_H_
#define MINX_MATH_H_

#include <cmath>

namespace MINX
{
	namespace Math
	{
		extern double PI;
		extern double TAO;
		extern double E;
		/// Trig Functions
		extern double sin(double radians);
		extern double cos(double radians);
		extern double tan(double radians);
		extern double cot(double radians);
		extern double sec(double radians);
		extern double csc(double radians);
		extern double sinh(double radians);
		extern double cosh(double radians);
		extern double tanh(double radians);
		extern double coth(double radians);
		extern double sech(double radians);
		extern double csch(double radians);
		extern double asin(double num);
		extern double acos(double num);
		extern double atan(double num);
		extern double atan2(double y, double x);
		extern double acot(double num);
		extern double acot2(double y, double x);
		extern double asec(double num);
		extern double acsc(double num);

		extern double degreesToRadians(double degrees);
		extern double radiansToDegrees(double radians);

		//Logarithmic Functions
		extern double ln(double num);
		extern double log2(double num);
		extern double log10(double num);
		extern double log(double base, double num);
		extern double exp(double num);
		extern double pow(double num, double power);

		//General Functions
		extern int sign(double num);
		extern double abs(double num);
		extern bool parity(long num);
		extern double round(double x);
		extern double sqrt(double num);
		extern double cbrt(double num);
		extern double root(double degree, double num);
		extern double fmod(double numerator, double denominator);

	}
}
#endif
