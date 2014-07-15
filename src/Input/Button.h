/*
# MINX

Copyright (c) 2013-2014 Liam Middlebrook, Benjamin Pylko

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

> 1\. The origin of this software must not be misrepresented; you must not
> claim that you wrote the original software. If you use this software
> in a product, an acknowledgment in the product documentation would be
> appreciated but is not required.
>
> 2\. Altered source versions must be plainly marked as such, and must not be
> misrepresented as being the original software.
>
> 3\. This notice may not be removed or altered from any source
> distribution.
>
 */

#include "../API.h"

#ifndef BUTTON_H_
#define BUTTON_H_

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
