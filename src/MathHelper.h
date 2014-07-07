
/*
# The zlib/libpng License

Copyright (c) 2013-2014 Liam Middlebrook, Benjamin Pylko

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

> 1\. The origin of this software must not be misrepresented; you must not
> claim that you wrote the original software. If you use this software
> in a product, an acknowledgment in the product documentation would be
> appreciated but is not required.
>
> 2\. Altered source versions must be plainly marked as such, and must not be
> misrepresented as being the original software.
>
> 3\. This notice may not be removed or altered from any source
> distribution.
>
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
		extern double clamp(double number, double lowerLimit, double upperLimit);
		extern double max(double num1, double num2);
		extern double min(double num1, double num2);
	}
}
#endif
