
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
#ifndef FONT_H_
#define FONT_H_

#include "../API.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <GL/glew.h>
#include "GameWindow.h"
#include "../Vector2.h"
#include "Color.h"
#include <string>
#include "Texture2D.h"

namespace MINX
{
	class MINX_API Game;
	namespace Graphics
	{
		/** A Font Container Class
		 * Protip: Use std::stringstream in order to concatenate strings with numbers
		*/
		class MINX_API Font
		{
		public:
			/** Creates a new Instance of a Font
			*/
			Font(Game* gameHandle, char* fileLocation, GLuint shaderProgram);
			
			/** Renders Text Onto the Screen using a string from the C++ standard library
			*	@param text The text to render to the screen.
			*	@param x The X component of the screen to draw the text to.
			*	@param y The Y component of the screen to draw the text to.
			*	@param fontSixe The size in points (pt.) to draw the font.
			*/
			void RenderText(std::string text, float x, float y, int fontSize);

			/** Renders Text Onto the Screen using a c-string (char*)
			*	@param text The text to render to the screen.
			*	@param x The X component of the screen to draw the text to.
			*	@param y The Y component of the screen to draw the text to.
			*	@param fontSixe The size in points (pt.) to draw the font.
			*/
			void RenderText(const char *text, float x, float y, int fontSize);
			
			/** Renders Text Onto the Screen using a string from the C++ standard library
			*	@param text The text to render to the screen.
			*	@param x The X component of the screen to draw the text to.
			*	@param y The Y component of the screen to draw the text to.
			*	@param fontSixe The size in points (pt.) to draw the font.
			*/
			void RenderText(std::string text, float x, float y, int fontSize, Color color);

			/** Renders Text Onto the Screen using a c-string (char*)
			*	@param text The text to render to the screen.
			*	@param x The X component of the screen to draw the text to.
			*	@param y The Y component of the screen to draw the text to.
			*	@param fontSixe The size in points (pt.) to draw the font.
			*/
			void RenderText(const char *text, float x, float y, int fontSize, Color color);

			/** Gets the size of the text if it were to be rendered
			*	@param text The text to check the size of.
			*	@param fontSize The size in points (pt.) to check the size of.
			*	@return The Size of the Text as a Vector2 with the width as the X component and the height as the Y component
			*/
			Vector2 TextSize(const char *text, int fontSize);
		private:
			float getMaxHeightGap(const char *text, int fontSize);
			GLuint shaderProgram;
			GLint attribute_coord;
			GLint uniform_tex;
			GLint uniform_color;
			GLuint vertexBuffer;
			FT_Library library;
			FT_Face fontFace;
			FT_CharMap charMap;
			FT_GlyphSlot glyphSlot;
			GLuint tex[256];

			Vector2 textSize;

		};
	}
}

#include "../Game.h"
#endif
