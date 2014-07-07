
/*
# The zlib/libpng License

MINX Copyright (c) 2013-2014 Liam Middlebrook, Benjamin Pylko

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

#include "Rectangle.h"
#include <math.h>

using namespace MINX;

Rectangle::Rectangle()
{
	X = 0;
	Y = 0;
	Width = 0;
	Height = 0;
}
Rectangle::Rectangle(double x, double y, double width, double height)
{
	X=x;
	Y=y;
	Width = width;
	Height = height;
}
double Rectangle::Area()
{
	return Width * Height;
}
double Rectangle::Top()
{
	return Y;
}
double Rectangle::Bottom()
{
	return Y + Height;
}
double Rectangle::Left()
{
	return X;
}
double Rectangle::Right()
{
	return X + Width;
}
bool Rectangle::Intersects(Rectangle* rect2)
{
	return !(
			(Bottom() < rect2->Top()) ||
			(Top() > rect2->Bottom()) ||
			(Left() > rect2->Right()) ||
			(Right() < rect2->Left()) );
}
