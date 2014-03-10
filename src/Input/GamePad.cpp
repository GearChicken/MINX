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
#include "GamePad.h"

using namespace MINX;
using namespace MINX::Input;
GamePad::GamePad(unsigned int deviceIndex, Game* game):IGenericHID(game, 16, 16)
{
	this->deviceIndex = deviceIndex;
	isConnected = glfwJoystickPresent(deviceIndex) == GL_TRUE;
}

GamePad::GamePad(unsigned int deviceIndex, Game* game, unsigned int gamePadType):IGenericHID(game, 16, 16)
{
	this->deviceIndex = deviceIndex;
	this->gamePadType = gamePadType;
	isConnected = glfwJoystickPresent(deviceIndex) == GL_TRUE;
}

void GamePad::Update(GameTime * gametime)
{
	int numButtons = 0;
	const unsigned char * buttonValues = glfwGetJoystickButtons(deviceIndex,&numButtons);
	
	int numAxes = 0;
	const float * axisValues = glfwGetJoystickAxes(deviceIndex,&numAxes);
	
	if(isConnected)
	{
		for(int id = 0; id < numButtons; id++)
		{
			(*buttons)[id].prevState = (*buttons)[id].state;
			(*buttons)[id].state = buttonValues[id];
		}
		
		for(int id = 0; id < numAxes; id++)
		{
			(*axes)[id].prevVal = (*axes)[id].val;
			(*axes)[id].val = axisValues[id];
		}
	}
}

Button GamePad::GetButton(unsigned int buttonID)
{
	if(isConnected)
	{
		return IGenericHID::GetButton(buttonID);
	}
	return Button();
}

Axis GamePad::GetAxis(unsigned int axisID)
{
	if(isConnected)
	{
		return IGenericHID::GetAxis(axisID);
	}
	return Axis();
}

const char * GamePad::GetName()
{
	return glfwGetJoystickName(deviceIndex);
}
