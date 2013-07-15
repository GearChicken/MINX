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
namespace MINX
{
	namespace Graphics
	{
		struct Color
		{
			unsigned char R;
			unsigned char G;
			unsigned char B;
			unsigned char A;
			Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
			Color(unsigned char r, unsigned char g, unsigned char b);
			Color(float r, float b, float g);
			Color(float r, float b, float g, float a);
			bool operator==(const Color& compareTo);
			bool operator!=(const Color& compareTo);
		};
	}
}
#endif
