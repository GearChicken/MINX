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

Color* MINX::Graphics::Primitives::pixelToColor(Uint32 pixel, SDL_Surface * surface)
{
	Uint8 * r;
	Uint8 * g;
	Uint8 * b;
	Uint8 * a;
	SDL_GetRGBA(pixel,surface->format,r,g,b,a);
	return new Color(*r,*g,*b,*a);
}
Color* MINX::Graphics::Primitives::pixelToColor(int x, int y, SDL_Surface* surface)
{
	Uint32 *pixels = (Uint32*)surface->pixels;
	return pixelToColor(*(pixels + y * 4 * surface->w + x * 4), surface);
}
void MINX::Graphics::Primitives::colorToPixel(MINX::Graphics::Color* color, int x, int y, SDL_Surface* surface)
{
	if(y > 0 && x > 0 && y < surface->h && x < surface->w)
	{
		Uint32 *pixels = (Uint32 *) surface->pixels;
		Uint32 pixel = SDL_MapRGBA(surface->format,color->R,color->G,color->B,color->A);
		pixels[(y * surface->w)+x] = pixel;
	}
}
void MINX::Graphics::Primitives::drawRectangle(Color* color, int x, int y, int w, int h, SDL_Surface* surface)
{
	for(int i = y; i < y+h; i++)
	{
		for(int j = x; j < x+w; j++)
		{
			colorToPixel(color,j,i,surface);
		}
	}
}
void MINX::Graphics::Primitives::drawOutlineRectangle(Color* color, int x, int y, int w, int h, SDL_Surface* surface)
{
	for(int i = y; i < y+h; i++)
	{
		colorToPixel(color,x,i,surface);
		colorToPixel(color,x+w,i,surface);
	}
	for(int j = x; j < x+w; j++)
	{
		colorToPixel(color,j,y,surface);
		colorToPixel(color,j,y+h,surface);
	}
}
