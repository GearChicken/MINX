
/*
# MINX

Copyright (c) 2013-2014 Liam Middlebrook, Benjamin Pylko

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

> 1\. The origin of this software must not be misrepresented; you must not
> claim that you wrote the original software. If you use this software
> in a product, an acknowledgment in the product documentation would be
> appreciated but is not required.
>
> 2\. Altered source versions must be plainly marked as such, and must not be
> misrepresented as being the original software.
>
> 3\. This notice may not be removed or altered from any source
> distribution.
>
        */
#include "GamePad.h"

using namespace MINX;
using namespace MINX::Input;

bool GamePad::IsConnected()
{
	return isConnected = glfwJoystickPresent(deviceIndex) == GL_TRUE;
}

GamePad::GamePad(unsigned int deviceIndex, Game* game):IGenericHID(game, 16, 16)
{
	this->deviceIndex = deviceIndex;
	IsConnected();
}

GamePad::GamePad(unsigned int deviceIndex, Game* game, unsigned int gamePadType):IGenericHID(game, 16, 16)
{
	this->deviceIndex = deviceIndex;
	this->gamePadType = gamePadType;
	IsConnected();
}

void GamePad::Update(GameTime * gametime)
{
	
	if(IsConnected())
	{
		int numButtons = 0;
		const unsigned char * buttonValues = glfwGetJoystickButtons(deviceIndex,&numButtons);
	
		int numAxes = 0;
		const float * axisValues = glfwGetJoystickAxes(deviceIndex,&numAxes);
		
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
	if(IsConnected())
	{
		return IGenericHID::GetButton(buttonID);
	}
	return Button();
}

Axis GamePad::GetAxis(unsigned int axisID)
{
	if(IsConnected())
	{
		return IGenericHID::GetAxis(axisID);
	}
	return Axis();
}

const char * GamePad::GetName()
{
	if(IsConnected())
	{
		return glfwGetJoystickName(deviceIndex);
	}
	return "DEVICE DISCONNECTED";
}
