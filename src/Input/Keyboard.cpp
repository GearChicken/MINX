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

Keyboard::Keyboard (Game * game) : IGenericHID(game,512,0) //512 might be a little high
{
}

void Keyboard::handleEvent(SDL_Event * evt,GameTime * gameTime)
{
	if(evt->type == SDL_KEYDOWN || evt->type == SDL_KEYUP)
	{
		int id = evt->key.keysym.sym;
		if(id > 0 && id < 512)
		{
			(*buttons)[id].prevState = (*buttons)[id].state;
			(*buttons)[id].state= evt->type == SDL_KEYDOWN;
		}
	}
}

Button Keyboard::getKey(char key)
{
	switch(key)
	{
		case '\n':
			return getButton(int('\r'));
		case '~':
			return getButton(int('`')) && (getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '`':
			return getButton(int('`')) && !(getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '+':
			return getButton(int('=')) && (getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '=':
			return getButton(int('=')) && !(getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '!':
			return getButton(int('1')) && (getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '1':
			return getButton(int('1')) && !(getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '@':
			return getButton(int('2')) && (getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '2':
			return getButton(int('2')) && !(getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '#':
			return getButton(int('3')) && (getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '3':
			return getButton(int('3')) && !(getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '$':
			return getButton(int('4')) && (getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '4':
			return getButton(int('4')) && !(getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '%':
			return getButton(int('5')) && (getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '5':
			return getButton(int('5')) && !(getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '^':
			return getButton(int('6')) && (getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '6':
			return getButton(int('6')) && !(getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '&':
			return getButton(int('7')) && (getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '7':
			return getButton(int('7')) && !(getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '*':
			return getButton(int('8')) && (getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '8':
			return getButton(int('8')) && !(getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '(':
			return getButton(int('9')) && (getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '9':
			return getButton(int('9')) && !(getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case ')':
			return getButton(int('0')) && (getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '0':
			return getButton(int('0')) && !(getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '|':
			return getButton(int('\\')) && (getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		case '\\':
			return getButton(int('\\')) && !(getButton(SDLK_RSHIFT) || getButton(SDLK_LSHIFT));
		default:
			return getButton(int(key));
	}
}
