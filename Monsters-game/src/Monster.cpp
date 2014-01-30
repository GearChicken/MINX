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
#include "Monster.h"
#include <iostream>
using namespace MINX_monsters;
Monster::Monster(Vector2* position, Graphics::Texture2D* texture, Graphics::Color* color, Game* game)
{
	this->usingGamePad=false;
	this->position = position;
	this->color = color;
	this->velocity = new Vector2(0,0);
	this->texture = texture;
	if(GamePad::CheckIfDeviceValid(0))
	{
		this->usingGamePad=true;
		this->gamePad = new Input::GamePad(0,game);
	}
	else
	{
		
		this->gamePad=NULL;
	}
}
Monster::Monster(Vector2* position, Graphics::Texture2D* texture, Graphics::Color* color)
{
	this->usingGamePad=false;
	this->position = position;
	this->color = color;
	this->velocity = new Vector2(0,0);
	this->texture = texture;
}
void Monster::Update(GameTime* gameTime, Input::Keyboard* keyboard)
{
	/*
	std::cout << "Axis 0: " << gamePad->GetAxis(0).val << std::endl;
	std::cout << "Axis 1: " << gamePad->GetAxis(1).val << std::endl;
	std::cout << "Axis 2: " << gamePad->GetAxis(2).val << std::endl;
	std::cout << "Axis 3: " << gamePad->GetAxis(3).val << std::endl;
	*/
	if(keyboard->GetKey(Input::Keys::KEY_A).state || (usingGamePad && gamePad->GetButton(2).state) || (usingGamePad && gamePad->GetAxis(0).val < -0.12))
	{
		position->X--;
		if(position->X < 0)
		{
			position->X = 0;
		}
	}
	if(keyboard->GetKey(Input::Keys::KEY_D).state || (usingGamePad && gamePad->GetButton(1).state) || (usingGamePad && gamePad->GetAxis(0).val > 0.12))
	{
		position->X++;
		if(position->X >= Graphics::GameWindow::GetWidth() - (int)texture->GetWidth())
		{
			position->X = Graphics::GameWindow::GetWidth() - (int)texture->GetWidth();
		}
	}
	if(keyboard->GetKey(Input::Keys::KEY_W).state || (usingGamePad && gamePad->GetButton(3).state) || (usingGamePad && gamePad->GetAxis(1).val < -0.12))
	{
		position->Y--;
		if(position->Y < 0)
		{
			position->Y = 0;
		}
	}
	if(keyboard->GetKey(Input::Keys::KEY_S).state || (usingGamePad && gamePad->GetButton(0).state) || (usingGamePad && gamePad->GetAxis(1).val > 0.12))
	{
		position->Y++;
		if(position->Y >= Graphics::GameWindow::GetHeight() - (int)texture->GetHeight())
		{
			position->Y = Graphics::GameWindow::GetHeight() - (int)texture->GetHeight();
		}
	}
	//*/
}
void Monster::Draw(TextureBatch* texBatch)
{
	texBatch->Draw(texture, position->X, position->Y, 1.0f, 1.0f, 0.0f, *color);
}