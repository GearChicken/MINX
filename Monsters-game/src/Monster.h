/*
MINX_Monsters - A C++ Game Based off the
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
#ifndef MONSTER_H_
#define MONSTER_H_

#include <Vector2.h>
#include <GameTime.h>
#include <Input/Keyboard.h>
#include <Graphics/Color.h>
#include <Graphics/TextureBatch.h>
#include <Graphics/GameWindow.h>
#include <Input/GamePad.h>
using namespace MINX;
using namespace MINX::Input;
using namespace MINX::Graphics;
namespace MINX_monsters
{
	class Monster
	{
		public:
			Vector2* position;
			Vector2* velocity;
			Graphics::Texture2D* texture;
			Graphics::Color* color;
			Monster(Vector2* position, Graphics::Texture2D* texture, Graphics::Color* color, Game* game);
			Monster(Vector2* position, Graphics::Texture2D* texture, Graphics::Color* color);
			virtual void Update(GameTime* gameTime, Input::Keyboard* keyboard);
			void Draw(TextureBatch* texBatch);
			Input::GamePad* gamePad;
			bool usingGamePad;
	};
}
#endif