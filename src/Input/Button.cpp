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

#include "Button.h"

using namespace MINX::Input;

void Button::SetState(bool state)
{
	prevState = this->state;
	this->state = state;
}

bool Button::GetState()
{
	return state;
}

bool Button::GetPrevState()
{
	return prevState;
}

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
