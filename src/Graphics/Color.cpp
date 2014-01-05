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
#include "Color.h"
using namespace MINX::Graphics;

Color::Color()
{
	R = 255;
	B = 255;
	G = 255;
	A = 255;
}

Color::Color(byte r, byte g, byte b, byte a)
{
	R=r;
	G=g;
	B=b;
	A=a;
}

Color::Color(byte r, byte g, byte b)
{
	//Color(r,g,b,255);
	R=r;
	G=g;
	B=b;
	A=255;
}
bool Color::operator==(const Color& compareTo)
{
	return R == compareTo.R && G == compareTo.G && B == compareTo.B && A == compareTo.A;
}
bool Color::operator!=(const Color& compareTo)
{
	return !operator==(compareTo);
}
Color * Color::operator*(const float& scale)
{
	return new Color(R*scale,G*scale,B*scale,A*scale);
}
