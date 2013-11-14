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
	FT_Set_Char_Size(fontFace, 0, 16*64, 72, 72);
}
void Font::RenderChar(char charToRender, int x, int y)
{ 
	Texture2D* texture;
	glyphSlot = fontFace->glyph;
	FT_Load_Char(fontFace, charToRender, FT_LOAD_RENDER);
	texture = new Texture2D(glyphSlot->bitmap.buffer, glyphSlot->bitmap.width, glyphSlot->bitmap.rows, GL_DEPTH_COMPONENT, shaderProgram);
	texture->Draw(x + glyphSlot->advance.x >> 6, y + glyphSlot->advance.y >> 6);
	texture->~Texture2D();
	delete texture;
}
void Font::RenderString(char* string, int x, int y)
{

	Texture2D* texture;
	glyphSlot = fontFace->glyph;
	for(int i = 0; i < sizeof(string)/sizeof(char); i++)
	{
	FT_Load_Char(fontFace, string[i], FT_LOAD_RENDER);
	texture = new Texture2D(glyphSlot->bitmap.buffer, glyphSlot->bitmap.width, glyphSlot->bitmap.rows, GL_DEPTH_COMPONENT, shaderProgram);
	texture->Draw(x*64 + glyphSlot->bitmap_left, y*64);
	texture->~Texture2D();
	delete texture;
	x += glyphSlot->advance.x;
	}
}


//http://www.freetype.org/freetype2/docs/tutorial/example1.c