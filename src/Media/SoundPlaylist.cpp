/*
# MINX

Copyright (c) 2013-2014 Liam Middlebrook, Benjamin Pylko

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

> 1\. The origin of this software must not be misrepresented; you must not
> claim that you wrote the original software. If you use this software
> in a product, an acknowledgment in the product documentation would be
> appreciated but is not required.
>
> 2\. Altered source versions must be plainly marked as such, and must not be
> misrepresented as being the original software.
>
> 3\. This notice may not be removed or altered from any source
> distribution.
>
 */
 
#include "SoundPlaylist.hpp"

using namespace MINX;
using namespace MINX::Media;

SoundPlaylist::SoundPlaylist()
{
	songFiles = std::vector<char*>();
	doShuffle = false;
	songIndex = 0;
}

void SoundPlaylist::AddSound(char* fileLocation)
{
	songFiles.push_back(fileLocation);
}

void SoundPlaylist::Play()
{
	if(currentSong && !songDeleted)
	{
		currentSong->Stop();
 		delete currentSong;
		currentSong = NULL;
		songDeleted = true;
	}

	if(doShuffle)
	{
		songIndex = rand() % songFiles.size();
	}

	currentSong = new SoundFile(songFiles[songIndex]);
	songDeleted = false;
	currentSong->Play();
	++songIndex;
	if(songIndex >= songFiles.size())
	{
		songIndex = 0;
	}
}

void SoundPlaylist::Stop()
{
	if(currentSong && !songDeleted)
	{
		currentSong->Stop();
		delete currentSong;
		songDeleted = true;
		songIndex = 0;
	}
}

