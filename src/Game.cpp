/*
# MINX

Copyright (c) 2013-2014 Liam Middlebrook, Benjamin Pylko

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

> 1\. The origin of this software must not be misrepresented; you must not
> claim that you wrote the original software. If you use this software
> in a product, an acknowledgment in the product documentation would be
> appreciated but is not required.
> 
> 2\. Altered source versions must be plainly marked as such, and must not be
> misrepresented as being the original software.
> 
> 3\. This notice may not be removed or altered from any source
> distribution.
>
 */

#include "Game.hpp"
#include <iostream>
#include <thread>
#if defined(LINUX) || defined(OSX)
	#include "X11/Xlib.h"
#endif

using namespace MINX;
using namespace MINX::Graphics;
using namespace std;

MINX::Graphics::RenderTarget* Game::activeRenderTarget = NULL;

Game::Game()
{
	windowWidth = 640;
	windowHeight = 480;

	#if defined(LINUX) || defined(OSX)
		XInitThreads();
	#endif

	Components = new vector<GameComponent*>();
}

int doUpdate(void * game, GameTime* gameTime)
{
	do
	{
		((Game*)game)->isRunning = !glfwWindowShouldClose(((Game*)game)->gameWindow->window);
		((Game*)game)->Update(gameTime);
	} while(((Game*)game)->isRunning);

	return 0;
}

void Game::Run()
{

	gameTime = new GameTime();

	#ifdef MINX_DEBUG
		std::cout << "Game Running!\n";
	#endif

	isRunning = true;

	this->Initialize();
	this->LoadContent();

	thread updateThread = thread(doUpdate, this, this->gameTime);
	updateThread.detach();

	do
	{
		this->Draw(this->gameTime);
	} while(isRunning);

	this->UnloadContent();

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Game::Initialize()
{

	if(!glfwInit())
	{
		std::cout << "GLFW NOT INITED!\n";
		exit(EXIT_FAILURE);
	}	

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	gameWindow = new GameWindow(windowWidth, windowHeight, fullscreen, windowTitle);
	glfwMakeContextCurrent(gameWindow->window);

	glewExperimental=true;
	if(glewInit() != GLEW_OK )
	{
		std::cout << "GLEW NOT INITED!\n";
	}

	for(vector<GameComponent*>::size_type i=0; i < Components->size(); ++i)
	{
		(*Components)[i]->Initialize();
	}

	if(FT_Init_FreeType(&freeTypeLibrary))
	{
		std::cout << "FreeType Not Inited!";
	}


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void Game::LoadContent()
{
}

void Game::Update(GameTime* gameTime)
{
	gameTime->Update();
	for (vector<GameComponent*>::size_type i=0; i < Components->size(); i++)
	{
		if((*Components)[i]->enabled)
		{
			(*Components)[i]->Update(gameTime);
		}
	}
}


void Game::Draw(GameTime* gameTime)
{
	glfwSwapBuffers(gameWindow->window);
	glfwPollEvents();

}

void Game::UnloadContent()
{
	glfwTerminate();
}

void Game::SetVideoOptions(unsigned int DwindowWidth, unsigned int DwindowHeight, bool Dfullscreen)
{
	windowWidth = DwindowWidth;
	windowHeight = DwindowHeight;
	fullscreen = Dfullscreen;
}

void Game::SetVideoOptions(unsigned int DwindowWidth, unsigned int DwindowHeight, bool Dfullscreen, char *DwindowTitle)
{
	windowWidth = DwindowWidth;
	windowHeight = DwindowHeight;
	fullscreen = Dfullscreen;
	windowTitle = DwindowTitle;
}

void Game::SetRenderTarget(RenderTarget* target, Color clearColor)
{
	//If it's already the same same the GPU some time by not changing the framebuffer
	if(activeRenderTarget != target)
	{
		activeRenderTarget = target;
		glBindTexture(GL_TEXTURE_2D, 0);

		if(target == NULL)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0,0, GameWindow::GetWidth(), GameWindow::GetHeight());
			return;
		}
		else
		{
			glBindFramebuffer(GL_FRAMEBUFFER, target->frameBuffer);
			glViewport(0,0, target->width, target->height);
		}
	}
	GLfloat color[] = {static_cast<GLfloat>(clearColor.R)/255.f, static_cast<GLfloat>(clearColor.G)/255.f, static_cast<GLfloat>(clearColor.B)/255.f, static_cast<GLfloat>(clearColor.A)/255.f};
	glClearColor(color[0], color[1], color[2], color[3]);
	glClear(GL_COLOR_BUFFER_BIT);

}
