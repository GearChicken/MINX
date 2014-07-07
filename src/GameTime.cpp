
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
#include "GameTime.h"
using namespace MINX;

GameTime::GameTime()
{
	totalTimeMillis=0;
	deltaTime=0;
	lastUpdate=0;
}

/*void GameTime::limitFPS(int desiredFPS)
{
	
	int NextTick = totalTimeMillis + (1000/desiredFPS);
	if(NextTick > glfwGetTime())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000/desiredFPS-deltaTimeMillis));
	}
}//*/
void GameTime::Update()
{
	totalTimeMillis = glfwGetTime()*1000.0;
	deltaTime = totalTimeMillis - lastUpdate;
	lastUpdate = totalTimeMillis;
	deltaTime = deltaTime > 0 ? deltaTime : std::numeric_limits<double>::epsilon();
}
long GameTime::GetElapsedMillis()
{
	return totalTimeMillis;
}

double GameTime::GetDeltaTimeSeconds()
{
	return deltaTime / 1000.0;
}

float GameTime::GetDeltaTimeSecondsF()
{
	return GetDeltaTimeSeconds() > std::numeric_limits<float>::epsilon() ? GetDeltaTimeSeconds() : std::numeric_limits<float>::epsilon();
}

long GameTime::GetDeltaTimeMillis()
{
	return deltaTime;
}
