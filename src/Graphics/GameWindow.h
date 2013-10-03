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
#ifndef GAME_WINDOW_H_
#define GAME_WINDOW_H_
#include <GL/glfw.h>
namespace MINX
{
	namespace Graphics
	{
		class GameWindow
		{
			public:
				GameWindow(int width, int height, int bpp, int flags);
				GameWindow(int width, int height, int bpp, int flags, char* title);
				static int width, height;
				int bpp;
				int flags;
			private:
		};
	}
}
#endif
