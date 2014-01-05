/*
    MINX - A C++ Graphics and Input Wrapper Library
    Copyright (C) 2013-2014  MINX Team

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

	*/
#include "Vector2.h"
#include <math.h>
#include <iostream>

using namespace MINX;

Vector2::Vector2(float x, float y) : X( x ), Y( y ) { }

Vector2 Vector2::operator+(const Vector2& addTo)
{
	return Vector2(X+addTo.X,Y+addTo.Y);
}
Vector2 Vector2::operator-(const Vector2& subtractFrom)
{
	return Vector2(X-subtractFrom.X,Y-subtractFrom.Y);
}
Vector2 Vector2::crossMultiply(const Vector2& multiplyBy)
{//really just guessing here, I'm not sure what the XNA implementation does actually, cause really this should be a 3d vector
	float angle = atan2(Y,X)-atan2(multiplyBy.Y,multiplyBy.X);
	float magnitude = sqrt(X*X+Y*Y)*sqrt(multiplyBy.X*multiplyBy.X+multiplyBy.Y*multiplyBy.Y);
	float resultantMagnitude = magnitude*sin(angle);
	return Vector2(sqrt(resultantMagnitude/2),sqrt(resultantMagnitude/2));
}
float Vector2::operator*(const Vector2& multiplyBy)
{
	float angle = atan2(Y,X)-atan2(multiplyBy.Y,multiplyBy.X);
	return sqrt(X*X+Y*Y)*sqrt(multiplyBy.X*multiplyBy.X+multiplyBy.Y*multiplyBy.Y)*cos(angle);
}
Vector2 Vector2::operator*(const float& multiplyBy)
{
	return Vector2(X*multiplyBy,Y*multiplyBy);
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
float Vector2::lengthSquared()
{
	return X*X+Y*Y;
}
float Vector2::length()
{
	return sqrt(lengthSquared());
}
Vector2 Vector2::normalize()
{
	if(lengthSquared() != 0)
	{
		return Vector2(X/length(),Y/length());
	}
	return Vector2(0,0);
}
