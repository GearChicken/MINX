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
#include "Player.h"

using namespace MINX_GEMGAME;

using namespace MINX;

MINX_GEMGAME::Player::Player(int X, int Y, Texture2D* texture):rect(new Rectangle(X,Y,16,16)) // Instantiate a new Player with a width and height equal to 16.
{
	color = new Color(255,255,255,0); // make the player whitee
	velocity = new Vector2(0,0); // make the player's velocity zero
	loc = new Vector2(0,0); // set the player at the top left corner of the screen
	speedMultiplier=5; // set the players speed to 5
	this->texture=texture;
}
void Player::Update(GameTime * gametime, Keyboard* keyboard, vector<Gem*> * gems, int * score)
{
	velocity->X =0;  // reset the players velocity
	velocity->Y =0; 
	if(keyboard->getButton(87).state)
	{
		velocity->Y +=-1;
	}
	if(keyboard->getButton(83).state)
	{
		velocity->Y +=1;
	}
	if(keyboard->getButton(65).state)
	{
		velocity->X +=-1;
	}
	if(keyboard->getButton(68).state)
	{
		velocity->X +=1;
	}

	*velocity = velocity->normalize();
	*velocity = *velocity * speedMultiplier; // limit the players velocity to have a magnitude of speedMultiplier
	loc->X += velocity->X; // update the players location
	loc->Y += velocity->Y;
	
	//SCREEN WRAPPING

	if(loc->X < 192) 
	{
		loc->X = 816;
	}
	if(loc->X > 816)
	{
		loc->X = 192;
	}
	if(loc->Y < 144)
	{
		loc->Y = 608;
	}
	if(loc->Y > 608)
	{
		loc->Y = 144;
	}

	//update player location
	rect->X = loc->X;
	rect->Y = loc->Y;
	int i = 0;
#ifdef _WIN32
	for(vector<Gem*>::iterator it = gems->begin(); it < gems->end(); ++it)
	{
		// Gem * gem = *it;
		if(rect->intersects((*it)->rect))
		{
			//gems->at(0) = NULL;
			gems->erase(gems->begin() + i);
			(*score)++;
			i--;
		}
		i++;
	}
#else
	for(Gem* gem : *gems)
	{
		if(rect->intersects(gem->rect))
		{
			//gems->at(0) = NULL;
			gems->erase(gems->begin() + i);
			(*score)++;
			i--;
		}
		i++;
	}
#endif
}
void Player::Draw(GameTime * gametime)
{
	//Put stuff here to draw your game each frame.
	texture->Draw(rect->X,rect->Y,1.0f,1.0f,0.0f,new Color(255,255,255));
}
