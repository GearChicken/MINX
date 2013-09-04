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
#ifndef AUDIOCLIP_H_
#define AUDIOCLIP_H_
#include <string>
#include <iostream>
#ifdef _WIN32
#include <SDL_mixer.h>
#else
#include "SDL/SDL_mixer.h"
#endif
using namespace std;
namespace MINX
{
	namespace Audio
	{
		/** Represents a segment of audio to be played
		 */
		class AudioClip
		{
			public:
				/** Constructs a non-autoplaying, non-looping AudioClip
				 * @param filename the name of the file to load
				 */
			AudioClip(string filename);
				/** Contsructs an AudioClip
				 * @param filename the name of the file to load
				 * @param autoplay whether or not to automatically play the clip
				 * @param loop whether or not to loop the clip
				 */
			AudioClip(string filename, bool autoplay, bool loop);
				/** Initialize the Audio Clip (This function is needed by the _WIN32 platform).
				*/
			void init(std::string filename, bool autoplay, bool loop);
				/** If the clip is paused, unpause it, if it's stopped, start it, otherwise do nothing
				 */
			void play();
				/** Pause the clip if it is playing
				 */
			void pause();
				/** Stop the clip if it is playing or paused
				 */
			void stop();
				/** Set the volume of the clip.
				 * @param volume the volume to set the clip to. values less than 0 will be interpreted as 0, and values greater than 1 will be interpreted as 1
				 */
			void setVolume(float volume);
				/** Set the origin of this sound in relation to the listener
				 * @param angle the angle in degrees of the location of the sound
				 * @param distance the distance of the sound from the listener
				 */
			void setPosition(Sint16 angle, Uint8 distance);
				/** Disables the use of 3D audio. Default is disabled, is enabled when setPosition is called with either value non-zero
				 */
			void disable3DAudio();
				/** Enables headphone mode
				 * Only enables it for this clip
				 * Squishes the angle of the clip down to between -45 degrees and 45 degrees in order to blend the left and right outputs together a little bit.
				 */
			void headPhoneMode();
				/** Destructs this AudioClip
				 */
			~AudioClip();
				/** The channel to play this AudioClip on
				 * You probably don't want to mess with this
				 */
				int mix_channel;
				/** The volume of the AudioClip
				*/
				float chunkVolume;
				float chunkDistance;
				float chunkAngle;
				/** Whether or not Mix has been initialized
				 * You REALLY don't want to mess with this unless you absolutely know what you're doing and have called Mix_CloseAudio()
				 */
				static bool mix_initialized;
				/** How many channels Mix has allocated
				 * There is no reason to mess with this unless you know what you're doing and you want to trick mix into deleting some channels or adding some
				 */
				static int allocated_channels;
				/** How many channels are in use
				 * There probably is no reason to mess with this
				 */
				static int used_channels;
				/** A pointer to the raw WAV data stored in a Mix_Chunk
				 */
				Mix_Chunk * audiodata;
		};
	}
}
#endif
