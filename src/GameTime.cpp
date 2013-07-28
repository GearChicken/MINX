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

#include "GameTime.h"
using namespace MINX;

GameTime::GameTime(long millisecondsSinceStart, long timeSinceLastUpdate, bool runningSlowly)
{
	startOffset=millisecondsSinceStart;
	deltaTime=timeSinceLastUpdate;
	isRunningSlowly=runningSlowly;
}
GameTime::GameTime(long millisecondsSinceStart, long timeSinceLastUpdate)
{
	GameTime(millisecondsSinceStart, timeSinceLastUpdate, false);
}
GameTime::GameTime()
{
	GameTime(0,0,false);
}

long GameTime::getElapsedMillis()
{
	return time;
}

long GameTime::getDeltaTime()
{
	return deltaTime;
}

bool GameTime::getIsRunningSlowly()
{
	return isRunningSlowly;
}
