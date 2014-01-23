/*
    MINX - A C++ Graphics and Input Wrapper Library
    Copyright (C) 2013-2014  MINX Team

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
#include "Vector2.h"
#include <math.h>
#include <iostream>

using namespace MINX;

Vector2::Vector2():  X( 0 ), Y( 0 ) {}

Vector2::Vector2(double x, double y) : X( x ), Y( y ) {}
Vector2::Vector2(double length, double angle, bool radians) : X( length*cos(angle*(radians ? 1 : 3.14159265/180)) ), Y( length*sin(radians*(radians ? 1 : 3.14159265/180)) ) {}

Vector2 Vector2::operator+(const Vector2& addTo)
{
	return Vector2(X+addTo.X,Y+addTo.Y);
}
Vector2 Vector2::operator+=(const Vector2& addTo)
{
	X += addTo.X;
	Y += addTo.Y;
	return *this;
}
Vector2 Vector2::operator-(const Vector2& subtractFrom)
{
	return Vector2(X-subtractFrom.X,Y-subtractFrom.Y);
}
Vector2 Vector2::operator-=(const Vector2& subtractFrom)
{
	X -= subtractFrom.X;
	Y -= subtractFrom.Y;
	return *this;
}
double Vector2::crossMultiply(const Vector2& multiplyBy)
{
	return X*multiplyBy.Y - Y*multiplyBy.X;
}
double Vector2::dotMultiply(const Vector2& multiplyBy)
{
	return X*multiplyBy.X + Y*multiplyBy.Y;
}
Vector2 Vector2::operator*(const Vector2& multiplyBy)
{
	return Vector2(X*multiplyBy.X,Y*multiplyBy.Y);
}
Vector2 Vector2::operator*(const double& multiplyBy)
{
	return Vector2(X*multiplyBy,Y*multiplyBy);
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
	return Vector2(X/divideBy.X,Y/divideBy.Y);
}
Vector2 Vector2::operator/(const double& divideBy)
{
	return Vector2(X/divideBy,Y/divideBy);
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
		return Vector2(X/Length(),Y/Length());
	}
	return Vector2(0,0);
}
double Vector2::Direction()
{
	return atan2(Y, X);
}
