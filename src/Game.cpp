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
Graphics::GameWindow* window = NULL;
GameComponent* component = NULL;
Game::Game()
{
	gameTime = NULL;
	window = NULL;
	component = NULL;
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
	SDL_Init(SDL_INIT_EVERYTHING);

	 window = new Graphics::GameWindow(640, 480, 32, SDL_SWSURFACE);
}
void Game::LoadContent()
{

}
void Game::Update(GameTime * gameTime)
{

}
void Game::Draw(GameTime * gameTime)
{
	SDL_Flip(window->screen);
	//std::cout << "Screen Flipped!\n";
	SDL_Delay(50);
}

void Game::UnloadContent()
{
	SDL_Quit();
}
