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
#include "AudioClip.h"

using namespace MINX;

AudioClip::AudioClip(string filename, bool autoplay)
{
	if(SDL_LoadWAV(filename.c_str(), &spec, &buffer, &length) == NULL)
	{
		cerr << "Error loading file" << endl;
	}
	SDL_PauseAudio(!autoplay);
}
//these should probably not be here, because they apply to all audio
void AudioClip::play()
{
	SDL_PauseAudio(0);
}

void AudioClip::pause()
{
	SDL_PauseAudio(1);
}
