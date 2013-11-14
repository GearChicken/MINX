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
#include "Font.h"
#include "Texture2D.h"
using namespace MINX;
using namespace MINX::Graphics;
Font::Font(FT_Library libraryRef, char* fileLocation, GLuint shaderProgram)
{
	this->library = libraryRef;
	this->shaderProgram = shaderProgram;
	FT_New_Face(library, fileLocation, 0, &fontFace);
	FT_Set_Char_Size(fontFace, 0, 16*64, 96, 96);
}
void Font::RenderChar(char charToRender, int x, int y)
{ 
	FT_Load_Char(fontFace, charToRender, FT_LOAD_RENDER);
}

void Font::RenderString(std::string text, float x, float y, float sx, float sy)
{

	glyphSlot = fontFace->glyph;
	const char *p;
	for(p = text.c_str(); *p; p++)
	{
		if(FT_Load_Char(fontFace, *p, FT_LOAD_RENDER))
			continue;



		float x2 = x + glyphSlot->bitmap_left * sx;
		float y2 = y + glyphSlot->bitmap_top * sy;
		float w = glyphSlot->bitmap.width * sx;
		float h = glyphSlot->bitmap.rows * sy;

		Texture2D* texture;
		texture = new Texture2D(glyphSlot->bitmap.buffer, w, h, GL_ALPHA, shaderProgram);
		texture->Draw(x2, y2  + (glyphSlot->metrics.vertAdvance - glyphSlot->metrics.height)/64.0f - glyphSlot->metrics.horiBearingY/64.0f + (glyphSlot->metrics.height - glyphSlot->metrics.horiBearingY)/64.0f, 1.0f, -1.0f);
		texture->~Texture2D();
		delete texture;

		x += (glyphSlot->advance.x >> 6) * sx;
		y += (glyphSlot->advance.y >> 6) * sy;
	}
}
void Font::RenderCharStar(const char *text, float x, float y, float sx, float sy)
{

	glyphSlot = fontFace->glyph;
	const char *p;
	for(p = text; *p; p++)
	{
		if(FT_Load_Char(fontFace, *p, FT_LOAD_RENDER))
			continue;



		float x2 = x + glyphSlot->bitmap_left * sx;
		float y2 = y + glyphSlot->bitmap_top * sy;
		float w = glyphSlot->bitmap.width * sx;
		float h = glyphSlot->bitmap.rows * sy;

		Texture2D* texture;
		texture = new Texture2D(glyphSlot->bitmap.buffer, w, h, GL_ALPHA, shaderProgram);
		texture->Draw(x2, y2  + (glyphSlot->metrics.vertAdvance - glyphSlot->metrics.height)/64.0f - glyphSlot->metrics.horiBearingY/64.0f + (glyphSlot->metrics.height - glyphSlot->metrics.horiBearingY)/64.0f, 1.0f, -1.0f);
		texture->~Texture2D();
		delete texture;

		x += (glyphSlot->advance.x >> 6) * sx;
		y += (glyphSlot->advance.y >> 6) * sy;
	}
}
//http://www.freetype.org/freetype2/docs/tutorial/example1.c