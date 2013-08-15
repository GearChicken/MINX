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
#ifndef GAMEPAD_H_
#define GAMEPAD_H_
#include "../Game.h"
#include "../GameTime.h"
#include "IGenericHID.h"
namespace MINX
{
	namespace Input
	{
		/** Represents a gamepad device
		 */
		class GamePad : IGenericHID
		{
			/** Constructs a GamePad, calls IGenericHID() with game,0xF1FF, 0xF1FF
			 */
#ifdef _WIN32
			__declspec(dllexport)
#endif
			GamePad(Game * game);
			/** Updates the state of the GamePad.
			 */
#ifdef _WIN32
			__declspec(dllexport)
#endif
			void handleEvent(SDL_Event * evt, GameTime * gameTime);
		};
	}
}
#endif
