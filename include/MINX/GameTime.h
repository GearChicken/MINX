/*
    MINX - A C++ Graphics and Input Wrapper Library
    Copyright (C) 2013-2014  MINX Team

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

#ifndef GAMETIME_H_
#define GAMETIME_H_

#include "API.h"

#include <thread>
#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
			inline void LimitFPS(unsigned int desiredFPS){std::this_thread::sleep_for(std::chrono::milliseconds((long)(1000/desiredFPS-(GetDeltaTimeSeconds()))));}
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
#include "Game.h"
#endif
