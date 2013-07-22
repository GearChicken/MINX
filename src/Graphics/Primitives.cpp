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
#include "Primitives.h"
#include <iostream>
#include <bitset>
using namespace MINX::Graphics;
using namespace MINX::Graphics::Primitives;

Color* MINX::Graphics::Primitives::pixelToColor(Uint32 pixel)
{
	Uint8 *colors = (Uint8*)&pixel;
	return new Color(colors[0], colors[1], colors[2]);
}
Color* MINX::Graphics::Primitives::pixelToColor(int x, int y, SDL_Surface* surface)
{
	Uint32 *pixels = (Uint32*)surface->pixels;
	Uint8 *colors = (Uint8*)&pixels[(y * surface->w +x)];
	return new Color(colors[3], colors[2], colors[1]);
}
void MINX::Graphics::Primitives::colorToPixel(MINX::Graphics::Color* color, int x, int y, SDL_Surface* surface)
{
	Uint32 *pixels = (Uint32 *) surface->pixels;
	Uint8 colors[4];
	colors[0] = color->R;
	colors[1] = color->G;
	colors[2] = color->B;
	colors[3] = color->A;
	Uint32 pixel = ((colors[0]<<24)|(colors[1]<<16)|(colors[2]<<8)|(colors[3]));
	pixels[(y * surface->w)+x] = pixel;
}
void MINX::Graphics::Primitives::drawRectangle(Color* color, int x, int y, int w, int h, SDL_Surface* surface)
{
	for(int i = y; i < h; i++)
	{
		for(int j = x; j < w; j++)
		{
			colorToPixel(color,j,i,surface);
		}
	}
}
