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
#ifndef GAME_H_
#define GAME_H_
#include <string>
#include <vector>
#include <iostream>
#include "SDL/SDL.h"
#include "GameComponent.h"
#include "GameTime.h"
#include "Event.h"
#include "Graphics/GameWindow.h"

using namespace std;

namespace MINX
{
	typedef void function(SDL_Event * event);
	class Game 
	{
		public:
			Game();
			virtual void Initialize();
			virtual void LoadContent();
			virtual void Update(GameTime * gameTime);
			virtual void UnloadContent();
			virtual void Draw(GameTime * gameTime);
			void Run();
			void addEventHandler(Event evt_type, function callback);
			Graphics::GameWindow* gameWindow;
			vector<GameComponent*>* Components;
			GameTime * getGameTime();
		private:
			SDL_Event event;
			GameTime* gameTime;
		protected:
			bool isRunning;
	};
}
#endif
