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
#ifndef I_GENERIC_HID_H_
#define I_GENERIC_HID_H_

#include "../GameTime.h"
#include "../GameComponent.h"
#include "SDL/SDL.h"
#include "Button.h"
#include "Axis.h"
#include "../Game.h"
#include <vector>

namespace MINX
{
	namespace Input
	{
		class IGenericHID : public GameComponent
		{
			public: 
				IGenericHID(Game * game, int buttonVectorSize, int axisVectorSize);
				vector<Button> * buttons;
				vector<Axis> * axes;
				virtual void Update(GameTime * gameTime);
				Button getButton(int id);
				Axis getAxis(int id);
			private:
				SDL_Event* inputEvent;
		};
	}
}
#endif
