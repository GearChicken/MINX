/*
    MINX - A C++ Graphics and Input Wrapper Library
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

#ifndef SOUND_FILE_H_
#define SOUND_FILE_H_

#include "../Game.h"

namespace MINX
{
	namespace Media
	{
		class SoundFile
		{
		public:
			SoundFile(char* fileLocation, Game* gameHandle, char* soundType);
			~SoundFile();
			void Play();
			void Pause();
			void Stop();
			void SetVolume(double volume);
		private:
			double volume;
			ga_Sound* gorillaSoundFile;
			ga_Handle* gorillaSoundHandle;
		};
	}
}


#endif
