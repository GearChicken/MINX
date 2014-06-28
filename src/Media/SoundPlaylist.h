/*
    MINX - A C++ Graphics and Input Wrapper Library
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

#ifndef SOUND_PLAYLIST_H_
#define SOUND_PLAYLIST_H_

#include "../API.h"

#include "SoundFile.h"
#include <vector>

namespace MINX
{
	namespace Media
	{
		/** Holds and plays a collection of sounds.
		 */
		class MINX_API SoundPlaylist
		{
		public:
			/** Constructs a SoundPlaylist with a handle to a game
			 */
			SoundPlaylist();
			
			/** Adds a sound to the playlist from a file
			 */
			void AddSound(char* fileLocation);
			
			/** Plays from the current location in the playlist
			 */
			void Play();
			
			/** Stops all songs in the playlist from playing
			 */
			void Stop();
			
			/** Enables/disables shuffling
			 */
			inline void Shuffle(bool doShuffle) { this->doShuffle = doShuffle; };
			
		private:
			/** Whether or not to shuffle the order
			 */
			bool doShuffle;

			/** The list of filenames in the playlist
			 */
			std::vector<char*> songFiles;

			/** The current song playing
			 */
			SoundFile* currentSong;
			/** The index in the filename vector of the current song
			 */
			unsigned int songIndex;
			/** Whether or not the current song has been deleted. If it has, a new one is constructed
			 */
			bool songDeleted;
		};
	}

}
#endif
