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
	
#include "Keyboard.h"

using namespace MINX::Input;
using namespace std;

Keyboard::Keyboard (Game * game) : IGenericHID(game,512,0) //1000 might be a little high
{
	//allan please add content
}

void Keyboard::Update(GameTime * gameTime)
{
	if(!game->keyboardEvents->empty())
	{
		SDL_Event * evt = game->keyboardEvents->front();
		if(evt != NULL)
		{
			game->keyboardEvents->pop();
			Button b;
			int id = evt->key.keysym.sym;
			cout << id << endl;
			if(id > 0 && id < 512)
			{
				b.prevState = (*buttons)[id].state;
				b.state= evt->type == SDL_KEYDOWN;
				(*buttons)[id] = b;
			}
		}
	}
}
