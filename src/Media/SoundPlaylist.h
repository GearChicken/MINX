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

#ifndef SOUND_PLAYLIST_H_
#define SOUND_PLAYLIST_H_

#include "SoundFile.h"

namespace MINX
{
	namespace Media
	{
		class SoundPlaylist
		{
		public:
			SoundPlaylist(Game* gameHandle);
			void AddSound(char* fileLocation);
			void Play();
			void Stop();
			inline void Shuffle(bool doShuffle) { this->doShuffle = doShuffle; };
		private:
			bool doShuffle;
			Game* gameHandle;
			vector<char*> songFiles;
			SoundFile* currentSong;
			int songIndex;
			bool songDeleted;
		};
	}

}
#endif