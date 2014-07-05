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

#include "API.h"

#include <cmath>

namespace MINX
{
	namespace Math
	{
		extern MINX_API double PI;
		extern MINX_API double TAO;
		extern MINX_API double E;
		/// Trig Functions
		extern MINX_API double sin(double radians);
		extern MINX_API double cos(double radians);
		extern MINX_API double tan(double radians);
		extern MINX_API double cot(double radians);
		extern MINX_API double sec(double radians);
		extern MINX_API double csc(double radians);
		extern MINX_API double sinh(double radians);
		extern MINX_API double cosh(double radians);
		extern MINX_API double tanh(double radians);
		extern MINX_API double coth(double radians);
		extern MINX_API double sech(double radians);
		extern MINX_API double csch(double radians);
		extern MINX_API double asin(double num);
		extern MINX_API double acos(double num);
		extern MINX_API double atan(double num);
		extern MINX_API double atan2(double y, double x);
		extern MINX_API double acot(double num);
		extern MINX_API double acot2(double y, double x);
		extern MINX_API double asec(double num);
		extern MINX_API double acsc(double num);

		extern MINX_API double degreesToRadians(double degrees);
		extern MINX_API double radiansToDegrees(double radians);

		//Logarithmic Functions
		extern MINX_API double ln(double num);
		extern MINX_API double log2(double num);
		extern MINX_API double log10(double num);
		extern MINX_API double log(double base, double num);
		extern MINX_API double exp(double num);
		extern MINX_API double pow(double num, double power);

		//General Functions
		extern MINX_API int sign(double num);
		extern MINX_API double abs(double num);
		extern MINX_API bool parity(long num);
		extern MINX_API double round(double x);
		extern MINX_API double sqrt(double num);
		extern MINX_API double cbrt(double num);
		extern MINX_API double root(double degree, double num);
		extern MINX_API double fmod(double numerator, double denominator);
		extern MINX_API double clamp(double number, double lowerLimit, double upperLimit);
		extern MINX_API double max(double num1, double num2);
		extern MINX_API double min(double num1, double num2);
		extern MINX_API double random(double minimum, double maximum, double precision);
	}
}
#endif
