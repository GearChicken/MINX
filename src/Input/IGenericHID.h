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
#ifndef I_GENERIC_HID_H_
#define I_GENERIC_HID_H_

#include "../API.h"

#include "../GameTime.h"
#include "../GameComponent.h"
#include "../Game.h"

#include "Button.h"
#include "Axis.h"

#include <GLFW/glfw3.h>
#include <vector>

namespace MINX
{
	namespace Input
	{
		/** Represents any Human Interface Device that has axes and/or buttons.
		 * Extended by Keyboard, Mouse, and GamePad classes.
		 * This class should almost NEVER be used directly, but rather a subclass should be used.
		 */
		class MINX_API IGenericHID : public GameComponent
		{
			public:
				/** Constructs an IGenericHID. Fills the button and axis vectors with zeroed values.
				 * @param game A pointer to the Game to attach to.
				 * @param buttonVectorSize The total number of buttons that the device has.
				 * @param axisVectorSize The total number of axes that the device has.
				 */
				IGenericHID(Game* game, unsigned int buttonVectorSize, unsigned int axisVectorSize);
				
				/** Contains all of the buttons used by the device.
				 */
				std::vector<Button>* buttons;
				
				/** Contains all of the axes used by the device.
				 */
				std::vector<Axis>* axes;
				
				/** Returns a Button from the specified index in the button vector.
				 */
				Button GetButton(unsigned int id);
				
				/** Returns an Axis from the specified index in the axis vector.
				 */
				Axis GetAxis(unsigned int id);
		};
	}
}
#endif
