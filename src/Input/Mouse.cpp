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
#include "Mouse.h"
using namespace MINX;
using namespace MINX::Input;
Mouse::Mouse(Game* game) : IGenericHID(game, 8, 8)
{

}
void Mouse::HandleEvent(GameTime* gameTime)
{
	for(int id = 0; id < 8; id++)
	{
		(*buttons)[id].prevState = (*buttons)[id].state;
		(*buttons)[id].state = (glfwGetMouseButton(game->gameWindow->window, id) == GLFW_PRESS);
	}
	(*axes)[0].val = (*axes)[0].prevVal;
	(*axes)[1].val = (*axes)[1].prevVal;
	glfwGetCursorPos(game->gameWindow->window,&((*axes)[0].val),&((*axes)[1].val));
}
Vector2 Mouse::GetPosition()
{
	return Vector2((*axes)[0].val, (*axes)[1].val);
}
Button Mouse::GetMouseButton(int buttonID)
{
	return GetButton(buttonID);
}
