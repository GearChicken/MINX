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
#ifndef _GAMEPAD_H
#define _GAMEPAD_H

#define GENERIC_GAMEPAD 0
#define XBOX_360_GAMEPAD 1
#include <gamepad/gamepad.h>
namespace MINX
{
	namespace Input
	{
		/** A Sprite class that take a texture and draws it to the screen
		*/
		class GamePad
		{
			public:
				GamePad(int deviceIndex);
			private:
				Gamepad_device gamePad;
				int gamePadType;
		};

	}

}
#endif