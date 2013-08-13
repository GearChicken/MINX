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
#if defined(LINUX) || defined(DARWIN)
#include "X11/Xlib.h"
#endif


using namespace MINX;
using namespace MINX::Graphics;
using namespace std;

Game::Game()
{	
	desiredFPS = 60;
	windowWidth = 640;
	windowHeight = 480;
	windowBPP = 32;
	windowFlags = SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_SRCALPHA|SDL_HWACCEL;
	content = new MINX::Content(this);
	Components = new vector<GameComponent*>();
	eventHandlers = new vector<EventHandler*>();
	gameTime = new GameTime();
	#if defined(LINUX) || defined(DARWIN)
	XInitThreads();
	#endif
}

int doDraw(void * game){
	Game * thisGame = (Game*)game;
	while(thisGame->isRunning)
	{
		thisGame->Draw(thisGame->getGameTime());
	}
	return 0;
}

int doUpdate(void * game){
	Game * thisGame = (Game*)game;
	while(thisGame->isRunning)
	{
		thisGame->Update(thisGame->getGameTime());
	}
	return 0;
}

void Game::Run()
{
	preventAutoQuitting = false;
	this->Initialize();
	this->LoadContent();
	SDL_Thread * drawingThread = SDL_CreateThread(&doDraw,(void*)this);
	SDL_Thread * updatingThread = SDL_CreateThread(&doUpdate,(void*)this);
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
		gameTime->update();
		//this->Update(gameTime);
	}
	SDL_WaitThread(drawingThread,NULL);
	SDL_WaitThread(updatingThread,NULL);
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
	while (!content->TTFFonts->empty())
	{
		TTF_CloseFont((content->TTFFonts->begin()->second));
		content->TTFFonts->erase(content->TTFFonts->begin());
	}
	while (!content->textures->empty())
	{
		SDL_FreeSurface((content->textures->begin()->second->tex));
		content->textures->erase(content->textures->begin());
	}
	while (!content->audioClips->empty())
	{
		content->audioClips->erase(content->audioClips->begin());
	}
	Mix_CloseAudio();
	SDL_Quit();
}
