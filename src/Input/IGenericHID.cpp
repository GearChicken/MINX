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
#include "IGenericHID.h"

using namespace MINX::Input;
using namespace MINX;

IGenericHID::IGenericHID(Game * game, unsigned int buttonVectorSize, unsigned int axisVectorSize) : GameComponent(game)
{
	Button b;
	b.prevState = 0;
	b.state = 0;
	buttons = new vector<Button>(buttonVectorSize,b);
	Axis a;
	a.prevVal = 0;
	a.val = 0;
	axes = new vector<Axis>(axisVectorSize,a);
}

Button IGenericHID::GetButton(unsigned int id)
{
	return (* buttons)[id];
}

Axis IGenericHID::GetAxis(unsigned int id)
{
	return (* axes)[id];
}
