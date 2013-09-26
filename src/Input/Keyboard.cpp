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
using namespace MINX;
using namespace std;

Keyboard::Keyboard (Game * game) : IGenericHID(game,350,0) //350 might be a little high
{
}

void Keyboard::handleEvent()
{
	for(int id = 0; id < 350; id++)
	{
			(*buttons)[id].prevState = (*buttons)[id].state;
			(*buttons)[id].state= glfwGetKey(id) == GLFW_PRESS;
		
	}
}

Button Keyboard::getKey(char key)
{
	switch(key)
	{
		case '\n':
			return getButton(int('\r'));
		case '~':
			return getButton(int('`')) && (getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '`':
			return getButton(int('`')) && !(getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '+':
			return getButton(int('=')) && (getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '=':
			return getButton(int('=')) && !(getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '!':
			return getButton(int('1')) && (getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '1':
			return getButton(int('1')) && !(getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '@':
			return getButton(int('2')) && (getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '2':
			return getButton(int('2')) && !(getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '#':
			return getButton(int('3')) && (getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '3':
			return getButton(int('3')) && !(getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '$':
			return getButton(int('4')) && (getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '4':
			return getButton(int('4')) && !(getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '%':
			return getButton(int('5')) && (getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '5':
			return getButton(int('5')) && !(getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '^':
			return getButton(int('6')) && (getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '6':
			return getButton(int('6')) && !(getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '&':
			return getButton(int('7')) && (getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '7':
			return getButton(int('7')) && !(getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '*':
			return getButton(int('8')) && (getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '8':
			return getButton(int('8')) && !(getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '(':
			return getButton(int('9')) && (getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '9':
			return getButton(int('9')) && !(getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case ')':
			return getButton(int('0')) && (getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '0':
			return getButton(int('0')) && !(getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '|':
			return getButton(int('\\')) && (getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		case '\\':
			return getButton(int('\\')) && !(getButton(GLFW_KEY_RIGHT_SHIFT) || getButton(GLFW_KEY_LEFT_SHIFT));
		default:
			return getButton(int(key));
	}
}
