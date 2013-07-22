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
using namespace MINX;
using namespace MINX::Graphics;

Game::Game()
{
	gameTime = NULL;
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
	while(isRunning)
	{
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

	 gameWindow = new GameWindow( 640, 480, 32, SDL_SWSURFACE);

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
	SDL_Flip(gameWindow->screen);
	//std::cout << "Screen Flipped!\n";
	SDL_Delay(50);
}

void Game::UnloadContent()
{
	SDL_Quit();
}

void Game::addEventHandler(Event evt_type, function callback)
{
	//allan please add content
}
