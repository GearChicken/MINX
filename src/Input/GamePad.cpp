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
#include "GamePad.h"
using namespace MINX;
using namespace MINX::Input;
bool GamePad::CheckIfDeviceValid(int deviceIndex)
{
	Gamepad_detectDevices();
	return deviceIndex < Gamepad_numDevices();
}
GamePad::GamePad(int deviceIndex, Game* game):IGenericHID(game, 16, 16)
{
	isConnected=true;
	this->gamePad = Gamepad_deviceAtIndex(deviceIndex);
	Gamepad_deviceRemoveFunc(GamePad::GamePadRemoved, (void*)this);
	Gamepad_deviceAttachFunc(GamePad::GamePadAttached, (void*)this);
}
GamePad::GamePad(int deviceIndex, Game* game, int gamePadType):IGenericHID(game, 16, 16)
{
	isConnected=true;
	this->gamePad = Gamepad_deviceAtIndex(deviceIndex);
	this->gamePadType = gamePadType;
	Gamepad_deviceRemoveFunc(GamePad::GamePadRemoved, (void*)this);
	Gamepad_deviceAttachFunc(GamePad::GamePadAttached, (void*)this);
}
void GamePad::handleEvent()
{
	Gamepad_processEvents();

	if(isConnected)
	{
		for(int id = 0; id < gamePad->numButtons; id++)
		{
			(*buttons)[id].prevState = (*buttons)[id].state;
			(*buttons)[id].state= gamePad->buttonStates[id*4];
		}
		for(int id = 0; id < gamePad->numAxes; id++)
		{
			(*axes)[id].prevVal = (*axes)[id].val;
			(*axes)[id].val= gamePad->axisStates[id];
		}
	}
}
Button GamePad::getButton(int buttonID)
{
	if(isConnected)
	{
		return IGenericHID::getButton(buttonID);
	}
	return Button();
}
Axis GamePad::getAxis(int axisID)
{
	if(isConnected)
	{
		return IGenericHID::getAxis(axisID);
	}
	return Axis();
}
void GamePad::GamePadRemoved(struct Gamepad_device* device, void* context)
{
	((GamePad*)context)->isConnected = (((GamePad*)context)->gamePad != device);
}
void GamePad::GamePadAttached(struct Gamepad_device* device, void* context)
{
	((GamePad*)context)->isConnected = (((GamePad*)context)->gamePad == device);
}