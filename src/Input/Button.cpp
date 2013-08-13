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
#include "Button.h"

using namespace MINX::Input;

Button Button::operator&&(const Button& andWith)
{
	Button b;
	b.state = this->state && andWith.state;
	b.prevState = this->prevState && andWith.prevState;
	return b;
}

Button Button::operator||(const Button& orWith)
{
	Button b;
	b.state = this->state || orWith.state;
	b.prevState = this->prevState || orWith.prevState;
	return b;
}

Button Button::operator!()const
{
	Button b;
	b.state = !this->state;
	b.prevState = !this->prevState;
	return b;
}
