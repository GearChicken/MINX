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
#ifndef WRAPPER_H_
#define WRAPPER_H_

#include "Monster.h"
namespace MINX_monsters
{
	class Wrapper : public Monster
	{
		public:
			Wrapper(Vector2* position, Graphics::Texture2D* texture);
			void Update(GameTime* gameTime, Input::Keyboard* keyboard);
	};
}
#endif