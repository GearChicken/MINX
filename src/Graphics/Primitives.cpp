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
	SDL_PixelFormat *fmt;
	fmt=surface->format;
	Uint32 temp;
	Uint8 red, green, blue, alpha;	
	/* Get Red component */
	temp=pixel&fmt->Rmask; /* Isolate red component */
	temp=temp>>fmt->Rshift;/* Shift it down to 8-bit */
	temp=temp<<fmt->Rloss; /* Expand to a full 8-bit number */
	red=(Uint8)temp;

	/* Get Green component */
	temp=pixel&fmt->Gmask; /* Isolate green component */
	temp=temp>>fmt->Gshift;/* Shift it down to 8-bit */
	temp=temp<<fmt->Gloss; /* Expand to a full 8-bit number */
	green=(Uint8)temp;

	/* Get Blue component */
	temp=pixel&fmt->Bmask; /* Isolate blue component */
	temp=temp>>fmt->Bshift;/* Shift it down to 8-bit */
	temp=temp<<fmt->Bloss; /* Expand to a full 8-bit number */
	blue=(Uint8)temp;

	/* Get Alpha component */
	temp=pixel&fmt->Amask; /* Isolate alpha component */
	temp=temp>>fmt->Ashift;/* Shift it down to 8-bit */
	temp=temp<<fmt->Aloss; /* Expand to a full 8-bit number */
	alpha=(Uint8)temp;
	return new Color(red, green, blue, alpha);
}
Color* MINX::Graphics::Primitives::pixelToColor(int x, int y, SDL_Surface* surface)
{
	SDL_LockSurface(surface);
	Uint32 *pixels = (Uint32*)surface->pixels;
	SDL_UnlockSurface(surface);
	return pixelToColor(*(pixels + y * surface->w + x), surface);
}
void MINX::Graphics::Primitives::drawColorToPixel(MINX::Graphics::Color* color, int x, int y, SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, color->R, color->G, color->B, color->A);
	SDL_RenderDrawPoint(renderer, x, y);
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
void MINX::Graphics::Primitives::drawRectangle(Color* color, int x, int y, int w, int h, SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, color->R, color->G, color->B, color->A);
	SDL_Rect* rect = new SDL_Rect();
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	SDL_RenderFillRect(renderer, rect);
	delete rect;
}
void MINX::Graphics::Primitives::drawOutlineRectangle(Color* color, int x, int y, int w, int h, SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, color->R, color->G, color->B, color->A);
	SDL_Rect* rect = new SDL_Rect();
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	SDL_RenderDrawRect(renderer, rect);
	delete rect;
}
