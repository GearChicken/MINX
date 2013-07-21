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
using namespace MINX;

GameTime* gameTime = NULL;
vector<GameComponent*>* Components;
SDL_Surface* screen = NULL;
Game::Game()
{
	gameTime = NULL;
}
void Game::Run()
{	
	this->Initialize();
	this->LoadContent();
	while(isRunning)
	{
		this->Update(gameTime);
		this->Draw(gameTime);
	}
	this->UnloadContent();
}
void Game::Initialize()
{
	if( SDL_Init(SDL_INIT_EVERYTHING) == -1 )
	{
		std::cout << "SDL NOT INITED!\n";
	}

	 screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE);

	/*for (vector<GameComponent*>::size_type i=0; i != Components->size(); i++)
	{
		(*Components)[i]->Initialize();
	}//*/
}
void Game::LoadContent()
{

}
void Game::Update(GameTime * gameTime)
{
	/*for (vector<GameComponent*>::size_type i=0; i != Components->size(); i++)
	{
		(*Components)[i]->Update(gameTime);
	}//*/
}
void Game::Draw(GameTime * gameTime)
{
	SDL_Flip(screen);
	//std::cout << "Screen Flipped!\n";
	SDL_Delay(50);
}

void Game::UnloadContent()
{
	SDL_Quit();
}
