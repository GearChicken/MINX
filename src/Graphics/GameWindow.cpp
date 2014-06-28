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

#include "GameWindow.h"

using namespace MINX::Graphics;
int GameWindow::width=0;
int GameWindow::height=0;
GLFWwindow* GameWindow::window = NULL;
bool GameWindow::sizeLocked = false;
RenderTarget * GameWindow::renderTarget;

void windowResizeCallback(GLFWwindow* window, int width, int height)
{
	if (!width || !height)
	{
		return;
	}
	GameWindow::SetWidth(width);
	GameWindow::SetHeight(height);
	glfwSetWindowSize(window, GameWindow::GetWidth(), GameWindow::GetHeight());
	renderTarget = new RenderTarget(GameWindow::GetWidth(), GameWindow::GetHeight());
}

GameWindow::GameWindow(int width, int height, bool fullscreen)
{
	const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	GLFWmonitor* monitor = fullscreen ? glfwGetPrimaryMonitor() : NULL;

	if(fullscreen)
	{
		width = vidMode->width;
		height = vidMode->height;
	}

	GameWindow::width = width;
	GameWindow::height = height;
	GameWindow::window = glfwCreateWindow(width, height, "MINX Window", monitor, NULL);
	renderTarget = new RenderTarget(GameWindow::GetWidth(), GameWindow::GetHeight());
	glfwSetWindowSizeCallback(GameWindow::window, windowResizeCallback);
}

GameWindow::GameWindow(int width, int height, bool fullscreen, char* title)
{
	const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	GLFWmonitor* monitor = fullscreen ? glfwGetPrimaryMonitor() : NULL;

	if(fullscreen)
	{
		width = vidMode->width;
		height = vidMode->height;
	}

	GameWindow::width = width;
	GameWindow::height = height;
	GameWindow::window = glfwCreateWindow(width, height, title, monitor, NULL);
	renderTarget = new RenderTarget(GameWindow::GetWidth(), GameWindow::GetHeight());
	glfwSetWindowSizeCallback(GameWindow::window, windowResizeCallback);
}

void GameWindow::SetHeight(int height)
{
	if(sizeLocked) return;
	GameWindow::height = height;
	glfwSetWindowSize(GameWindow::window, GameWindow::GetWidth(), GameWindow::GetHeight());
	renderTarget = new RenderTarget(GameWindow::GetWidth(), GameWindow::GetHeight());
}

void GameWindow::SetWidth(int width)
{
	if(sizeLocked) return;
	GameWindow::width = width;
	glfwSetWindowSize(GameWindow::window, GameWindow::GetWidth(), GameWindow::GetWidth());
	renderTarget = new RenderTarget(GameWindow::GetWidth(), GameWindow::GetHeight());
}
