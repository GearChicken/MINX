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
#include "Gem.h"

using namespace MINX_GEMGAME;

using namespace MINX;

MINX_GEMGAME::Gem::Gem(int X, int Y, Color* color, Texture2D* tex):rect(new Rectangle(X,Y,16,16)),color(color), tex(tex)
{

}

void MINX_GEMGAME::Gem::Draw(GameTime * gametime)
{
	//Put stuff here to draw your game each frame.
	//Graphics::Primitives::drawRectangle(color, rect->X, rect->Y, rect->Width, rect->Height, screen);
	tex->Draw(rect->X,rect->Y,1.0f,1.0f,0.0f,color);
}
