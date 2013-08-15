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
#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "IGenericHID.h"
#include "Button.h"
#include <map>
namespace MINX
{
	namespace Input
	{
		/** Represents a keyboard device.
		 */
		class Keyboard : public IGenericHID
		{
			public:
				/** Calls the IGenericHID constructor with game,512,0
				 */
#ifdef _WIN32
			__declspec(dllexport)
#endif
				Keyboard(Game * game);
				/** Pulls data from the keyboardEvent queue in the Game object given to the constructor.
				 */
#ifdef _WIN32
			__declspec(dllexport)
#endif
				void handleEvent(SDL_Event * evt, GameTime * gameTime);
				Button getKey(char key);
		};
	}
}
#endif
