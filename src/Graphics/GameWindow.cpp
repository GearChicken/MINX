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

#include "GameWindow.h"

using namespace MINX::Graphics;
int GameWindow::width=0;
int GameWindow::height=0;

void windowResizeCallback(GLFWwindow* window, int width, int height)
{
	glfwSetWindowSize(window, GameWindow::width, GameWindow::height);
}

GameWindow::GameWindow(int width, int height, int bpp, int flags)
{
	GameWindow::width = width;
	GameWindow::height = height;
	this->bpp = bpp;
	this->flags = flags;
	window = glfwCreateWindow(width, height, "MINX Window", NULL, NULL);
	glfwSetWindowSizeCallback(window, windowResizeCallback);
}
GameWindow::GameWindow(int width, int height, int bpp, int flags, char* title)
{
	GameWindow::width = width;
	GameWindow::height = height;
	this->bpp = bpp;
	this->flags = flags;
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	glfwSetWindowSizeCallback(window, windowResizeCallback);
}
