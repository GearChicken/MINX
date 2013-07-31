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
#ifndef COLOR_H_
#define COLOR_H_
typedef unsigned char byte;
namespace MINX
{
	namespace Graphics
	{
		/** A struct representing a color.
		 */
		struct Color
		{
			/** The red component of the color.
			 */
			byte R;
			/** The green component of the color.
			 */
			byte G;
			/** The blue component of the color.
			 */
			byte B;
			/** The alpha component of the color.
			 */
			byte A;
			/** Constructs a color with the given red, green, blue, and alpha values.
			 */
			Color(byte r, byte g, byte b, byte a);
			/** Constructs a color with the given red, green, and blue values.
			 */
			Color(byte r, byte g, byte b);
			/** Tests equality between two Colors.
			 */
			bool operator==(const Color& compareTo);
			/** Tests inequality between two Colors
			 */
			bool operator!=(const Color& compareTo);
			/** Multiplies a color by a scale.
			 */
			Color * operator*(const float& scale);
		};
	}
}
#endif
