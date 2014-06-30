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

#include "Game.h"
#include <iostream>
#include <thread>
#if defined(LINUX) || defined(OSX)
#include "X11/Xlib.h"
#endif

using namespace MINX;
using namespace MINX::Graphics;
using namespace std;

MINX::Graphics::RenderTarget* Game::activeRenderTarget = NULL;
Game::Game()
{
	windowWidth = 640;
	windowHeight = 480;

#if defined(LINUX) || defined(OSX)
	XInitThreads();
#endif

	Components = new vector<GameComponent*>();
}

int doUpdate(void * game)
{
	do
	{
		((Game*)game)->isRunning = !glfwWindowShouldClose(((Game*)game)->gameWindow->window);
		((Game*)game)->Update(((Game*)game)->GetGameTime());
	} while(((Game*)game)->isRunning);

	return 0;
}

void Game::Run()
{

	gameTime = new GameTime();

#ifdef MINX_DEBUG
	std::cout << "Game Running!\n";
#endif

	this->Initialize();
	this->LoadContent();

	thread updateThread = thread(doUpdate, this);
	updateThread.detach();

	do
	{
		this->Draw(this->gameTime);
	} while(isRunning);

	this->UnloadContent();
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

GameTime* Game::GetGameTime()
{
	return gameTime;
}

void Game::Initialize()
{

	if(!glfwInit())
	{
		std::cout << "GLFW NOT INITED!\n";
		exit(EXIT_FAILURE);
	}	


	gameWindow = new GameWindow(windowWidth, windowHeight, fullscreen, windowTitle);
	glfwMakeContextCurrent(gameWindow->window);
	glewExperimental=true;

	if(glewInit() != GLEW_OK )
	{
		std::cout << "GLEW NOT INITED!\n";
	}

	for(vector<GameComponent*>::size_type i=0; i < Components->size(); i++)
	{
		(*Components)[i]->Initialize();
	}

	if(FT_Init_FreeType(&freeTypeLibrary))
	{
		std::cout << "FreeType Not Inited!";
	}


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void Game::LoadContent()
{

}

void Game::Update(GameTime *gameTime)
{
	gameTime->Update();
	for (vector<GameComponent*>::size_type i=0; i < Components->size(); i++)
	{
		if((*Components)[i]->enabled)
		{
			(*Components)[i]->Update(gameTime);
		}
	}
}


void Game::Draw(GameTime * gameTime)
{
	glfwSwapBuffers(gameWindow->window);
	glfwPollEvents();

}

void Game::UnloadContent()
{
	glfwTerminate();
}

void Game::SetVideoOptions(unsigned int DwindowWidth, unsigned int DwindowHeight, bool Dfullscreen)
{
	windowWidth = DwindowWidth;
	windowHeight = DwindowHeight;
	fullscreen = Dfullscreen;
}

void Game::SetVideoOptions(unsigned int DwindowWidth, unsigned int DwindowHeight, bool Dfullscreen, char *DwindowTitle)
{
	windowWidth = DwindowWidth;
	windowHeight = DwindowHeight;
	fullscreen = Dfullscreen;
	windowTitle = DwindowTitle;
}

void Game::SetRenderTarget(RenderTarget* target, Color clearColor)
{
	//If it's already the same same the GPU some time by not changing the framebuffer
	if(activeRenderTarget != target)
	{
		activeRenderTarget = target;
		glBindTexture(GL_TEXTURE_2D, 0);
		if(target == NULL)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0,0, GameWindow::GetWidth(), GameWindow::GetHeight());
			return;
		}
		else
		{
			glBindFramebuffer(GL_FRAMEBUFFER, target->frameBuffer);
			glViewport(0,0, target->width, target->height);
		}
	}
	GLfloat color[] = {clearColor.R/255.0, clearColor.G/255.0, clearColor.B/255.0, clearColor.A/255.0};
	glClearColor(color[0], color[1], color[2], color[3]);
	glClear(GL_COLOR_BUFFER_BIT);

}
