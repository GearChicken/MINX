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

#ifndef LINE_H_
#define LINE_H_
#include "DrawableGameComponent.h"
#include "Point.h"
#include "Game.h"
#include "GameTime.h"
#include "SDL/SDL.h"
#include "SDL_gfxPrimitives.h"

namespace MINX
{
	class Line : public DrawableGameComponent
	{
		public:
			Line(int x1, int y1, int x2, int y2, Game * game, SDL_Surface * target);
			Line(Point pt1, Point pt2, Game * game, SDL_Surface * target);
			Line(Point origin, Vector2 magnitude, Game * game, SDL_Surface * target);
			void Draw(GameTime * gameTime);
			void setCoords(int x1, int y1, int x2, int y2);
			void setCoords(Point pt1, Point pt2);
			void setCoords(Point pt, Vector2 magnitude);
			
	}
}
#endif
