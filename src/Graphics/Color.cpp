
/*
# The zlib/libpng License

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
#include "Color.h"
using namespace MINX::Graphics;

Color::Color()
{
	R = 255.0;
	B = 255.0;
	G = 255.0;
	A = 255.0;
}

Color::Color(double r, double g, double b, double a)
{
	R=r;
	G=g;
	B=b;
	A=a;
}

Color::Color(double r, double g, double b)
{
	R=r;
	G=g;
	B=b;
	A=255.0;
}
bool Color::operator==(const Color& compareTo)
{
	return R == compareTo.R && G == compareTo.G && B == compareTo.B && A == compareTo.A;
}
bool Color::operator!=(const Color& compareTo)
{
	return !operator==(compareTo);
}
Color* Color::operator*(const double& scale)
{
	return new Color(R*scale,G*scale,B*scale,A*scale);
}
Color* Color::operator*=(const double& scale)
{
	R*=scale;
	G*=scale;
	B*=scale;
	A*=scale;
	return this;
}
