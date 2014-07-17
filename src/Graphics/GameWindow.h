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
	
#ifndef GAME_WINDOW_H_
#define GAME_WINDOW_H_

#include "../API.h"

#include <GLFW/glfw3.h>

#include "Color.h"

namespace MINX
{
	namespace Graphics
	{
		/** A class that holds the GLFW window pointer and some basic info about the window
		*/
		class MINX_API GameWindow
		{
			public:
				/** Creates a new instance of GameWindow
				*	@param width The Width of the GameWindow
				*	@param height The Height of the GameWindow
				*	@param bpp The Bits Per Pixel of the GameWindow
				*	@param flags The flags to create the GameWindow with
				*	@param fullscreen Whether or not to initialize MINX in Fullscreen mode
				*/
				GameWindow(int width, int height, bool fullscreen);
				
				/** Creates a new instance of GameWindow
				*	@param width The Width of the GameWindow
				*	@param height The Height of the GameWindow
				*	@param bpp The Bits Per Pixel of the GameWindow
				*	@param flags The flags to create the GameWindow with
				*	@param fullscreen Whether or not to initialize MINX in Fullscreen mode
				*	@param title The Title of the GameWindow
				*/
				GameWindow(int width, int height, bool fullscreen, char* title);

				/** Returns the width of the GameWindow
				 */
				inline static int GetWidth() { return width; }

				/** Returns the height of the GameWindow
				 */
				inline static int GetHeight() { return height; }
				
				/** Sets the width of the GameWindow
				 */
				static void SetWidth(int width);
				
				/** Sets the height of the GameWindow
				 */
				static void SetHeight(int height);

				/** A Pointer to the instance of the GLFWwindow
				*/
				static GLFWwindow* window;

				/** Whether or not the window size is locked
				 */
				static bool sizeLocked;
			private:
				/** The Width of the GameWindow
				*/
				static int width;
				
				/** The Height of the GameWindow
				*/
				static int height;

		};
	}
}
#endif
