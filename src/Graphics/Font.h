/*
    MINX - A C++ Graphics and Input Wrapper Library
    Copyright (C) 2013  MINX Team

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

	*/
#ifndef FONT_H_
#define FONT_H_

#include <ft2build.h>
#include FT_FREETYPE_H
#include <GL/glew.h>
#include "GameWindow.h"
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
			Font(FT_Library libraryRef, char* fileLocation, GLuint shaderProgram);
			void RenderChar(char charToRender, int x, int y);
			void RenderString(std::string text, float x, float y, float sx, float sy);
			void RenderCharStar(const char *text, float x, float y, float sx, float sy);
		private:
			GLuint shaderProgram;
			FT_Library library;
			FT_Face fontFace;
			FT_CharMap charMap;
			FT_GlyphSlot glyphSlot;
		};
	}
}

#endif