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
#include "Ray2.h"

using namespace MINX;

Ray2::Ray2(double direction, double xPosition, double yPosition)
{
	dir=direction;
	xPos=xPosition;
	yPos=yPosition;
}

Ray2::Ray2(double direction)
{
	dir=direction;
	xPos=0;
	yPos=0;
}

Ray2 Ray2::operator-()const
{
	return Ray2(-dir,xPos,yPos);
}

bool Ray2::operator==(const Ray2& compareTo)
{
	return dir==compareTo.dir && xPos==compareTo.xPos && yPos==compareTo.yPos;
}

bool Ray2::operator!=(const Ray2& compareTo)
{
	return !operator==(compareTo);
}
