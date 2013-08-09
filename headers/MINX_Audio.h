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
#ifndef MINX_AUDIO_H_
#define MINX_AUDIO_H_
#include <string>
#include <SDL/SDL_mixer.h>
namespace MINX
{
	namespace Audio
	{
		class AudioClip
		{
			public:
				AudioClip(std::string filename);
				AudioClip(std::string filename, bool autoplay, bool loop);
				void play();
				void pause();
				void stop();
				void setVolume(float volume);
				void setPosition(Sint16 angle, Uint8 distance);
				void disable3DAudio();
				~AudioClip();
				int mix_channel;
				static bool mix_initialized;
				static int allocated_channels;
				static int used_channels;
				Mix_Chunk * audiodata;
		};
		bool AudioClip::mix_initialized=false;
		int AudioClip::allocated_channels=0;
		int AudioClip::used_channels=0;
	}
}
#endif
