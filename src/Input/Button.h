/*
    MINX - A C++ Graphics and Input Wrapper Library
    Copyright (C) 2013-2014  MINX Team

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

	*/
#ifndef BUTTON_H_
#define BUTTON_H_

#include "../API.h"

namespace MINX
{
	namespace Input
	{
		/** Represents a button on an input device, such as a keyboard, mouse, or a joystick.
		 * This could also be used to create a soft button within a game.
		 */
		struct MINX_API Button
		{
			/** Sets the state of the button to state
			 */
			void SetState(bool state);
			
			/** Sets the state of the button to state
			 */
			inline void UpdateState(bool state){SetState(state);}
			
			/** Returns the current state of the button
			 */
			bool GetState();
			
			/** Returns the previous state of the button
			 */
			bool GetPrevState();
			
			/** Returns the logical and between 2 buttons.
			 */
			Button operator&&(const Button& andWith);

			/** Returns the logical or between 2 buttons.
			 */
			Button operator||(const Button& orWith);

			/** Returns the button with flipped value.
			 */
			Button operator!()const;
			private:
				/** The current state of the button.
				 */
				bool state;

				/** The previous state of the button.
				 */
				bool prevState;
		};
	}
}
#endif
