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
<<<<<<< HEAD
#include <SDL.h>
=======
#ifdef _WIN32
#include <SDL.h>
#else
#include "SDL/SDL.h"
#endif
>>>>>>> 706fcfe2adabcbfb242a025e1b1b896fa9f64854
#include "Button.h"
#include "Axis.h"
#include "../Game.h"
#include <vector>

namespace MINX
{
	namespace Input
	{
		/** Represents any Human Interface Device that has axes and/or buttons.
		 * Extended by Keyboard, Mouse, and (in the future) Joystick classes.
		 * This class should almost NEVER be used directly, but rather a subclass should be used.
		 */
		class IGenericHID : public EventHandler
		{
			public:
				/** Constructs an IGenericHID. Fills the button and axis vectors with zeroed values.
				 * @param game A pointer to the Game to attach to.
				 * @param buttonVectorSize The total number of buttons that the device has.
				 * @param axisVectorSize The total number of axes that the device has.
				 */
#ifdef _WIN32
			__declspec(dllexport)
#endif
				IGenericHID(Game * game, int buttonVectorSize, int axisVectorSize);
				/** Contains all of the buttons used by the device.
				 */
				vector<Button> * buttons;
				/** Contains all of the axes used by the device.
				 */
				vector<Axis> * axes;
<<<<<<< HEAD
				/** Implemented by a subclass. Should modify the button and axis vectors to hold the most current information
				 */
#ifdef _WIN32
			__declspec(dllexport)
#endif
				virtual void Update(GameTime * gameTime);
=======
>>>>>>> 706fcfe2adabcbfb242a025e1b1b896fa9f64854
				/** Returns a Button from the specified index in the button vector.
				 */
#ifdef _WIN32
			__declspec(dllexport)
#endif
				Button getButton(int id);
				/** Returns an Axis from the specified index in the axis vector.
				 */
#ifdef _WIN32
			__declspec(dllexport)
#endif
				Axis getAxis(int id);
		};
	}
}
#endif
