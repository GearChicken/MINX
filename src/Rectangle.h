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
#ifndef Rectangle_H_
#define Rectangle_H_
#include <cmath>
namespace MINX
{
	/** A Rectangle struct
	*/
	struct Rectangle
	{
		/** Creates a new instance of Rectangle with all 0 values
		*/
		Rectangle();

		/** Creates a new instance of Rectangle
		*	@param x The X coordinate of the Rectangle
		*	@param y the Y coordinate of the Rectangle
		*	@param width The Width of the Rectangle
		*	@param height The Height of the Rectangle
		*/
		Rectangle(int x, int y, int width, int height);
		/** Returns the Area of the Rectangle
		*/
		int area();
		/** The X location of the Rectangle
		*/
		int X;
		/** The Y location of the Rectangle
		*/
		int Y;
		/** The Width of the Rectangle
		*/
		int Width;
		/** The Hight of the Rectangle
		*/
		int Height;
		/** The Y coordinate of the Top Edge of the Rectangle
		*/
		int Top();
		/** The Y coordinate of the Bottom Edge of the Rectangle
		*/
		int Bottom();
		/** The X coordinate of the Left Edge of the Rectangle
		*/
		int Left();
		/** The X coordinate of the Right Edge of the Rectangle
		*/
		int Right();
		/** Checks if one Rectangle intersects another
		*	@param rect2 The Rectangle to Check for Intersection against
		*	@returns Whether or not the two Rectangles intersect
		*/
		bool intersects(Rectangle* rect2);
	};
}
#endif
