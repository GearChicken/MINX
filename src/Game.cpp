/*
    MINX - A C++ Graphics and Input Wrapper Library
    Copyright (C) 2013-2014  MINX Team

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
//#define MINX_DEBUG
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glfw3.h>
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
	windowWidth = 640;
	windowHeight = 480;
	windowBPP = 32;
	windowFlags = 0;
	#if defined(LINUX) || defined(OSX)
	XInitThreads();
	#endif
	Components = new vector<GameComponent*>();
	eventHandlers = new vector<EventHandler*>();
}

int doUpdate(void * game){

		((Game*)game)->Update(((Game*)game)->getGameTime());
	
	return 0;
}
void Game::Run()
{

	gameTime = new GameTime();
#ifdef MINX_DEBUG
	std::cout << "Game Running!\n";
#endif
	this->Initialize();
	this->LoadContent();
	while(isRunning && !glfwWindowShouldClose(gameWindow->window))
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
	
	if(!glfwInit())
	{
	std::cout << "GLFW NOT INITED!\n";
		exit(EXIT_FAILURE);
	}	

	
	gameWindow = new GameWindow(windowWidth, windowHeight, windowBPP, windowFlags, windowTitle);
	glfwMakeContextCurrent(gameWindow->window);
	glewExperimental=true;
	if(glewInit() == -1 )
	{
		std::cout << "GLEW NOT INITED!\n";
	}
	for (vector<GameComponent*>::size_type i=0; i < Components->size(); i++)
	{
		(*Components)[i]->Initialize();
	}
	Gamepad_init();
	if(FT_Init_FreeType(&freeTypeLibrary))
	{
		std::cout << "FreeType Not Inited!";
	}
	/*
	 const char* vertexSource =
		"#version 330\n"
		"in vec4 coord;"
		"out vec2 texpos;"
		"uniform mat4 trans;"
		"void main() {"
		"	texpos = coord.zw;" 
		"	gl_Position = trans * vec4(coord.xy, 0.0, 1.0);"
		"}";

	 const char* fragmentSource =
		"#version 330\n"
		"in vec2 texpos;"
		"uniform sampler2D tex;"
		"uniform vec3 color;"
		"void main() {"
		"	gl_FragColor = texture(tex, texpos) * vec4(color,1.0);"
		"}";

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);	//Create a new Vertex Shader and set it to the value of vertex source
	glCompileShader(vertexShader);	// compile the vertex shader

#ifdef MINX_DEBUG
	GLint status;
	glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &status );
	//Check if the shader compiled succesfully
	
	std::cout << status << " Vertex Shader\n";
#endif
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, & fragmentSource, NULL); //Create a new Fragment shader and set it to the value of fragment source
	glCompileShader(fragmentShader);	//compile the vertexShader
	
#ifdef MINX_DEBUG
	glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &status );
	std::cout << status << " Fragment Shader\n";
#endif
	
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");



	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);


	const char* fontVertexSource =
		"#version 120\n"
		"attribute vec4 coord;"
		"varying vec2 texpos;"
		"void main() {"
		"	gl_Position = vec4(coord.xy, 0.0, 1.0);"
		"	texpos = coord.zw;" 
		"}";

	const char* fontFragmentSource =
		"#version 120\n"
		"varying vec2 texpos;"
		"uniform sampler2D tex;"
		"uniform vec4 color;"
		"void main() {"
		"	gl_FragColor = vec4(1,1,1,texture2D(tex, texpos).a)* color;"
		"}";

	 GLuint fontVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(fontVertexShader, 1, &fontVertexSource, NULL);	//Create a new Vertex Shader and set it to the value of vertex source
	glCompileShader(fontVertexShader);	// compile the vertex shader

#ifdef MINX_DEBUG
	glGetShaderiv( fontVertexShader, GL_COMPILE_STATUS, &status );
	//Check if the shader compiled succesfully
	
	std::cout << status << " Vertex Shader\n";
#endif
	GLuint fontFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fontFragmentShader, 1, & fontFragmentSource, NULL); //Create a new Fragment shader and set it to the value of fragment source
	glCompileShader(fontFragmentShader);	//compile the vertexShader
	
#ifdef MINX_DEBUG
	glGetShaderiv( fontFragmentShader, GL_COMPILE_STATUS, &status );
	std::cout << status << " Fragment Shader\n";
#endif
	
	fontShaderProgram = glCreateProgram();
	glAttachShader(fontShaderProgram, fontVertexShader);
	glAttachShader(fontShaderProgram, fontFragmentShader);
	
	glLinkProgram(fontShaderProgram);
	//*/
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
	}/*
	gameTime->limitFPS(desiredFPS);*/
}
				

void Game::Draw(GameTime * gameTime)
{
	glfwSwapBuffers(gameWindow->window);
	glfwPollEvents();

}

void Game::UnloadContent()
{
    //SDL_DestroySemaphore( videoLock );
	Gamepad_shutdown();

	glfwTerminate();
}

void Game::setVideoOptions(int DwindowWidth, int DwindowHeight, int DwindowBPP, int DwindowFlags)
{
	windowWidth = DwindowWidth;
	windowHeight = DwindowHeight;
	windowBPP = DwindowBPP;
	windowFlags =DwindowFlags;
}
void Game::setVideoOptions(int DwindowWidth, int DwindowHeight, int DwindowBPP, int DwindowFlags, char* DwindowTitle)
{
	windowWidth = DwindowWidth;
	windowHeight = DwindowHeight;
	windowBPP = DwindowBPP;
	windowFlags =DwindowFlags;
	windowTitle = DwindowTitle;
}
