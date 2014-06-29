/*
MINX - A C++ Graphics and Input Wrapper Library
Copyright (C) 2013-2014  MINX Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef GAME_H_
#define GAME_H_
#define MINX_DEBUG

#include "API.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <queue>
#include <iostream>

#include "Graphics/Font.h"
#include "Graphics/RenderTarget.h"
#include "GameComponent.h"
#include "GameTime.h"
#include "Graphics/GameWindow.h"
#include <thread>
#include <mutex>
using namespace std;

namespace MINX
{
	/** The class that handles everything.
	* When using the library, your code will probably construct, Initialize() and Run() your subclass of Game.
	*/
	class MINX_API Game 
	{
	public:
		/** The constructor, which handles some of the initialization code for the Game.
		*/
		Game();
		
		/** This handles the rest of the initialization code for the game.
		*/
		virtual void Initialize();
		
		/** Loads content used by the game.
		*/
		virtual void LoadContent();
		
		/** Updates the game state.
		* Should be extended when you create a subclass of Game.
		* @param gameTime the GameTime to use when updating.
		*/
		virtual void Update(GameTime * gameTime);
		
		/** Unloads content used by the game.
		*/
		virtual void UnloadContent();
		
		/** Draws the state of the game every frame.
		* This method is called by a different thread than Update(), so it is ok to use sleeps in Update() and not worry about freezing the drawing, or vice versa.
		* @param gameTime the GameTime to use when drawing.
		*/
		virtual void Draw(GameTime * gameTime);
		
		/** Handles Update()ing, Draw()ing, and event handling.
		*/
		void Run();
		
		/** A pointer to the window used by the game.
		*/
		Graphics::GameWindow* gameWindow;
		
		/** A pointer to a vector of pointers to the GameComponents used in the game.
		*/
		vector<GameComponent*>* Components;
		
		/** Returns a pointer to the GameTime being used by the game.
		*/
		GameTime* GetGameTime();
		
		/** Set the video options when creating a new GameWindow
		*	@param windowWidth The Width of the GameWindow
		*	@param windowHeight The Height of the GameWindow
		*	@param fullscreen Whether or not the window is fullscreen
		*/
		void SetVideoOptions(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen);
		
		/** Set the video options when creating a new GameWindow
		*	@param windowWidth The Width of the GameWindow
		*	@param windowHeight The Height of the GameWindow
		*	@param fullscreen Whether or not the window is fullscreen
		*	@param windowTitle The title of the GameWindow
		*/
		void SetVideoOptions(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, char* windowTitle);
		
		/** Is the Game Running, or should it close?
		*/
		bool isRunning;
		
		/** Set's the Game's RenderTarget and clears to the clearColor.
		 */
		void SetRenderTarget(Graphics::RenderTarget* target, Graphics::Color clearColor);

		/** Set's the Game's RenderTarget and clears to cornflower blue.
		 */
		void SetRenderTarget(Graphics::RenderTarget* target);
	protected:
		/** An instance of freetype used to draw text
		*/
		FT_Library freeTypeLibrary;
		
	private:
		/** A pointer to the GameTime being used by the game.
		*/
		GameTime* gameTime;
		
		/** The width of the window
		 */
		int windowWidth;
		
		/** The height of the window
		 */
		int windowHeight;
		
		/** Whether or not the window is fullscreen
		*/
		bool fullscreen;
		
		/** The title of the window
		 */
		char* windowTitle;
		
		/** The current RenderTarget for the game
		 */
		static Graphics::RenderTarget* activeRenderTarget;
		
		friend class MINX::Graphics::Font;
	};
}
#endif
