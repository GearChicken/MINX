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
#include "test.h"
#include <iostream>
using namespace MINX_TEST;
using namespace std;


test::test()
{
	//This is the constructor. Put stuff here that should happen when the Game is created.
isRunning = true;
}

void test::Initialize()
{
	//Put stuff here that should happen when the Game is initialized.
	std::cout << "Game INIT" << "\n";
	Game::Initialize();
	SDL_WM_SetCaption("simple window", "Window");
}

void test::LoadContent()
{

	std::cout << "Game content loaded" << "\n";
	//Put stuff here that loads content for your game.
	Game::LoadContent();
}

void test::UnloadContent()
{

	std::cout << "Game content UNloaded" << "\n";
	//Put stuff here that unloads content from your game.
	Game::UnloadContent();
}

void test::Update(GameTime * gameTime)
{
	std::cout << gameWindow->screen->w << "\n";
	//Put stuff here to update the logic in your game each tick.
	Game::Update(gameTime);
}

void test::Draw(GameTime * gameTime)
{
	cout << "test" << endl;
	SDL_FillRect(gameWindow->screen, NULL, 0x00FFFF);
	// A G R B
	Graphics::Primitives::drawRectangle(new Graphics::Color(0,0,0,255), 50, 50, 100, 100, gameWindow->screen);
	//Put stuff here to draw your game each frame.
	Game::Draw(gameTime);
	cout << "test2" << endl;
	SDL_Delay(1000);
}
