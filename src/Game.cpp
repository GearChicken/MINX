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
SDL_sem* videoLock;
Game::Game()
{	
	videoLock = SDL_CreateSemaphore(1);
	desiredFPS = 60;
	windowWidth = 640;
	windowHeight = 480;
	windowBPP = 32;
	windowFlags = SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_SRCALPHA|SDL_HWACCEL;
	Components = new vector<GameComponent*>();
	eventHandlers = new vector<EventHandler*>();
	gameTime = new GameTime();
	#if defined(LINUX) || defined(OSX)
	XInitThreads();
	#endif
}

int doDraw(void * game){
	Game * thisGame = (Game*)game;
	while(thisGame->isRunning)
	{
		SDL_SemWait(videoLock);
		thisGame->Draw(thisGame->getGameTime());
		SDL_SemPost(videoLock);
	}
	return 0;
}

int doUpdate(void * game){
	Game * thisGame = (Game*)game;
	while(thisGame->isRunning)
	{
		SDL_SemWait(videoLock);
		thisGame->Update(thisGame->getGameTime());
		SDL_SemPost(videoLock);
	}
	return 0;
}

void Game::Run()
{
	std::cout << "Game Running!\n";
	preventAutoQuitting = false;
	this->Initialize();
	this->LoadContent();
	SDL_Thread * drawingThread = SDL_CreateThread(doDraw,(void*)this);
	SDL_Thread * updatingThread = SDL_CreateThread(doUpdate,(void*)this);
	while(isRunning)
	{
		if(SDL_WaitEvent(&evt))
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
	}
	SDL_WaitThread(updatingThread,NULL);
	SDL_WaitThread(drawingThread,NULL);
	this->UnloadContent();
}

GameTime * Game::getGameTime()
{
	return gameTime;
}

void Game::Initialize()
{
	if( SDL_Init(SDL_INIT_EVERYTHING) == -1 )
	{
		std::cout << "SDL NOT INITED!\n";
	}

	if(TTF_Init() == -1 )
	{
		std::cout << "TTF NOT INITED!\n";
	}


					//uses video memory,prevents tearing,alpha works,hardware accelerated 
	 gameWindow = new GameWindow(windowWidth, windowHeight, windowBPP, windowFlags);

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
	SDL_Flip(gameWindow->screen);
}

void Game::UnloadContent()
{
    SDL_DestroySemaphore( videoLock );
	Mix_CloseAudio();
	SDL_Quit();
}

void Game::setVideoOptions(int DdesiredFPS, int DwindowWidth, int DwindowHeight, int DwindowBPP, Uint32 DwindowFlags)
{
	desiredFPS = DdesiredFPS;
	windowWidth = DwindowWidth;
	windowHeight = DwindowHeight;
	windowBPP = DwindowBPP;
	windowFlags =DwindowFlags;
}
