/*
	Copyright (C) 2014  MINX Team

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

#include "SoundFile.h"

using namespace MINX;
using namespace MINX::Sound;

SoundFile::SoundFile(char* fileLocation, Game* gameHandle, char* soundType)
{
	gorillaSoundFile = gau_load_sound_file(fileLocation, soundType);
	
	gorillaSoundHandle = gau_create_handle_sound(gameHandle->gorillaMixer, gorillaSoundFile, 0, 0, 0);

	volume = 1.0;
}
SoundFile::~SoundFile()
{
	ga_handle_destroy(gorillaSoundHandle);
}
void SoundFile::Play()
{
	ga_handle_setParamf(gorillaSoundHandle, GA_HANDLE_PARAM_GAIN, volume);
	ga_handle_play(gorillaSoundHandle);
}

void SoundFile::Pause()
{
	ga_handle_stop(gorillaSoundHandle);
}

void SoundFile::Stop()
{
	ga_handle_stop(gorillaSoundHandle);
	ga_handle_seek(gorillaSoundHandle, 0);
}
void SoundFile::SetVolume(double volume)
{
	if(volume > 1.0)
	{
		this->volume = 1.0;
		return;
	}
	if(volume < 0.0)
	{
		this->volume = 0.0;
		return;
	}
	this->volume = volume;
}