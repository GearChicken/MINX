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
	
#include "Mouse.h"

using namespace MINX::Input;

Mouse::Mouse(Game * game) : IGenericHID(game,0xFFF,4)
{

}

void Mouse::handleEvent(SDL_Event * evt, GameTime * gameTime)
{
	if(evt->type == SDL_MOUSEBUTTONDOWN || evt->type == SDL_MOUSEBUTTONUP)
	{
		int id = evt->button.which*0x100 + evt->button.button; //In case it's not clear, which is which input device. so button 1 device 1 would be 0x1 (DEC 1). A button on a specific device can be retrieved by getButton(deviceID*256 + buttonID)
		if(id > 0 && id < 0xFFF)
		{
			(*buttons)[id].prevState = (*buttons)[id].state;
			(*buttons)[id].state= evt->type == SDL_MOUSEBUTTONDOWN;
		}
	}
	(*axes)[2].prevVal = (*axes)[2].val;
	(*axes)[3].prevVal = (*axes)[3].val;
	if(evt->type == SDL_MOUSEMOTION)
	{
		(*axes)[0].prevVal = (*axes)[0].val;
		(*axes)[1].prevVal = (*axes)[1].val;
		(*axes)[0].val = evt->motion.x;
		(*axes)[1].val = evt->motion.y;
		(*axes)[2].val = evt->motion.xrel;
		(*axes)[3].val = evt->motion.yrel;
	} else
	{
		(*axes)[2].val = 0;
		(*axes)[3].val = 0;
	}
}
