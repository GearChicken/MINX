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

#include "../API.hpp"

#include "SFML/Audio.hpp"
#include <string>

#ifndef MINX_SOUNDFILE_HPP_
#define MINX_SOUNDFILE_HPP_

namespace MINX
{
	namespace Media
	{
		/** A class to hold a single sound file
		 */
		class MINX_API SoundFile
		{
		public:
			/** Load a sound file from the hard disk
			 *	@param fileLocation The path of the file to load.
			 */
			SoundFile(char* fileLocation);

			/** Destroy the sound file safely
			 */
			~SoundFile();

			/** unload the sound file safely
			 */
			void Unload();

			/** Start playback of the sound file
			 */
			void Play();

			/** Pause playback of the sound file
			 */
			void Pause();

			/** Stop playback of the sound file
			 */
			void Stop();

			/** Set the Playback volume of the sound file
			 *	@param volume A double value from 0.0 to 100.0 for the GAIN or volume of the sound file
			 */
			void SetVolume(float volume);

		private:

			/** The volume of the sound file
			*/
			double volume;

			/** The internal sfml sound buffer
			 */
			sf::SoundBuffer soundBuffer;

			/** The internal sfml sound object
			 */
			sf::Sound sound;
		};
	}
}


#endif
