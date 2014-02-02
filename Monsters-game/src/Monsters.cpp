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
#include <Graphics/Font.h>
#include <Graphics/TextureBatch.h>
#include <Graphics/ShaderFactory.h>
#include <Media/SoundPlaylist.h>

using namespace MINX_monsters;
using namespace MINX;
using namespace MINX::Graphics;
using namespace MINX::Media;
Font* testFont;
vector<Monster*>* monsters;
Texture2D* monsterTexture;
Texture2D* penTex;
TextureBatch* texBatch;
SoundPlaylist* playlist;

MonsterGame::MonsterGame()
{
	//This is the constructor. Put stuff here that should happen when the Game is created.
	srand(time(NULL));
	Game::SetVideoOptions(1024, 768, 32, 0, "MINX Monster Game!");
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
	std::cout << std::endl << "Due to a bug in the MINX Framework this game must be closed through the Console Window!" << std::endl;
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
	//ShaderFactory::GetInstance()->LoadShaderFromFile("vertexShader.glsl", "fragmentShader.glsl");
	//ShaderFactory::GetInstance()->LoadShaderFromFile("fontVertexShader.glsl", "fontFragmentShader.glsl");

	playlist = new SoundPlaylist(this);

	playlist->AddSound("Converted_file_c2ef41aa.ogg");
	playlist->AddSound("Kalimba_-_Mr. Scruff_(HD).mp3");
	texBatch = new TextureBatch(ShaderFactory::GetInstance()->GetShaderAtIndex(0));

	penTex = new Texture2D("penguin.jpg");

	
	monsterTexture = new Texture2D("gem.png");
	monsters->push_back(new Bouncer(new Vector2(10,10), monsterTexture));
	monsters->push_back(new Wrapper(new Vector2(10,10), monsterTexture));
	monsters->push_back(new PatternMonster(new Rectangle(6*8,5*8,50*8,8*8), monsterTexture));
	monsters->push_back(new RandomMonster(new Vector2(GameWindow::GetWidth()/2,GameWindow::GetHeight()/2), monsterTexture));
	monsters->push_back(new Monster(new Vector2(14*8,14*8), monsterTexture, new Graphics::Color(255.0f,255.0f,255.0f), this));
	//*/

	testFont = new Font(freeTypeLibrary, "Ubuntu-B.ttf", ShaderFactory::GetInstance()->GetShaderAtIndex(1));
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
	//*/
	
	if(keyboard->GetButton(Input::Keys::KEY_ESCAPE).state)
	{
		isRunning = false;
	}
	if(keyboard->GetButton(Input::Keys::KEY_ENTER).state && !keyboard->GetButton(Input::Keys::KEY_ENTER).prevState)
	{
		playlist->Play();
	}

	//gameTime->LimitFPS(60);

}

void MonsterGame::Draw(GameTime* gameTime)
{
	glClearColor( 100/255.0f, 149/255.0f, 237/255.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
	
	
	texBatch->Draw(penTex, 10.0f, 10.0f, 0.25f, 0.5f, Rectangle(200,100,300,400));

	//Put stuff here to draw your game each frame.

	//std::cout << "Width: " << GameWindow::GetWidth() << " Height: " << GameWindow::GetHeight() << std::endl;
	
	
	for (int i = 0; i < 10; i++)
	{
		texBatch->Draw(monsterTexture, rand()%GameWindow::GetWidth(), rand()%GameWindow::GetHeight(), 1.0f, 1.0f, 0.0f, Color(rand()%256, rand()%256, rand()%256));

	}
	//*/

	
	for(Monster *m : *monsters)
	{
		m->Draw(texBatch);
	}//*/

	texBatch->DrawLoadedTextures();
	testFont->RenderText(" !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~", 0,  0, 12);

	Game::Draw(gameTime);
}
