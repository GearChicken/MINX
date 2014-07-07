
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

#include "Ray2.h"

using namespace MINX;

Ray2::Ray2(double direction, double xPosition, double yPosition)
{
	dir=direction;
	xPos=xPosition;
	yPos=yPosition;
}

Ray2::Ray2(double direction)
{
	dir=direction;
	xPos=0;
	yPos=0;
}

Ray2 Ray2::operator-()const
{
	return Ray2(-dir,xPos,yPos);
}

bool Ray2::operator==(const Ray2& compareTo)
{
	return dir==compareTo.dir && xPos==compareTo.xPos && yPos==compareTo.yPos;
}

bool Ray2::operator!=(const Ray2& compareTo)
{
	return !operator==(compareTo);
}
