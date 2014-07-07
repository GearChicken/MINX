
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
#ifndef COLOR_H_
#define COLOR_H_
namespace MINX
{
	namespace Graphics
	{
		/** A struct representing a color.
		 */
		struct Color
		{
			/** The red component of the color.
			 */
			double R;
			/** The green component of the color.
			 */
			double G;
			/** The blue component of the color.
			 */
			double B;
			/** The alpha component of the color.
			 */
			double A;
			/** Constructs the Color with a default value of White
			 */
			Color();
			/** Constructs a color with the given red, green, blue, and alpha values.
			 */
			Color(double r, double g, double b, double a);
			/** Constructs a color with the given red, green, and blue values.
			 */
			Color(double r, double g, double b);
			/** Tests equality between two Colors.
			 */
			bool operator==(const Color& compareTo);
			/** Tests inequality between two Colors
			 */
			bool operator!=(const Color& compareTo);
			/** Multiplies a color by a scale.
			 */
			Color* operator*(const double& scale);
			/** Multiplies a color by a scale.
			 */
			Color* operator*=(const double& scale);
		};
	}
}
#endif
