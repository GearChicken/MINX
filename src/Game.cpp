/*
    MINX - A C++ Graphics and Input Wrapper Library
    Copyright (C) 2013  MINX Team

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
#include "Game.h"
#include <iostream>
#if defined(LINUX) || defined(OSX)
#include "X11/Xlib.h"
#endif


using namespace MINX;
using namespace MINX::Graphics;
using namespace std;
mutex * videoLock;
Game::Game()
{	
	videoLock = new mutex();
	desiredFPS = 60;
	windowWidth = 640;
	windowHeight = 480;
	windowBPP = 32;
	windowFlags = 0;
	Components = new vector<GameComponent*>();
	eventHandlers = new vector<EventHandler*>();
	gameTime = new GameTime();
	#if defined(LINUX) || defined(OSX)
	XInitThreads();
	#endif
}

int doUpdate(void * game){
	Game * thisGame = (Game*)game;
	while(thisGame->isRunning)
	{
		#ifdef _WIN32
		videoLock->lock();
		#endif
		thisGame->Update(thisGame->getGameTime());
		#ifdef _WIN32
		videoLock->unlock();
		#endif
	}
	return 0;
}

void Game::Run()
{
	std::cout << "Game Running!\n";
	preventAutoQuitting = false;
	this->Initialize();
	this->LoadContent();
	SDL_Thread * updatingThread = SDL_CreateThread(doUpdate,"a",(void*)this);
	while(isRunning)
	{
		if(SDL_PollEvent(&evt))
		{
			for(vector<EventHandler*>::size_type i = 0; i < eventHandlers->size(); i++)
			{
				(*eventHandlers)[i]->handleEvent(&evt,gameTime);
			}
			if(evt.type == SDL_QUIT)
			{
				isRunning = preventAutoQuitting;
			}
		}
		videoLock->lock();
		this->Draw(this->gameTime);
		
		videoLock->unlock();
	}
	SDL_WaitThread(updatingThread,NULL);
	this->UnloadContent();
}

GameTime * Game::getGameTime()
{
	return gameTime;
}

void Game::Initialize()
{
	if(glfwInit() == -1)
	{
		std::cout << "GLFW NOT INITED!\n";
	}
	gameWindow = new GameWindow(windowWidth, windowHeight, windowBPP, windowFlags, "Window");
	glewExperimental=true;
	if(glewInit() == -1 )
	{
		std::cout << "GLEW NOT INITED!\n";
	}
	for (vector<GameComponent*>::size_type i=0; i < Components->size(); i++)
	{
		(*Components)[i]->Initialize();
	}
}
void Game::LoadContent()
{

}
void Game::Update(GameTime * gameTime)
{
	gameTime->update();
	for (vector<GameComponent*>::size_type i=0; i < Components->size(); i++)
	{
		if((*Components)[i]->enabled)
		{
			(*Components)[i]->Update(gameTime);
		}
	}
	gameTime->limitFPS(desiredFPS);
}
void Game::Draw(GameTime * gameTime)
{
	SDL_RenderPresent(sdlRenderer);
}

void Game::UnloadContent()
{
    //SDL_DestroySemaphore( videoLock );
	glfwTerminate();
}

void Game::setVideoOptions(int DdesiredFPS, int DwindowWidth, int DwindowHeight, int DwindowBPP, int DwindowFlags)
{
	desiredFPS = DdesiredFPS;
	windowWidth = DwindowWidth;
	windowHeight = DwindowHeight;
	windowBPP = DwindowBPP;
	windowFlags =DwindowFlags;
}
void Game::setVideoOptions(int DdesiredFPS, int DwindowWidth, int DwindowHeight, int DwindowBPP, int DwindowFlags, char* DwindowTitle)
{
	desiredFPS = DdesiredFPS;
	windowWidth = DwindowWidth;
	windowHeight = DwindowHeight;
	windowBPP = DwindowBPP;
	windowFlags =DwindowFlags;
	windowTitle = DwindowTitle;
}
