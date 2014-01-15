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
//#define MINX_DEBUG
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
	eventHandlers = new vector<EventHandler*>();
}

int doUpdate(void * game)
{
	while(((Game*)game)->isRunning)
	{
		((Game*)game)->Update(((Game*)game)->getGameTime());
	}
	return 0;
}

int audioUpdate(void * game)
{
	while(((Game*)game)->isRunning)
	{
		gau_manager_update(((Game*)game)->gorillaManager);
	}
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
	thread audioThread = thread(audioUpdate, this);
	thread updateThread = thread(doUpdate, this);
	updateThread.detach();
	audioThread.detach();
	while(isRunning)
	{
		isRunning = !glfwWindowShouldClose(gameWindow->window);
		for(vector<EventHandler*>::size_type i = 0; i < eventHandlers->size(); i++)
		{
			(*eventHandlers)[i]->HandleEvent();
		}
		//doUpdate(this);
		this->Draw(this->gameTime);
	}
	updateThread.~thread();
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
	if(glewInit() == -1 )
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

	gc_initialize(0);

	gorillaManager = gau_manager_create();

	gorillaMixer = gau_manager_mixer(gorillaManager);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}
void Game::LoadContent()
{

}
void Game::Update(GameTime * gameTime)
{
	gameTime->Update();
	for (vector<GameComponent*>::size_type i=0; i < Components->size(); i++)
	{
		if((*Components)[i]->enabled)
		{
			(*Components)[i]->Update(gameTime);
		}
	}

	/*
	gameTime->limitFPS(desiredFPS);*/
}
				

void Game::Draw(GameTime * gameTime)
{
	glfwSwapBuffers(gameWindow->window);
	glfwPollEvents();

}

void Game::UnloadContent()
{
    //SDL_DestroySemaphore( videoLock );
	Gamepad_shutdown();
	gau_manager_destroy(gorillaManager);
	gc_shutdown();
	glfwTerminate();
}

void Game::SetVideoOptions(int DwindowWidth, int DwindowHeight, int DwindowBPP, int DwindowFlags)
{
	windowWidth = DwindowWidth;
	windowHeight = DwindowHeight;
	windowBPP = DwindowBPP;
	windowFlags =DwindowFlags;
}
void Game::SetVideoOptions(int DwindowWidth, int DwindowHeight, int DwindowBPP, int DwindowFlags, char* DwindowTitle)
{
	windowWidth = DwindowWidth;
	windowHeight = DwindowHeight;
	windowBPP = DwindowBPP;
	windowFlags =DwindowFlags;
	windowTitle = DwindowTitle;
}
