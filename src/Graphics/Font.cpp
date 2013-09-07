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
#include "Font.h"
#include <iostream>
#include <bitset>
using namespace MINX::Graphics;

void MINX::Graphics::DrawString(int x, int y, string text, SDL_Renderer* renderer, TTF_Font * font)
{
#ifdef _WIN32
	SDL_Color white = {255,255,255};
	SDL_Surface* messageTex = TTF_RenderText_Solid(font, text.c_str(), white);
#else
	SDL_Surface* messageTex = TTF_RenderText_Solid(font, text.c_str(), {255,255,255});
#endif
	SDL_Rect* loc =  new SDL_Rect();
	loc->x=x;
	loc->y=y;
	TTF_SizeText(font, text.c_str(), &(loc->w), &(loc->h));
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, messageTex);
	SDL_RenderCopy(renderer, tex, NULL, loc);
	SDL_FreeSurface(messageTex);
	SDL_DestroyTexture(tex);
	delete loc;
}
