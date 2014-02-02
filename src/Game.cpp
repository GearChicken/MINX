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

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glfw3.h>
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
	windowBPP = 32;
	windowFlags = 0;
	
	#if defined(LINUX) || defined(OSX)
		XInitThreads();
	#endif
	
	Components = new vector<GameComponent*>();
}

int doUpdate(void * game)
{
	do
	{
		((Game*)game)->Update(((Game*)game)->getGameTime());
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
		isRunning = !glfwWindowShouldClose(gameWindow->window);
		this->Draw(this->gameTime);
	} while(isRunning);
	
	this->UnloadContent();
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

GameTime* Game::getGameTime()
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

	
	gameWindow = new GameWindow(windowWidth, windowHeight, windowBPP, windowFlags, windowTitle);
	glfwMakeContextCurrent(gameWindow->window);
	glewExperimental=true;
	
	if(glewInit() != GLEW_OK )
	{
		std::cout << "GLEW NOT INITED!\n";
	}
	
	for (vector<GameComponent*>::size_type i=0; i < Components->size(); i++)
	{
		(*Components)[i]->Initialize();
	}
	
	Gamepad_init();
	
	if(FT_Init_FreeType(&freeTypeLibrary))
	{
		std::cout << "FreeType Not Inited!";
	}

	libVLCInstance = libvlc_new(0, NULL);

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
	Gamepad_shutdown();


	libvlc_release(libVLCInstance);

	glfwTerminate();
}

void Game::SetVideoOptions(unsigned int DwindowWidth, unsigned int DwindowHeight, unsigned int DwindowBPP, unsigned int DwindowFlags)
{
	windowWidth = DwindowWidth;
	windowHeight = DwindowHeight;
	windowBPP = DwindowBPP;
	windowFlags =DwindowFlags;
}

void Game::SetVideoOptions(unsigned int DwindowWidth, unsigned int DwindowHeight, unsigned int DwindowBPP, unsigned int DwindowFlags, char *DwindowTitle)
{
	windowWidth = DwindowWidth;
	windowHeight = DwindowHeight;
	windowBPP = DwindowBPP;
	windowFlags =DwindowFlags;
	windowTitle = DwindowTitle;
}
