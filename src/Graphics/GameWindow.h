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
	
#ifndef GAME_WINDOW_H_
#define GAME_WINDOW_H_

#include <GL/glfw3.h>

namespace MINX
{
	namespace Graphics
	{
		/** A class that holds the GLFW window pointer and some basic info about the window
		*/
		class GameWindow
		{
			public:
				/** Creates a new instance of GameWindow
				*	@param width The Width of the GameWindow
				*	@param height The Height of the GameWindow
				*	@param bpp The Bits Per Pixel of the GameWindow
				*	@param flags The flags to create the GameWindow with
				*/
				GameWindow(int width, int height, int bpp, int flags);
				
				/** Creates a new instance of GameWindow
				*	@param width The Width of the GameWindow
				*	@param height The Height of the GameWindow
				*	@param bpp The Bits Per Pixel of the GameWindow
				*	@param flags The flags to create the GameWindow with
				*	@param title The Title of the GameWindow
				*/
				GameWindow(int width, int height, int bpp, int flags, char* title);
				
				inline static int GetWidth() { return width; }

				inline static int GetHeight() { return height; }
				
				inline static void SetWidth(int width) { GameWindow::width = width; }
				
				inline static void SetHeight(int height) { GameWindow::height = height; }

				/** A Pointer to the instance of the GLFWwindow
				*/
				GLFWwindow* window;
			private:
				/** The Width of the GameWindow
				*/
				static int width;
				
				/** The Height of the GameWindow
				*/
				static int height;
				
				int bpp;
				int flags;
		};
	}
}
#endif
