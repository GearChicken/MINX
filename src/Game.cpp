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
#include <thread>
#if defined(LINUX) || defined(DARWIN)
#include "X11/Xlib.h"
#endif
using namespace MINX;
using namespace MINX::Graphics;
using namespace std;

Game::Game()
{	
	desiredFPS = 60;
	Components = new vector<GameComponent*>();
	keyboardEvents = new queue<SDL_Event*>();
	gameTime = NULL;
	#if defined(LINUX) || defined(DARWIN)
	XInitThreads();
	#endif
}

int doDraw(Game * game){
	while(1)
	{
		game->Draw(game->getGameTime());
	}
	return 0;
}

void Game::Run()
{	
	this->Initialize();
	this->LoadContent();
	std::thread drawingThread(&doDraw, this);
	SDL_Event evt;
	while(isRunning)
	{
		if(SDL_PollEvent(&evt))
		{
			switch(evt.type)
			{
				case SDL_ACTIVEEVENT:
					break;
				case SDL_KEYDOWN:
					keyboardEvents->push(&evt);
					break;
				case SDL_KEYUP:
					keyboardEvents->push(&evt);
					break;
				case SDL_MOUSEMOTION:
					break;
				case SDL_MOUSEBUTTONDOWN:
					break;
				case SDL_MOUSEBUTTONUP:
					break;
				case SDL_JOYAXISMOTION:
					break;
				case SDL_JOYBALLMOTION:
					break;
				case SDL_JOYHATMOTION:
					break;
				case SDL_JOYBUTTONDOWN:
					break;
				case SDL_JOYBUTTONUP:
					break;
				case SDL_VIDEORESIZE:
					break;
				case SDL_VIDEOEXPOSE:
					break;
				case SDL_QUIT:
					this->UnloadContent();
					exit(0);
					break;
				case SDL_USEREVENT:
					break;
				case SDL_SYSWMEVENT:
					break;
			}
				
		}
		this->Update(gameTime);
	}
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


					//uses video memory      prevents tearing  alpha works  hardware accelerated 
	 gameWindow = new GameWindow(640, 480, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_SRCALPHA|SDL_HWACCEL);

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
		(*Components)[i]->Update(gameTime);
	}
	int NextTick = SDL_GetTicks() + (1000/desiredFPS);
	if(NextTick > SDL_GetTicks())
	{
		SDL_Delay(NextTick - SDL_GetTicks());
	}
	NextTick = SDL_GetTicks() + (1000/desiredFPS);
}
void Game::Draw(GameTime * gameTime)
{
	SDL_Flip(gameWindow->screen);
}

void Game::UnloadContent()
{
	SDL_Quit();
}
