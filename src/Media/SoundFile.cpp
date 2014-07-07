
/*
# The zlib/libpng License

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

#include "SoundFile.h"
#include "../MathHelper.h"

using namespace MINX;
using namespace MINX::Media;

SoundFile::SoundFile(char* fileLocation)
{
	soundBuffer.loadFromFile(std::string(fileLocation));
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
