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

#ifndef MINX_RECTANGLE_HPP_
#define MINX_RECTANGLE_HPP_

#include "API.hpp"

#include <cmath>

namespace MINX
{
	/** A Rectangle struct
	 */
	struct MINX_API Rectangle
	{
		/** Creates a new instance of Rectangle with all 0 values
		 */
		Rectangle();

		/** Creates a new instance of Rectangle
		 *	@param x The X coordinate of the Rectangle
		 *	@param y the Y coordinate of the Rectangle
		 *	@param width The Width of the Rectangle
		 *	@param height The Height of the Rectangle
		 */
		Rectangle(double x, double y, double width, double height);
		
		/** Returns the Area of the Rectangle
		*/
		double Area();
		
		/** The X location of the Rectangle
		 */
		double X;
		
		/** The Y location of the Rectangle
		 */
		double Y;
		
		/** The Width of the Rectangle
		 */
		double Width;
		
		/** The Height of the Rectangle
		 */
		double Height;
		
		/** The Y coordinate of the Top Edge of the Rectangle
		 */
		double Top();
		
		/** The Y coordinate of the Bottom Edge of the Rectangle
		 */
		double Bottom();
		
		/** The X coordinate of the Left Edge of the Rectangle
		 */
		double Left();
		
		/** The X coordinate of the Right Edge of the Rectangle
		 */
		double Right();
		
		/** Checks if one Rectangle intersects another
		 * @param rect2 The Rectangle to Check for Intersection against
		 * @returns Whether or not the two Rectangles intersect
		 */
		bool Intersects(Rectangle* rect2);
	};
}
#endif
