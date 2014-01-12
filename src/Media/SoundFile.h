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
		/** A class to hold a single sound file
		*/
		class SoundFile
		{
		public:
			/* Load a sound file from the hard disk
			*	@param fileLocation The path of the file to load.
			*	@param gameHandle A pointer the the game that the sound will be played in.
			*	@param soundType The sound format to load
			*/
			SoundFile(char* fileLocation, Game* gameHandle, char* soundType);
			
			/* Destroy the sound file safely
			*/
			~SoundFile();
			
			/* Start playback of the sound file
			*/
			void Play();
			
			/* Pause playback of the sound file
			*/
			void Pause();
			
			/* Stop playback of the sound file
			*/
			void Stop();
			
			/* Set the Playback volume of the sound file
			*	@param volume A double value from 0.0 to 1.0 for the GAIN or volume of the sound file
			*/
			void SetVolume(double volume);
		private:

			/* The volume of the sound file
			*/
			double volume;
			
			/* The Gorilla Audio sound object that will contain the loaded file data
			*/
			ga_Sound* gorillaSoundFile;
			
			/* The Gorilla Audio handle that will be used to play the loaded sound file
			*/
			ga_Handle* gorillaSoundHandle;
		};
	}
}


#endif
