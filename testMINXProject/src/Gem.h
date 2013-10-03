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
#include <Rectangle.h>
#include <GameTime.h>
#include <Graphics/Color.h>
#include <Graphics/Texture2D.h>
#ifndef GEM_H_
#define GEM_H_

using namespace MINX;
using namespace MINX::Graphics;

namespace MINX_GEMGAME
{
	class Gem
	{
		public:
			Gem(int X, int Y, Color* color, Texture2D* tex);
			void Draw(GameTime * gametime);
			MINX_Rectangle* rect;
			Color* color;
			Texture2D* tex;
	};
}

#endif
