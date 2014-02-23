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
#ifndef COLOR_H_
#define COLOR_H_
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
			double R;
			/** The green component of the color.
			 */
			double G;
			/** The blue component of the color.
			 */
			double B;
			/** The alpha component of the color.
			 */
			double A;
			/** Constructs the Color with a default value of White
			 */
			Color();
			/** Constructs a color with the given red, green, blue, and alpha values.
			 */
			Color(double r, double g, double b, double a);
			/** Constructs a color with the given red, green, and blue values.
			 */
			Color(double r, double g, double b);
			/** Tests equality between two Colors.
			 */
			bool operator==(const Color& compareTo);
			/** Tests inequality between two Colors
			 */
			bool operator!=(const Color& compareTo);
			/** Multiplies a color by a scale.
			 */
			Color* operator*(const double& scale);
			/** Multiplies a color by a scale.
			 */
			Color* operator*=(const double& scale);
		};
	}
}
#endif
