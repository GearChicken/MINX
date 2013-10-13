/*
MINX_Monsters - A C++ Game Based off the
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
#include "Bouncer.h"
using namespace MINX_monsters;
Bouncer::Bouncer(Vector2* position, Graphics::Texture2D* texture) : Monster(position, texture, new Graphics::Color(0.0f,255.0f,0.0f))
{
	velocity->X = 1;
	velocity->Y = 1;
}
void Bouncer::Update(GameTime* gameTime, Input::Keyboard* keyboard)
{
	position->X += velocity->X;
	position->Y += velocity->Y;
	
	if(position->X < 1 || position->X > Graphics::GameWindow::width - texture->width)
	{
		velocity->X *=-1;
	}
	if(position->Y < 1 || position->Y > Graphics::GameWindow::height - texture->height)
	{
		velocity->Y *=-1;
	}
}