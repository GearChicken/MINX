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
#ifndef _TEXT2D_H
#define _TEXT2D_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GL/FreeImage.h>
#include "Color.h"
#include "GameWindow.h"
#include "../Rectangle.h"
#include <string>
//TODO: Implement Sprite Sheet http://antongerdelan.net/opengl/sprite_sheets.html
namespace MINX
{
	namespace Graphics
	{
		class Text2D
		{
		public:
			Text2D(char* fileLoc, GLuint shaderProgram);
			~Text2D();
			void DrawString(float x, float y, std::string text);
			void DrawString(float x, float y, std::string text, Color* color);
		private:
			MINX_Rectangle* GlyphToCoords(char glyph);
			void Draw(MINX_Rectangle* sourceRect);
			double width;
			double height;
			float vertices[42];
			GLuint vertexBuffer;
			GLuint vertexArray;
			GLuint shaderProgram;
			GLint uniTrans;
			GLint uniTint;
			GLint uniSourceX;
			GLint uniSourceY;
			GLint uniRows;
			GLint uniColumns;
			GLuint texture;
			glm::mat4 ConvCoords(glm::vec4 coords);
		};

	}

}
#endif