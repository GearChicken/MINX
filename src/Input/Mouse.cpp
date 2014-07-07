
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
