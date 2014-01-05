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
#ifndef RAY2_H_
#define RAY2_H_
namespace MINX
{
	/** Represents a 2 dimensional ray.
	 * Contains 2 position components and one direction (sorry) component.
	 * Of course the direction is in radians.
	 */
	struct Ray2
	{
		/** Creates a Ray2 with the specified direction and position.
		 */
			Ray2(float direction, float xPosition, float yPosition);
		/** Creates a Ray2 with the specified direction.
		 */
			Ray2(float direction);
		/** The direction of the Ray2.
		 */
		float dir;
		/** The X position of the Ray2.
		 */
		float xPos;
		/** The Y position of the Ray2.
		 */
		float yPos;
		/** Negates a Ray2.
		 */
			Ray2 operator-()const;
		/** Tests equality between 2 Ray2s.
		 */
			bool operator==(const Ray2& compareTo);
		/** Tests inequality between 2 Ray2s.
		 */
			bool operator!=(const Ray2& compareTo);
	};
}
#endif
