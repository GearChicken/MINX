/*
# MINX

Copyright (c) 2013-2014 Liam Middlebrook, Benjamin Pylko

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

> 1\. The origin of this software must not be misrepresented; you must not
> claim that you wrote the original software. If you use this software
> in a product, an acknowledgment in the product documentation would be
> appreciated but is not required
>
> 2\. Altered source versions must be plainly marked as such, and must not be
> misrepresented as being the original software
>
> 3\. This notice may not be removed or altered from any source
> distribution
>
 */

#ifndef MINX_SOUNDPLAYLIST_HPP_
#define MINX_SOUNDPLAYLIST_HPP_

#include "../API.hpp"

#include "SoundFile.hpp"
#include <vector>

namespace MINX
{
	namespace Media
	{
		/** Holds and plays a collection of sounds
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
