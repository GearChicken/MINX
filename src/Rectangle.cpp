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
#include "Rectangle.h"
#include <math.h>

using namespace MINX;

MINX_Rectangle::MINX_Rectangle(int x, int y, int width, int height)
{
	X=x;
	Y=y;
	Width = width;
	Height = height;
}
int MINX_Rectangle::area()
{
	return Width * Height;
}
int MINX_Rectangle::Top()
{
	return Y;
}
int MINX_Rectangle::Bottom()
{
	return Y + Height;
}
int MINX_Rectangle::Left()
{
	return X;
}
int MINX_Rectangle::Right()
{
	return X + Width;
}
bool MINX_Rectangle::intersects(MINX_Rectangle* rect2)
{
	return !(
			(Bottom() < rect2->Top()) ||
			(Top() > rect2->Bottom()) ||
			(Left() > rect2->Right()) ||
			(Right() < rect2->Left()) );
}
