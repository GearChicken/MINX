/*
    MINX - A C++ Graphics and Input Wrapper Library
    Copyright (C) 2013-2014  MINX Team

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
#ifndef MOUSE_H_
#define MOUSE_H_

#define MINX_MOUSE_LEFT 0
#define MINX_MOUSE_RIGHT 1
#define MINX_MOUSE_MIDDLE 2
#include "IGenericHID.h"
#include "../Game.h"
#include "../Vector2.h"
#include <GL/glfw3.h>

namespace MINX
{
	namespace Input
	{
		namespace MouseButtons
		{
			enum MouseButtons
			{
				BUTTON_1 = 0,
				BUTTON_2 = 1,
				BUTTON_3 = 2,
				BUTTON_4 = 3,
				BUTTON_5 = 4,
				BUTTON_6 = 5,
				BUTTON_7 = 6,
				BUTTON_8 = 7,
				BUTTON_LEFT = BUTTON_1,
				BUTTON_RIGHT = BUTTON_2,
				BUTTON_MIDDLE = BUTTON_3
				
			};
		}
		/** Represents a mouse device
		 */
		class Mouse : public IGenericHID
		{
			public:
				/** Calls the IGenericHID constructor with game,0xFFF,4
				 */
				Mouse(Game * game);
				
				/** Grabs an event and processes it from the mouseEvents queue in the Game object provided to the constructor.
				 */
				void Update(GameTime * gametime);
				
				/** Gets the Position of the Mouse
				*/
				Vector2 GetPosition();
				
				/** Gets a button for the state of the mouse button at 'buttonID'
				*	@param buttonID The Identifier of the Mouse Button to get the state of
				*/
				Button GetMouseButton(unsigned int buttonID);
		};
	}
}
#endif
