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
#include <math.h>
using namespace MINX::Graphics;
using namespace MINX::Graphics::Primitives;
using namespace std;

Texture2D::Texture2D(SDL_Surface * surface, GameWindow * gameWindow, SDL_Renderer* renderer)
{
	surf=surface;
	tex = SDL_CreateTextureFromSurface(renderer, surface);
	screen=gameWindow->screen;
	sdlRenderer = renderer;
}
Texture2D::Texture2D()
{

}

void Texture2D::Draw(int x, int y)
{
	SDL_Rect loc;
	loc.x=x;
	loc.y=y;
	//SDL_BlitSurface(tex,NULL,screen,&loc);
	SDL_UpdateTexture(tex,NULL, surf->pixels, surf->pitch);
	SDL_Rect* destRect = new SDL_Rect();
	destRect->x = x;
	destRect->y = y;
	destRect->w = surf->w;
	destRect->h = surf->h;
	SDL_RenderCopy(sdlRenderer, tex, NULL, destRect);
	delete &loc;
}

void Texture2D::Draw(int x, int y, Color* tint)
{
	if(surf != NULL){
	SDL_Surface * tempTex = SDL_ConvertSurface(surf, surf->format, surf->flags);
	Color * pixel;
	for(int i = 0; i < tempTex->h; i++)
	{
		for(int j = 0; j < tempTex->w; j++)
		{
			pixel = pixelToColor(j, i, tempTex);//
			// The next three lines set the color the average of it's original value with a 2/3's tint bias
			pixel->R = sqrt(float(tint->R)*float(pixel->R));
			pixel->G = sqrt(float(tint->G)*float(pixel->G));
			pixel->B = sqrt(float(tint->B)*float(pixel->B));
			colorToPixel(pixel, j, i, tempTex);
			delete pixel;
		}
	}
	SDL_Rect loc;
	loc.x=x;
	loc.y=y;
	//SDL_BlitSurface(tempTex,NULL,screen,&loc);
	SDL_LockTexture(tex,NULL, &(tempTex->pixels), &(tempTex->pitch));
	SDL_UnlockTexture(tex);
	SDL_Rect* destRect = new SDL_Rect();
	destRect->x = x;
	destRect->y = y;
	destRect->w = surf->w;
	destRect->h = surf->h;
	SDL_RenderCopy(sdlRenderer, tex, NULL, destRect);
	SDL_FreeSurface(tempTex);
	delete destRect;
	}
}

Texture2D::~Texture2D()
{
	SDL_DestroyTexture(tex);
	SDL_FreeSurface(surf);
}
