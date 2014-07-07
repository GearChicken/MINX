
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

#include "Vector2.h"
#include "MathHelper.h"
#include <iostream>

using namespace MINX;

Vector2::Vector2():  X(0), Y(0) {}

Vector2::Vector2(double x, double y) : X(x), Y(y) {}

Vector2::Vector2(double magnitude, double direction, Heading heading) : X(magnitude*Math::cos(direction+heading*Math::PI/8)), Y(magnitude*Math::sin(direction+heading*Math::PI/8)) {}

Vector2 Vector2::operator+(const Vector2& addTo)
{
	return Vector2(X+addTo.X, Y+addTo.Y);
}
Vector2 Vector2::operator+=(const Vector2& addTo)
{
	X += addTo.X;
	Y += addTo.Y;
	return *this;
}
Vector2 Vector2::operator-(const Vector2& subtractFrom)
{
	return Vector2(X-subtractFrom.X, Y-subtractFrom.Y);
}
Vector2 Vector2::operator-=(const Vector2& subtractFrom)
{
	X -= subtractFrom.X;
	Y -= subtractFrom.Y;
	return *this;
}
double Vector2::Cross(const Vector2& multiplyBy)
{
	return X*multiplyBy.Y - Y*multiplyBy.X;
}
double Vector2::Dot(const Vector2& multiplyBy)
{
	return X*multiplyBy.X + Y*multiplyBy.Y;
}
Vector2 Vector2::operator*(const Vector2& multiplyBy)
{
	return Vector2(X*multiplyBy.X, Y*multiplyBy.Y);
}
Vector2 Vector2::operator*(const double& multiplyBy)
{
	return Vector2(X*multiplyBy, Y*multiplyBy);
}
Vector2 Vector2::operator*=(const double& multiplyBy)
{
	X *= multiplyBy;
	Y *= multiplyBy;
	return *this;
}
Vector2 Vector2::operator*=(const Vector2& multiplyBy)
{
	X *= multiplyBy.X;
	Y *= multiplyBy.Y;
	return *this;
}
Vector2 Vector2::operator/(const Vector2& divideBy)
{
	return Vector2(X/divideBy.X, Y/divideBy.Y);
}
Vector2 Vector2::operator/(const double& divideBy)
{
	return Vector2(X/divideBy, Y/divideBy);
}
Vector2 Vector2::operator/=(const double& divideBy)
{
	X /= divideBy;
	Y /= divideBy;
	return *this;
}
Vector2 Vector2::operator/=(const Vector2& divideBy)
{
	X /= divideBy.X;
	Y /= divideBy.Y;
	return *this;
}
Vector2 Vector2::operator-()const
{
	return Vector2(-X,-Y);
}
bool Vector2::operator==(const Vector2& compareTo)
{
	return compareTo.X == X && compareTo.Y == Y;
}
bool Vector2::operator!=(const Vector2& compareTo)
{
	return !operator==(compareTo);
}
double Vector2::LengthSquared()
{
	return X*X+Y*Y;
}
double Vector2::Length()
{
	return sqrt(LengthSquared());
}
Vector2 Vector2::Normalize()
{
	if(LengthSquared() != 0)
	{
		return Vector2(X/Length(), Y/Length());
	}
	return Vector2(0, 0);
}
double Vector2::Direction()
{
	return Math::atan2(Y, X);
}
