/*
Copyright (C) 2014  MINX Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "Song.h"
#include "../MathHelper.h"
#include <string>

using namespace MINX;
using namespace MINX::Media;

Song::Song(char* fileLocation)
{
	song.openFromFile(std::string(fileLocation));
}

Song::~Song()
{
	song.~Music();
}
void Song::Play()
{
	this->song.play();
}

void Song::Pause()
{
	this->song.pause();
}

void Song::Stop()
{
	this->song.stop();
}
void Song::SetVolume(double volume)
{
	this->song.setVolume(volume);
}
void Song::SetLoop(bool loop)
{
	this->song.setLoop(loop);
}
