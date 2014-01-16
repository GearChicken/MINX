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

Keyboard::Keyboard (Game * game) : IGenericHID(game,350,0) //350 might be a little high
{

}

void Keyboard::Update(GameTime * gametime)
{
	for(unsigned int id = 0; id < 350; id++)
	{
			(*buttons)[id].prevState = (*buttons)[id].state;
			(*buttons)[id].state= (glfwGetKey(game->gameWindow->window, id) == GLFW_PRESS);
		
	}
}

Button Keyboard::GetKey(unsigned int key)
{
	return GetButton(key);
}
