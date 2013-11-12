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
#include "RandomMonster.h"
using namespace MINX_monsters;
RandomMonster::RandomMonster(Vector2* position, Graphics::Texture2D* texture) : Monster(position, texture, new Graphics::Color(255.0f,0.0f,0.0f))
{
	velocity->X = 1;
	velocity->Y = 1;
	srand(time(0));
}
void RandomMonster::Update(GameTime* gameTime, Input::Keyboard* keyboard)
{
	position->X += velocity->X;
	position->Y += velocity->Y;
	velocity->X = rand()%3 -1;
	velocity->Y = rand()%3 -1;
	if (position->X + velocity->X < 0 || position->X + velocity->X > Graphics::GameWindow::width - texture->GetWidth())
	{
		velocity->X *= -1;
	}
	if (position->Y + velocity->Y < 0 || position->Y + velocity->Y > Graphics::GameWindow::height - texture->GetHeight())
	{
		velocity->Y *= -1;
	}
}