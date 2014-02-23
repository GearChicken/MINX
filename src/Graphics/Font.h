/*
    MINX - A C++ Graphics and Input Wrapper Library
    Copyright (C) 2013-2014  MINX Team

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

	*/
#ifndef FONT_H_
#define FONT_H_

#include <ft2build.h>
#include FT_FREETYPE_H
#include <GL/glew.h>
#include "GameWindow.h"
#include "../Vector2.h"
#include "Color.h"
#include <string>

namespace MINX
{
	namespace Graphics
	{
		/** A Font Container Class
		*/
		class Font
		{
		public:
			/** Creates a new Instance of a Font
			*/
			Font(FT_Library libraryRef, char* fileLocation, GLuint shaderProgram);
			
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
		};
	}
}

#endif
