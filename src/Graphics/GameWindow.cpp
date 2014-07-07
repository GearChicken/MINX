
/*
# The zlib/libpng License

MINX Copyright (c) 2013-2014 Liam Middlebrook, Benjamin Pylko

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

#include "GameWindow.h"

using namespace MINX::Graphics;
int GameWindow::width=0;
int GameWindow::height=0;

void windowResizeCallback(GLFWwindow* window, int width, int height)
{
	if (!width|| !height)
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
	window = glfwCreateWindow(width, height, "MINX Window", monitor, NULL);
	glfwSetWindowSizeCallback(window, windowResizeCallback);
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
	window = glfwCreateWindow(width, height, title, monitor, NULL);
	glfwSetWindowSizeCallback(window, windowResizeCallback);
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
