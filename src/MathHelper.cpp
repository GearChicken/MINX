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

#include "MathHelper.h"

using namespace MINX;

//Constants

double Math::PI = ::asin(-1.0);

double Math::TAO = 2 * asin(-1.0);

//Trig Functions

double Math::sin(double radians)
{
	return ::sin(radians);
}

double Math::cos(double radians)
{
	return ::cos(radians);
}

double Math::tan(double radians)
{
	return ::tan(radians);
}

double Math::cot(double radians)
{
	return ::tan(1.0 / radians);
}

double Math::sec(double radians)
{
	return ::cos(1.0 / radians);
}

double Math::csc(double radians)
{
	return ::sin(1.0 / radians);
}

double Math::sinh(double radians)
{
	return ::sinh(radians);
}

double Math::cosh(double radians)
{
	return ::cosh(radians);
}

double Math::tanh(double radians)
{
	return ::tanh(radians);
}

double Math::coth(double radians)
{
	return ::tanh(1.0 / radians);
}

double Math::sech(double radians)
{
	return ::cosh(1.0 / radians);
}

double Math::csch(double radians)
{
	return ::sinh(1.0 / radians);
}

double Math::asin(double num)
{
	return ::asin(num);
}

double Math::acos(double num)
{
	return ::acos(num);
}

double Math::atan(double num)
{
	return ::atan(num);
}

double Math::atan2(double y, double x)
{
	return ::atan2(y, x);
}

double Math::acot(double num)
{
	return ::atan(1.0 / num);
}

double Math::acot2(double y, double x)
{
	return ::atan2(1.0 / y, 1.0 / x);
}

double Math::asec(double num)
{
	return ::acos(1.0 / num);
}

double Math::acsc(double num)
{
	return ::asin(1.0 / num);
}

double Math::degreesToRadians(double degrees)
{
	return degrees * Math::PI / 180.0;
}

double Math::radiansToDegrees(double radians)
{
	return radians * 180.0 / Math::PI;
}

//Logarithmic Functions

double Math::ln(double num)
{
	return ::log(num);
}

double Math::log2(double num)
{
	return ::log(num) / ::log(2);
}

double Math::log10(double num)
{
	return ::log10(num);
}

double Math::log(double base, double num)
{
	return ::log(num) / ::log(base);
}

double Math::exp(double num)
{
	return ::exp(num);
}

double Math::pow(double num, double power)
{
	return ::pow(num, power);
}

//General Functions

int Math::sign(double num)
{
	return int(num == 0 ? 0 : abs(num)/num);
}

double Math::abs(double num)
{
	return num >= 0 ? num : -num;
}

bool Math::parity(long num)
{
	return (num % 2) == 0;
}

double Math::round(double x)
{
	double wholeNumber = int(x);
	float dif = x - wholeNumber;
	if(dif >= 0.5f)
	{
		return wholeNumber + 1;
	}
	return wholeNumber;
}

double Math::sqrt(double num)
{
	return ::sqrt(num);
}

double Math::cbrt(double num)
{
	return pow(num, 1.0/3.0);
}

double Math::root(double degree, double num)
{
	return pow(num, 1.0/degree);
}

double Math::fmod(double numerator, double denominator)
{
	return denominator == 0 ? 0 : ::fmod(numerator,denominator);
}
