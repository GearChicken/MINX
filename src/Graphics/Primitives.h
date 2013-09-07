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
#ifndef PRIMITIVES_H_
#define PRIMITIVES_H_
#ifdef _WIN32
#include <SDL.h>
#else
#include "SDL/SDL.h"
#endif
#include "Color.h"
typedef unsigned char byte;


namespace MINX
{
	namespace Graphics
	{
		namespace Primitives
		{
			Color* pixelToColor(Uint32 pixel, SDL_Surface* surface);
			Color* pixelToColor(int x, int y, SDL_Surface* surface);
			void colorToPixel(Color* color, int x, int y, SDL_Surface* surface);
			void drawColorToPixel(Color* color, int x, int y, SDL_Renderer* surface);
			void drawRectangle(Color* color, int x, int y, int w, int h, SDL_Renderer* renderer);
			void drawOutlineRectangle(Color* color, int x, int y, int w, int h, SDL_Renderer* renderer);
		}
	}
}
#endif
