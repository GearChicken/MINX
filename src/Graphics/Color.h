
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

#include "../API.h"

namespace MINX
{
	namespace Graphics
	{
		/** A struct representing a color.
		 */
		struct MINX_API Color
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

			/** Tests if a color is lighter than another Color
			 */
			bool operator>(const Color& compareTo);

			/** Tests if a color is lighter than or the same as another Color
			 */
			bool operator>=(const Color& compareTo);

			/** Tests if a Color is darker than another Color
			 */
			bool operator<(const Color& compareTo);

			/** Tests if a Color is darker than or the same as another Color
			 */
			bool operator<=(const Color& compareTo);

			/** Inverts a Color
			 */
			Color operator!()const;

			/** Adds 2 Colors
			 */
			Color operator+(const Color& addTo);

			/** Adds 2 Colors
			 */
			Color operator+=(const Color& addTo);

			/** Subtracts a color from another color
			 */
			Color operator-(const Color& subtract);

			/** Subtracts a color from another color
			 */
			Color operator-=(const Color& subtract);

			/** Multiplies 2 colors
			 */
			Color operator*(const Color& multiplyBy);

			/** Multiplies 2 colors
			 */
			Color operator*=(const Color& multiplyBy);

			/** Divides a color by another color
			 */
			Color operator/(const Color& divideBy);

			/** Divides a color by another color
			 */
			Color operator/=(const Color& divideBy);

			/** Cross multiplies 2 colors
			 */
			Color Cross(const Color& crossWith);

			/** Multiplies a color by a scale
			 */
			Color operator*(const double& scale);

			/** Multiplies a color by a scale
			 */
			Color operator*=(const double& scale);

			/** Divides a color by a scale
			 */
			Color operator/(const double& scale);

			/** Divides a color by a scale
			 */
			Color operator/=(const double& scale);

			/** \defgroup colors Named Colors
			 * @{
			 */
			/** \defgroup Transparency
			 * @{
			 */
			static Color TransparentBlack;
			static Color TransparentWhite;

			/** @}*/
			/** \defgroup Pink Shades of Pink
			 * @{
			 */
			static Color Pink;
			static Color LightPink;
			static Color HotPink;
			static Color DeepPink;
			static Color PaleVioletRed;
			static Color MediumVioletRed;

			/** @}*/
			/** \defgroup Red Shades of Red
			 * @{
			 */
			static Color LightSalmon;
			static Color Salmon;
			static Color DarkSalmon;
			static Color LightCoral;
			static Color IndianRed;
			static Color Crimson;
			static Color FireBrick;
			static Color DarkRed;
			static Color Red;

			/** @}*/
			/** \defgroup Orange Shades of Orange
			 * @{
			 */
			static Color OrangeRed;
			static Color Tomato;
			static Color Coral;
			static Color DarkOrange;
			static Color Orange;

			/** @}*/
			/** \defgroup Yellow Shades of Yellow
			 * @{
			 */
			static Color Yellow;
			static Color LightYellow;
			static Color LemonChiffon;
			static Color LightGoldenrodYellow;
			static Color PapayaWhip;
			static Color Moccasin;
			static Color PeachPuff;
			static Color PaleGoldenrod;
			static Color Khaki;
			static Color DarkKhaki;
			static Color Gold;

			/** @}*/
			/** \defgroup Brown Shades of Brown
			 * @{
			 */
			static Color Cornsilk;
			static Color BlanchedAlmond;
			static Color Bisque;
			static Color NavajoWhite;
			static Color Wheat;
			static Color BurlyWood;
			static Color Tan;
			static Color RosyBrown;
			static Color SandyBrown;
			static Color GoldenRod;
			static Color DarkGoldenrod;
			static Color Peru;
			static Color Chocolate;
			static Color SaddleBrown;
			static Color Sienna;
			static Color Brown;
			static Color Maroon;

			/** @}*/
			/** \defgroup Green Shades of Green
			 * @{
			 */
			static Color DarkOliveGreen;
			static Color Olive;
			static Color OliveDrab;
			static Color YellowGreen;
			static Color LimeGreen;
			static Color Lime;
			static Color Green;
			static Color LawnGreen;
			static Color Chartreuse;
			static Color GreenYellow;
			static Color SpringGreen;
			static Color MediumSpringGreen;
			static Color LightGreen;
			static Color PaleGreen;
			static Color DarkSeaGreen;
			static Color MediumSeaGreen;
			static Color SeaGreen;
			static Color ForestGreen;
			static Color WebGreen;
			static Color DarkGreen;

			/** @}*/
			/** \defgroup Cyan Shades of Cyan
			 * @{
			 */
			static Color MediumAquamarine;
			static Color Cyan;
			static Color LightCyan;
			static Color PaleTurquoise;
			static Color Aquamarine;
			static Color Turquoise;
			static Color MediumTurquoise;
			static Color DarkTurquoise;
			static Color LightSeaGreen;
			static Color CadetBlue;
			static Color DarkCyan;
			static Color Teal;

			/** @}*/
			/** \defgroup Blue Shades of Blue
			 * @{
			 */
			static Color LightSteelBlue;
			static Color PowderBlue;
			static Color LightBlue;
			static Color SkyBlue;
			static Color LightSkyBlue;
			static Color DeepSkyBlue;
			static Color DodgerBlue;
			static Color CornflowerBlue;
			static Color SteelBlue;
			static Color RoyalBlue;
			static Color Blue;
			static Color MediumBlue;
			static Color DarkBlue;
			static Color Navy;
			static Color MidnightBlue;

			/** @}*/
			/** \defgroup Purple Shades of Purple
			 * @{
			 */
			static Color Lavender;
			static Color Thistle;
			static Color Plum;
			static Color Violet;
			static Color Orchid;
			static Color Magenta;
			static Color MediumOrchid;
			static Color MediumPurple;
			static Color BlueViolet;
			static Color DarkViolet;
			static Color DarkOrchid;
			static Color DarkMagenta;
			static Color Purple;
			static Color Indigo;
			static Color DarkSlateBlue;
			static Color SlateBlue;
			static Color MediumSlateBlue;

			/** @}*/
			/** \defgroup White Shades of White
			 * @{
			 */
			static Color White;
			static Color Snow;
			static Color Honeydew;
			static Color MintCream;
			static Color Azure;
			static Color AliceBlue;
			static Color GhostWhite;
			static Color WhiteSmoke;
			static Color Seashell;
			static Color Beige;
			static Color OldLace;
			static Color FloralWhite;
			static Color Ivory;
			static Color AntiqueWhite;
			static Color Linen;
			static Color LavenderBlush;
			static Color MistyRose;

			/** @}*/
			/** \defgroup Gray Shades of Gray
			 * @{
			 */
			static Color Gainsboro;
			static Color LightGray;
			static Color Silver;
			static Color DarkGray;
			static Color Gray;
			static Color DimGray;
			static Color LightSlateGray;
			static Color SlateGray;
			static Color DarkSlateGray;

			/** @}*/
			/** \defgroup Black
			 * @{
			 */
			static Color Black;

			/** @}*/
			/** @}*/
		};
	}
}
#endif
