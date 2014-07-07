
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

#ifndef RAY2_H_
#define RAY2_H_

#include "API.h"

namespace MINX
{
	/** Represents a 2 dimensional ray.
	 * Contains 2 position components and one direction (sorry) component.
	 * Of course the direction is in radians.
	 */
	struct MINX_API Ray2
	{
		/** Creates a Ray2 with the specified direction and position.
		 */
		Ray2(double direction, double xPosition, double yPosition);
		/** Creates a Ray2 with the specified direction.
		 */
		Ray2(double direction);
		/** The direction of the Ray2.
		 */
		double dir;
		/** The X position of the Ray2.
		 */
		double xPos;
		/** The Y position of the Ray2.
		 */
		double yPos;
		/** Negates a Ray2.
		 */
		Ray2 operator-()const;
		/** Tests equality between 2 Ray2s.
		 */
		bool operator==(const Ray2& compareTo);
		/** Tests inequality between 2 Ray2s.
		 */
		bool operator!=(const Ray2& compareTo);
	};
}
#endif
