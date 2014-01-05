/*
MINX - A C++ Graphics and Input Wrapper Library
Copyright (C) 2013-2014  MINX Team

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
#include <iostream>
using namespace MINX;
using namespace MINX::Graphics;
Font::Font(FT_Library libraryRef, char* fileLocation, GLuint shaderProgram)
{
	this->library = libraryRef;
	this->shaderProgram = shaderProgram;
	FT_New_Face(library, fileLocation, 0, &fontFace);
	FT_Set_Pixel_Sizes(fontFace, 0, 48);
	//FT_Set_Char_Size(fontFace, 0, 16*64, 96, 96);
	attribute_coord = glGetAttribLocation(shaderProgram, "coord");
	uniform_tex = glGetUniformLocation(shaderProgram, "tex");
	uniform_color = glGetUniformLocation(shaderProgram, "color");
	glGenBuffers(1, &vertexBuffer);
	for (int i = 0; i < 256; i++)
	{
		tex[i] = 0;
	}
}

void Font::RenderText(std::string text, float x, float y, int fontSize)
{
	RenderText(text.c_str(), x, y, fontSize);
}
void Font::RenderText(const char *text, float x, float y, int fontSize)
{

	float sx = 2.0f / GameWindow::width;
	float sy = 2.0f / GameWindow::height;


	glUseProgram(shaderProgram);
	FT_Set_Pixel_Sizes(fontFace, 0, fontSize);
	GLfloat color[] = {0.0f, 0.0f, 0.0f, 1.0f};
	glUniform4fv(uniform_color, 1, color); 
	glyphSlot = fontFace->glyph;
	const char *p;


	//vertexbuffer
	glEnableVertexAttribArray(attribute_coord);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0 , 0);
	float textWidthGLCoords = 0.0f;
	float textHeightGLCoords = 0.0f;
	Vector2 textSize = TextSize(text, fontSize);
	textWidthGLCoords = textSize.X;
	textHeightGLCoords = textSize.Y;
	//std::cout << textWidthGLCoords << " Text width" << std::endl;
	//std::cout << textHeightGLCoords << " Text height" << std::endl;
	/*
	x += 0 - textWidthGLCoords;
	y += 1 - textHeightGLCoords;
	*/
	glm::mat4 modelviewMatrix;
	glm::mat4 projectionMatrix;
	projectionMatrix = glm::ortho(0.0f, (float)GameWindow::width-0.0f, (float)GameWindow::height-0.0f, 0.0f);

	//make new translation matrix
	modelviewMatrix = glm::translate(projectionMatrix, glm::vec3(x, y + textHeightGLCoords, 1));
	x = modelviewMatrix[3][0];
	y = modelviewMatrix[3][1];

	//std::cout << x << " x" << std::endl;
	//std::cout << y << " y" << std::endl;

	for(p = text; *p; p++)
	{
		if(FT_Load_Char(fontFace, *p, FT_LOAD_RENDER))
			continue;



		if(!tex[*p])
		{
			glActiveTexture(GL_TEXTURE0);
			glGenTextures(1, &(tex[*p]));
			glBindTexture(GL_TEXTURE_2D, tex[*p]);
			glUniform1i(uniform_tex, 0);

			//1 byte alignmeny
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			//clamp edges
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			//linear filetering
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, glyphSlot->bitmap.width, glyphSlot->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, glyphSlot->bitmap.buffer);

		}
		glBindTexture(GL_TEXTURE_2D, tex[*p]);
		float x2 = x + glyphSlot->bitmap_left * sx;
		float y2 = -y - glyphSlot->bitmap_top * sy;
		float w = glyphSlot->bitmap.width * sx;
		float h = glyphSlot->bitmap.rows * sy;


		GLfloat box[4][4] = {
			{x2,     -y2    , 0, 0},
			{x2 + w, -y2    , 1, 0},
			{x2,     -y2 - h, 0, 1},
			{x2 + w, -y2 - h, 1, 1},
		};

		//std::cout << "X: " << box[0][0] << " Y: " << box[0][1] << std::endl;
		glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		x += (glyphSlot->advance.x >> 6) * sx;
		y += (glyphSlot->advance.y >> 6) * sy;
	}

	glDisableVertexAttribArray(attribute_coord);
	//glDeleteTextures(1, &(tex[*p]));

}
Vector2 Font::TextSize(const char *text, int fontSize)
{
	float textWidthGLCoords = 0.0f;
	float textHeightGLCoords = 0.0f;
	const char *p;
	for(p = text; *p; p++)
	{
		if(FT_Load_Char(fontFace, *p, FT_LOAD_RENDER))
			continue;
		textWidthGLCoords += glyphSlot->bitmap.width;// * sx;
		textHeightGLCoords = (glyphSlot->bitmap.rows > textHeightGLCoords) ? glyphSlot->bitmap.rows : textHeightGLCoords;
	}

	//std::cout << textWidthGLCoords << " Text width" << std::endl;
	//std::cout << textHeightGLCoords << " Text height" << std::endl;
	return Vector2(textWidthGLCoords, textHeightGLCoords);
}
//http://www.freetype.org/freetype2/docs/tutorial/example1.c