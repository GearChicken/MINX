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
#ifndef MINX_INPUT_H_
#define MINX_INPUT_H_


#include <vector>
#ifdef _WIN32
#include <SDL.h>
#include <MINX.h>
#else
#include <SDL/SDL.h>
#include <MINX/MINX.h>
#endif
namespace MINX
{
	namespace Input{
		struct Axis
		{
			float val;
			float prevVal;
		};
		struct Button
		{
			bool state;
			bool prevState;
		};
		class IGenericHID : public GameComponent
		{
			public:
				IGenericHID(Game * game, int buttonVectorSize, int axisVectorSize);
				std::vector<Button> * buttons;
				std::vector<Axis> * axes;
				virtual void Update(GameTime * gameTime);
				Button getButton(int id);
				Axis getAxis(int id);
			protected:
				SDL_Event* evt;
		};
		class Keyboard : public IGenericHID
		{
			public:
				Keyboard(Game * game);
				void Update(GameTime * gameTime);
		};
		class Mouse : public IGenericHID
		{
			public:
				Mouse(Game * game);
				void Update(GameTime * gameTime);
		};
		class GamePad : IGenericHID
		{
			GamePad(Game * game);
			void Update(GameTime * gameTime);
		};
	}
}
#endif
