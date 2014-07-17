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

#include "../API.hpp"

#include "IGenericHID.hpp"
#include "../Game.hpp"
#include "../Vector2.hpp"

#ifndef MINX_MOUSE_HPP_
#define MINX_MOUSE_HPP_

namespace MINX
{
	namespace Input
	{
		namespace MouseButtons
		{
			/** Enumerates all readable mouse buttons.
			 */
			enum MINX_API MouseButtons
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
		class MINX_API Mouse : public IGenericHID
		{
			public:
				/** Calls the IGenericHID constructor
				 */
				Mouse(Game* game);
				
				/** Grabs an event and processes it from the mouseEvents queue in the Game object provided to the constructor.
				 */
				void Update(GameTime* gametime);
				
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
