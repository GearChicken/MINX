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
#include "Mouse.h"
using namespace MINX;
using namespace MINX::Input;
Mouse::Mouse(Game* game) : IGenericHID(game, 8, 8)
{

}

void Mouse::Update(GameTime * gametime)
{
	for(unsigned int id = 0; id < 8; id++)
	{
		(*buttons)[id].UpdateState(glfwGetMouseButton(game->gameWindow->window, id) == GLFW_PRESS);
	}
	double posX = 0.0f;
	double posY = 0.0f;
	glfwGetCursorPos(game->gameWindow->window,&posX,&posY);
	(*axes)[0].UpdateValue(posX);
	(*axes)[1].UpdateValue(posY);
}

Vector2 Mouse::GetPosition()
{
	return Vector2((*axes)[0].GetValue(), (*axes)[1].GetValue());
}

Button Mouse::GetMouseButton(unsigned int buttonID)
{
	return GetButton(buttonID);
}
