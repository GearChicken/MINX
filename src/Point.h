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
	
#ifndef POINT_H_
#define POINT_H_
namespace MINX
{
	/** A structure that represents a point.
	 */
	struct Point
	{
		/** Constructs a Point with the specified X and Y coordinates.
		 * @param x the x coordinate of the Point.
		 * @param y the y coordinate of the Point.
		 */
			Point(int x, int y);
		/** The X coordinate of the Point.
		 */
		int X;
		/** The Y coordinate of the Point.
		 */
		int Y;
		/** Tests equality between 2 Points.
		 * @param compareTo the Point to compare this one to.
		 */
			bool operator==(const Point& compareTo);
		/** Tests equality between 2 Points.
		 * @param compareTo the Point to compare this one to.
		 */
			bool operator!=(const Point& compareTo);
	};
}
#endif
