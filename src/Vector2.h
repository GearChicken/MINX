/*
    MINX - A C++ Graphics and Input Wrapper Library
    Copyright (C) 2013  MINX Team

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
#ifndef VECTOR2_H_
#define VECTOR2_H_
namespace MINX
{
	struct Vector2
	{
		Vector2(float x, float y);
		Vector2 operator+(const Vector2& addTo);
		Vector2 operator-(const Vector2& subtractFrom);
		Vector2 crossMultiply(const Vector2& multiplyBy);
		float operator*(const Vector2& multiplyBy);
		Vector2 operator*(const float& multiplyBy);
		Vector2 operator-()const;
		bool operator==(const Vector2& compareTo);
		bool operator!=(const Vector2& compareTo);
		float length();
		float lengthSquared();
		Vector2 normalize();
		float X;
		float Y;
	};
}
#endif
