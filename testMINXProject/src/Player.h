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
#include "Game.h"
#include "Input/Keyboard.h"
#include "Vector2.h"
#include <vector>
#include "Gem.h"
#include <GL/glew.h>
#include <GL/glfw.h>
#ifndef PLAYER_H_
#define PLAYER_H_

using namespace MINX;
using namespace MINX::Graphics;
using namespace MINX::Input;
using namespace std;

namespace MINX_GEMGAME
{
	class Player
	{
		public:
			Player(int X, int Y, Texture2D* texture);
			void Update(GameTime * gametime, Keyboard* keyboard, vector<Gem*> * gems, int * score);
			void Draw(GameTime * gametime);
			float speedMultiplier;
		private:
			MINX_Rectangle* rect;
			Color* color;
			Vector2* velocity;
			Vector2 * loc;
			Texture2D* texture;
	};
}

#endif
