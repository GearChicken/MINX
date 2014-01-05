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
				void handleEvent(GameTime * gameTime);
				/** Gets the Position of the Mouse on the Screen (Realtive to GameWindow)
				*/
				Vector2 getPositionOnScreen();
				/** Gets the Relative Motion of the Mouse on the Screen (Realitive to the GameWindow's Center)
				*/
				Vector2 getRelativeMotion();
				/** Gets the Total Accumulated Position of the Mouse on the Screen (Realitive to the GameWindow's Center)
				*/
				Vector2 getAccumulatedPosition();
				/** Gets a button for the state of the mouse button at 'buttonID'
				*	@param buttonID The Identifier of the Mouse Button to get the state of
				*/
				Button getMouseButton(int buttonID);
		};
	}
}
#endif
