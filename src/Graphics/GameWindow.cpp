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

void windowResizeCallback(GLFWwindow* window, int width, int height)
{
	if (!width || !height)
	{
		return;
	}
	GameWindow::SetWidth(width);
	GameWindow::SetHeight(height);
	glfwSetWindowSize(window, GameWindow::GetWidth(), GameWindow::GetHeight());
	glViewport(0, 0, GameWindow::GetWidth(), GameWindow::GetHeight());
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
	glfwSetWindowSizeCallback(GameWindow::window, windowResizeCallback);
}

void GameWindow::Clear()
{
	glClearColor(0.392156863,0.584313725,0.929411765,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GameWindow::ClearColor(Color color)
{
	glClearColor(color.R/255.0, color.G/255.0, color.B/255.0, color.A/255.0);
	glClear(GL_COLOR_BUFFER_BIT);

}

void GameWindow::SetHeight(int height)
{
	if(sizeLocked) return;
	GameWindow::height = height;
	glfwSetWindowSize(GameWindow::window, GameWindow::GetWidth(), GameWindow::GetHeight());
	glViewport(0, 0, GameWindow::GetWidth(), GameWindow::GetHeight());
}

void GameWindow::SetWidth(int width)
{
	if(sizeLocked) return;
	GameWindow::width = width;
	glfwSetWindowSize(GameWindow::window, GameWindow::GetWidth(), GameWindow::GetWidth());
	glViewport(0, 0, GameWindow::GetWidth(), GameWindow::GetWidth());
}