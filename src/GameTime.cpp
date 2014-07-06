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

#include "GameTime.h"
using namespace MINX;

GameTime::GameTime()
{
	totalTime=0;
	deltaTime=0;
	lastUpdate=0;
}

void GameTime::Update()
{
	totalTime = glfwGetTime();
	deltaTime = totalTime - lastUpdate;
	lastUpdate = totalTime;
	deltaTime = deltaTime > 0 ? deltaTime : std::numeric_limits<double>::epsilon();
}
long GameTime::GetElapsedMillis()
{
	return totalTime * 1000;
}

double GameTime::GetElapsedSeconds()
{
	return totalTime;
}

float GameTime::GetElapsedSecondsF()
{
	return GetElapsedSeconds() > std::numeric_limits<float>::epsilon() ? GetElapsedSeconds() : std::numeric_limits<float>::epsilon();;
}

double GameTime::GetDeltaTimeSeconds()
{
	return deltaTime;
}

float GameTime::GetDeltaTimeSecondsF()
{
	return GetDeltaTimeSeconds() > std::numeric_limits<float>::epsilon() ? GetDeltaTimeSeconds() : std::numeric_limits<float>::epsilon();
}

long GameTime::GetDeltaTimeMillis()
{
	return deltaTime * 1000;
}
