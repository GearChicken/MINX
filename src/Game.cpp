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
Game::Game()
{	
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
		thisGame->Update(thisGame->getGameTime());
	}
	return 0;
}

void Game::Run()
{
	std::cout << "Game Running!\n";
	preventAutoQuitting = false;
	this->Initialize();
	this->LoadContent();

	while(isRunning)
	{
		for(vector<EventHandler*>::size_type i = 0; i < eventHandlers->size(); i++)
		{
			(*eventHandlers)[i]->handleEvent();
		}
		doUpdate(this);
		this->Draw(this->gameTime);
	}
	this->UnloadContent();
}

GameTime* Game::getGameTime()
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
	//
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
