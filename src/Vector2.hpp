/*
# MINX

Copyright (c) 2013-2014 Liam Middlebrook, Benjamin Pylko

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

> 1\. The origin of this software must not be misrepresented; you must not
> claim that you wrote the original software. If you use this software
> in a product, an acknowledgment in the product documentation would be
> appreciated but is not required
>
> 2\. Altered source versions must be plainly marked as such, and must not be
> misrepresented as being the original software
>
> 3\. This notice may not be removed or altered from any source
> distribution
>
 */

#ifndef MINX_VECTOR2_HPP_
#define MINX_VECTOR2_HPP_

#include "API.hpp"

namespace MINX
{
	/** A Vector that holds 2 components, X and Y
	 */
	struct MINX_API Vector2
	{
		/** Used when constructing a Vector2 by magnitude/direction instead of x/y
		 */
		enum Heading
		{
			E = 0,
			E_BY_NE = 1,
			NE = 2,
			N_BY_NE = 3,
			N = 4,
			N_BY_NW = 5,
			NW = 6,
			W_BY_NW = 7,
			W = 8,
			W_BY_SW = 9,
			SW = 10,
			S_BY_SW = 11,
			S = 12,
			S_BY_SE = 13,
			SE = 14,
			E_BY_SE = 15
		};
		
		/** Initializes the Vector2 with a value of (0, 0)
		 */
		Vector2();
		
		/** Initializes the Vector2 with an x and a y component
		 * @param x The x component of the Vector2
		 * @param y The y component of the Vector2
		 */
		Vector2(double x, double y);
		
		/** Initializes the Vector2 with a magnitude, direction, and heading
		 * @param magnitude The magnitude of the Vector2
		 * @param direction The direction of the Vector2
		 * @param heading The heading (offset of direction) of the Vector2
		 */
		Vector2(double magnitude, double direction, Heading heading);
		
		/** Adds 2 Vector2s
		 * @param addTo the Vector2 to add
		 */
		Vector2 operator+(const Vector2& addTo);
		
		/** Adds 2 Vector2s
		 * @param addTo the Vector2 to add
		 */
		Vector2 operator+=(const Vector2& addTo);
		
		/** Subtracts a Vector2 from another
		 * @param subtractFrom the Vector2 to subtract
		 */
		Vector2 operator-(const Vector2& subtractFrom);
		
		/** Subtracts a Vector2 from another
		 * @param subtractFrom the Vector2 to subtract
		 */
		Vector2 operator-=(const Vector2& subtractFrom);
		
		/** "cross multiplies" 2 Vector2s
		 * There are "'s there because you can't REALLY cross multiply a 2 dimensional vector
		 * It's equivalent to v1.X * v2.Y - v1.Y * v2.X, or v1.Length() * v2.Length() * sin(theta)
		 * @param multiplyBy the Vector2 to "cross multiply" by
		 */
		double Cross(const Vector2& multiplyBy);
		
		/** Dot multiplies 2 Vector2s
		 * @param multiplyBy the Vector2 to dot multiply by
		 */
		double Dot(const Vector2& multiplyBy);
		
		/** Multiplies 2 Vector2s component-wise
		 * @param multiplyBy the Vector2 to dot multiply by
		 */
		Vector2 operator*(const Vector2& multiplyBy);
		
		/** Multiplies a Vector2 by a scalar
		 * @param multiplyBy the scalar to multiply the length of the Vector2 by
		 */
		Vector2 operator*(const double& multiplyBy);
		
		/** Multiplies a Vector2 by a scalar
		 * @param multiplyBy the scalar to multiply the length of the Vector2 by
		 */
		Vector2 operator*=(const double& multiplyBy);
		
		/** Multiplies a Vector2 by another component-wise
		 * @param multiplyBy the Vector2 to multiply the Vector2 by
		 */
		Vector2 operator*=(const Vector2& multiplyBy);
		
		/** Divides 2 Vector2s component-wise
		 * @param divideBy the Vector2 to dot multiply by
		 */
		Vector2 operator/(const Vector2& divideBy);
		
		/** Divides a Vector2 by a scalar
		 * @param divideBy the scalar to divide the length of the Vector2 by
		 */
		Vector2 operator/(const double& divideBy);
		
		/** Divides a Vector2 by a scalar
		 * @param multiplyBy the scalar to divide the length of the Vector2 by
		 */
		Vector2 operator/=(const double& divideBy);
		
		/** Divides a Vector2 by a scalar
		 * @param multiplyBy the scalar to divide the length of the Vector2 by
		 */
		Vector2 operator/=(const Vector2& divideBy);
		
		/** Negates a Vector2
		 */
		Vector2 operator-()const;
		
		/** Tests equality between 2 Vector2s
		 * @param compareTo the Vector2 to test equality with
		 */
		bool operator==(const Vector2& compareTo);
		
		/** Tests inequality between 2 Vector2s
		 * @param compareTo the Vector2 to test equality with
		 */
		bool operator!=(const Vector2& compareTo);
		
		/** Returns the length of the Vector2
		 */
		double Length();
		
		/** Returns the magnitude of the Vector2
		 */
		inline double Magnitude(){return Length();}
		
		/** Returns the length of the Vector2 squared
		 * This is faster then squaring the result of length() because length() actually returns the square root of the mathematical result of the length squared
		 */
		double LengthSquared();
		
		/** Returns a Vector2 of length 1 but the same direction as the current Vector2
		 */
		Vector2 Normalize();
		
		/** Returns the direction of the vector in radians
		 */
		double Direction();
		
		/** The X component of the Vector2
		 */
		double X;
		
		/** The Y component of the Vector2
		 */
		double Y;
	};
}
#endif
