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
#ifndef RECTANGLE_H_
#define RECTANGLE_H_
#include <cmath>
namespace MINX
{
	struct Rectangle
	{
<<<<<<< HEAD
#ifdef _WIN32
			__declspec(dllexport)
#endif
			Rectangle(int x, int y, int width, int height);
#ifdef _WIN32
			__declspec(dllexport)
#endif
=======

			Rectangle(int x, int y, int width, int height);

>>>>>>> 706fcfe2adabcbfb242a025e1b1b896fa9f64854
			int area();
		int X;
		int Y;
		int Width;
		int Height;
<<<<<<< HEAD
#ifdef _WIN32
			__declspec(dllexport)
#endif
			int Top();
#ifdef _WIN32
			__declspec(dllexport)
#endif
			int Bottom();
#ifdef _WIN32
			__declspec(dllexport)
#endif
			int Left();
#ifdef _WIN32
			__declspec(dllexport)
#endif
			int Right();
#ifdef _WIN32
			__declspec(dllexport)
#endif
=======

			int Top();

			int Bottom();

			int Left();

			int Right();

>>>>>>> 706fcfe2adabcbfb242a025e1b1b896fa9f64854
			bool intersects(Rectangle* rect2);
	};
}
#endif
