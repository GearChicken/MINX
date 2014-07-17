/*
# MINX

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

#include "API.h"

#include <cmath>
#include <stdlib.h>

#ifndef MINX_MATH_H_
#define MINX_MATH_H_

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
		extern MINX_API double random(double minimum, double maximum, double precision = 100.0);
	}
}
#endif
