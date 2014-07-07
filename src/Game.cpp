/*
# The zlib/libpng License

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

#include "Game.h"
#include <iostream>
#include <thread>
#if defined(LINUX) || defined(OSX)
#include "X11/Xlib.h"
#endif

using namespace MINX;
using namespace MINX::Graphics;
using namespace std;

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
