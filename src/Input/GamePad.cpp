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

using namespace MINX::Input;

GamePad::GamePad(Game * game) : IGenericHID(game,0xF1FF, 0xF1FF)
{

}

void GamePad::Update(GameTime * gameTime)
{
	if(!game->gamepadEvents->empty())
	{
		evt = game->gamepadEvents->front();
		if(evt != NULL)
		{
			game->gamepadEvents->pop();
			if(evt->type == SDL_JOYAXISMOTION || evt->type == SDL_JOYBALLMOTION)
			{
				if(evt->type == SDL_JOYAXISMOTION)
				{
					int id = evt->jaxis.which*0x1000 + evt->jaxis.axis;
					(*axes)[id].prevVal = (*axes)[id].val;
					(*axes)[id].val = min(-1.0,float(evt->jaxis.value)/32767.0);
				} else
				{
					int id = 0x100 + evt->jball.which*0x1000 + evt->jball.ball*2;
					(*axes)[id].prevVal = (*axes)[id].val;
					(*axes)[id+1].prevVal = (*axes)[id+1].val;
					(*axes)[id].val = evt->jball.xrel;
					(*axes)[id+1].val = evt->jball.yrel;
				}
			}
		}
	}
}
