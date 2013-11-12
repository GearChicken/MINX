/*
MINX_Monsters - A C++ Game Based off the
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

#include "Monsters.h"
#include "Monster.h"
#include "Bouncer.h"
#include "Wrapper.h"
#include "PatternMonster.h"
#include "RandomMonster.h"
#include <vector>
#include <iostream>
using namespace MINX_monsters;
using namespace MINX;
using namespace MINX::Graphics;

vector<Monster*>* monsters;
Texture2D* monsterTexture;
MonsterGame::MonsterGame()
{
	//This is the constructor. Put stuff here that should happen when the Game is created.
	Game::setVideoOptions(640, 300 ,32,0,"MINX Monster Game!");
	srand(time(NULL));
	isRunning = true;
	monsters = new vector<Monster*>();
	std::cout << "Welcome to the MINX Monster Game!" << std::endl;
	std::cout << "This Game is based of a GDAPS 1 Homework intended for C# to teach inheritance." << std::endl;
	std::cout << "Each monster is derived from a base Monster class. " << std::endl;
	std::cout << "Each Monster demonstrates different movement patterns." << std::endl;
	std::cout << "Use the WASD keys to move around the White Monster." << std::endl;
	std::cout << "The Green Monster will bounce around the screen." << std::endl;
	std::cout << "The Blue Monster will wrap around the edges of the screen." << std::endl;
	std::cout << "The Red Monster will move randomly around the screen." << std::endl;
	std::cout << "The Cyan Monster will follow a rectangular movement pattern." << std::endl;
	std::cout << std::endl << "Due to a bug in the MINX Framework this game must be closed through the Console Window!\a" << std::endl;
	std::cout << std::endl << "Source code for this project can be found online at:" << std::endl << "https://github.com/GearChicken/MINX/tree/master/Monsters-game/src" << std::endl;
}

void MonsterGame::Initialize()
{
	//Put stuff here that should happen when the Game is initialized.
	Game::Initialize();
	//instantiate a new keyboard listener
	keyboard= new Input::Keyboard(this);

}

void MonsterGame::LoadContent()
{
	//Put stuff here that loads content for your game.

	monsterTexture = new Texture2D("gem.png",shaderProgram);

	monsters->push_back(new Monster(new Vector2(14*8,14*8), monsterTexture, new Graphics::Color(255.0f,255.0f,255.0f), this));
	monsters->push_back(new Bouncer(new Vector2(10,10), monsterTexture));
	monsters->push_back(new Wrapper(new Vector2(10,10), monsterTexture));
	monsters->push_back(new PatternMonster(new MINX_Rectangle(6*8,5*8,50*8,8*8), monsterTexture));
	monsters->push_back(new RandomMonster(new Vector2(GameWindow::width/2,GameWindow::height/2), monsterTexture));
	//*/
	Game::LoadContent();
}

void MonsterGame::UnloadContent()
{
	//Put stuff here that unloads content from your game


	Game::UnloadContent();
}

void MonsterGame::Update(GameTime* gameTime)
{
	//Put stuff here to update the logic in your game each tick.
	Game::Update(gameTime);
	for(Monster* m : *monsters)
	{
		m->Update(gameTime, keyboard);
	}
	if(keyboard->getButton(MINX_KEY_ESCAPE).state)
	{
		isRunning = false;
	}
}

void MonsterGame::Draw(GameTime* gameTime)
{
	glClearColor( 100/255.0f, 149/255.0f, 237/255.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
	//Put stuff here to draw your game each frame.
	for(Monster *m : *monsters)
	{
		m->Draw();
	}
	Game::Draw(gameTime);
}
