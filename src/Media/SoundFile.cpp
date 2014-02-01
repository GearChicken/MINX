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

using namespace MINX;
using namespace MINX::Media;

SoundFile::SoundFile(char* fileLocation, Game* gameHandle)
{
	libVLCMediaObject = libvlc_media_new_path(gameHandle->libVLCInstance, fileLocation);

	libvlc_media_player_set_media(gameHandle->libVLCMediaPlayer, libVLCMediaObject);

	volume = 1.0;
	
	this->gameHandle = gameHandle;
}

SoundFile::~SoundFile()
{
	Stop();

	libvlc_media_player_set_media(gameHandle->libVLCMediaPlayer, NULL);
	libvlc_media_release(libVLCMediaObject);
	//ga_sound_release(gorillaSoundFile);
}
void SoundFile::Play()
{
	libvlc_media_player_play(gameHandle->libVLCMediaPlayer);
}

void SoundFile::Pause()
{
	libvlc_media_player_pause(gameHandle->libVLCMediaPlayer);
}

void SoundFile::Stop()
{
	libvlc_media_player_stop(gameHandle->libVLCMediaPlayer);
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