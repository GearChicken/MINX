/*
    MINX - A C++ Graphics and Input Wrapper Library
    Copyright (C) 2013-2014  MINX Team

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

#include "GameTime.h"
#include <GL/glew.h>
#include <GL/glfw3.h>
using namespace MINX;

GameTime::GameTime()
{
}

/*void GameTime::limitFPS(int desiredFPS)
{
	
	int NextTick = totalTimeMillis + (1000/desiredFPS);
	if(NextTick > glfwGetTime())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000/desiredFPS-deltaTimeMillis));
	}
}//*/
void GameTime::update()
{
	totalTimeMillis = glfwGetTime()*1000.0;
	deltaTime = totalTimeMillis - lastUpdate;
	lastUpdate = totalTimeMillis;
	deltaTime = deltaTime > 0 ? deltaTime : std::numeric_limits<double>::epsilon();
	lastUpdate = totalTimeMillis;
	totalTimeMillis = glfwGetTime();
	deltaTime = totalTimeMillis - lastUpdate;
	deltaTime = deltaTime > 0 ? deltaTime : std::numeric_limits<double>::epsilon();
}
long GameTime::getElapsedMillis()
{
	return totalTimeMillis;
}

double GameTime::getDeltaTimeSeconds()
{
	return deltaTime;
}

long GameTime::getDeltaTimeMillis()
{
	return deltaTime*1000;
}
