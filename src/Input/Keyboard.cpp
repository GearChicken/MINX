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

#include "Keyboard.h"

using namespace MINX::Input;
using namespace MINX;
using namespace std;

			

Keyboard::Keyboard (Game * game) : IGenericHID(game,350,0) //350 might be a little high
{
}

void Keyboard::HandleEvent()
{
	for(int id = 0; id < 350; id++)
	{
			(*buttons)[id].prevState = (*buttons)[id].state;
			(*buttons)[id].state= (glfwGetKey(game->gameWindow->window, id) == GLFW_PRESS);
		
	}
}

Button Keyboard::GetKey(int key)
{
	switch(key)
	{
		case '\n':
			return GetButton(int('\r'));
		case '~':
			return GetButton(int('`')) && (GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '`':
			return GetButton(int('`')) && !(GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '+':
			return GetButton(int('=')) && (GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '=':
			return GetButton(int('=')) && !(GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '!':
			return GetButton(int('1')) && (GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '1':
			return GetButton(int('1')) && !(GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '@':
			return GetButton(int('2')) && (GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '2':
			return GetButton(int('2')) && !(GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '#':
			return GetButton(int('3')) && (GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '3':
			return GetButton(int('3')) && !(GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '$':
			return GetButton(int('4')) && (GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '4':
			return GetButton(int('4')) && !(GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '%':
			return GetButton(int('5')) && (GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '5':
			return GetButton(int('5')) && !(GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '^':
			return GetButton(int('6')) && (GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '6':
			return GetButton(int('6')) && !(GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '&':
			return GetButton(int('7')) && (GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '7':
			return GetButton(int('7')) && !(GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '*':
			return GetButton(int('8')) && (GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '8':
			return GetButton(int('8')) && !(GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '(':
			return GetButton(int('9')) && (GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '9':
			return GetButton(int('9')) && !(GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case ')':
			return GetButton(int('0')) && (GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '0':
			return GetButton(int('0')) && !(GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '|':
			return GetButton(int('\\')) && (GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		case '\\':
			return GetButton(int('\\')) && !(GetButton(Keys::KEY_LEFT_SHIFT) || GetButton(Keys::KEY_RIGHT_SHIFT));
		default:
			return GetButton(int(key));
	}
}
