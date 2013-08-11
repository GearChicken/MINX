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

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL/SDL.h>
#endif
namespace MINX
{
	namespace Graphics
	{
		class GameWindow
		{
			public:
#ifdef _WIN32
			__declspec(dllexport)
#endif
				GameWindow(int width, int height, int bpp, Uint32 flags);
				SDL_Surface* screen;
				int width, height, bpp;
				Uint32 flags;
			private:
		};
	}
}
#endif
