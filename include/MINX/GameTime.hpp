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

#include "API.hpp"

#include <thread>
#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifndef MINX_GAMETIME_HPP_
#define MINX_GAMETIME_HPP_

namespace MINX
{
	class MINX_API Game;
	class MINX_API GameComponent;

	/** Contains a bunch of time related functions for use in the Game
	 */
	class MINX_API GameTime
	{
		public:
			/** @return the number of milliseconds since the start of the Game
			 */
			long GetElapsedMillis();

			/** @return the number of seconds since the start of the Game
			 */
			double GetElapsedSeconds();

			/** @return the number of seconds since the start of the Game as a float
			 */
			float GetElapsedSecondsF();

			/** @return the number of milliseconds since the last update()
			 */
			long GetDeltaTimeMillis();

			/** @return the number of seconds since the last update()
			 */
			double GetDeltaTimeSeconds();

			/** @return the number of seconds since the last update() as a float
			 */
			float GetDeltaTimeSecondsF();

			/** Limits the updates per second of the current thread by delaying
			 */
			inline void LimitFPS(unsigned int desiredFPS){std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long>(1000/desiredFPS-(GetDeltaTimeSeconds()))));}

		private:
			/** Constructs a GameTime
			 */
			GameTime();

			/** Updates the gametime
			 */
			void Update();

			/** The total time in seconds that has passed
			 */
			double totalTime;

			/** The time in seconds that has passed between the 2 previous Updates
			 */
			double deltaTime;

			/** The value of totalTime as of the previous Update
			 */
			double lastUpdate;

		friend class MINX::Game;
	};
}
#include "Game.hpp"
#endif
