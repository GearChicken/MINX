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

#include "SoundFile.h"
#include "../MathHelper.h"

using namespace MINX;
using namespace MINX::Media;

SoundFile::SoundFile(char* fileLocation)
{
	soundBuffer.loadFromFile(string(fileLocation));
	sound.setBuffer(this->soundBuffer);
}

SoundFile::~SoundFile()
{
	sound.~Sound();
	soundBuffer.~SoundBuffer();
}
void SoundFile::Play()
{
	this->sound.play();
}

void SoundFile::Pause()
{
	this->sound.pause();
}

void SoundFile::Stop()
{
	this->sound.stop();
}
void SoundFile::SetVolume(double volume)
{
	this->sound.setVolume(volume);
}
