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
#include "Texture2D.h"
#include <iostream>
#include <bitset>
using namespace MINX::Graphics;
using namespace MINX::Graphics::Primitives;

Texture2D::Texture2D(SDL_Surface * surface, GameWindow * gameWindow)
{
	tex=surface;
	screen=gameWindow->screen;
}

void Texture2D::Draw(int x, int y)
{
	SDL_Rect loc;
	loc.x=x;
	loc.y=y;
	SDL_BlitSurface(tex,NULL,screen,&loc);
}

void Texture2D::Draw(int x, int y, Color* tint)
{
	Color * pixel;
	for(int i = 0; i < tex->h; i++)
	{
		for(int j = 0; j < tex->w; j++)
		{
			pixel = pixelToColor(j, i, tex);
			// The next three lines set the color the average of it's original value with a 2/3's tint bias
			pixel->R = (byte)((pixel->R + tint->R/3 - tint->G/3 - tint->B/3));
			pixel->G = (byte)((pixel->G - tint->R/3 + tint->G/3 - tint->B/3));
			pixel->B = (byte)((pixel->B - tint->R/3 - tint->G/3 + tint->B/3));
			colorToPixel(pixel, j, i, tex);
			pixel = NULL;
		}
	}
	SDL_Rect loc;
	loc.x=x;
	loc.y=y;
	SDL_BlitSurface(tex,NULL,screen,&loc);
}
