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
//#ifdef XBOX_360_GAMEPAD
#define CONTROLLER_A 0
#define CONTROLLER_X 1
#define CONTROLLER_Y 2
#define CONTROLLER_O 3
#define CONTROLLER_LB 4
#define CONTROLLER_RB 5
#define CONTROLLER_BACK 6
#define CONTROLLER_START 7
#define CONTROLLER_LEFTSTICK 8
#define CONTROLLER_RIGHTSTICK 9
#define CONTROLLER_LEFTAXIS_X 0
#define CONTROLLER_LEFTAXIS_Y 1
#define CONTROLLER_LEFTTRIGGER 3:1
#define CONTROLLER_RIGHTTRIGGER 3:-1
#define CONTROLLER_RIGHTSTICK_Y 3
#define CONTROLLER_RIGHTSTICK_X 4
//#endif
#include <gamepad/Gamepad.h>
#include "IGenericHID.h"
#include "../Game.h"
#include <functional>
namespace MINX
{
	namespace Input
	{
		/** A Sprite class that take a texture and draws it to the screen
		*/
		class GamePad : public IGenericHID
		{
			public:
				GamePad(int deviceIndex, Game* game);
				GamePad(int deviceIndex, Game* game, int gamePadType);
				static bool CheckIfDeviceValid(int deviceIndex);
				void handleEvent();
				Button getButton(int buttonID);
				Axis getAxis(int axisID);
				int deviceIndex;
				bool isConnected;
			private:
				Gamepad_device* gamePad;
				int gamePadType;
				static void GamePadRemoved(struct Gamepad_device* device, void* context);
				static void GamePadAttached(struct Gamepad_device* device, void* context);
		};

	}

}
#endif
