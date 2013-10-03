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
#include "Graphics/Text2D.h"
#include <iostream>
using namespace MINX::Graphics;
using namespace MINX;
Text2D::Text2D(char* fileLoc, GLuint shaderProgram)
{
	float tempVertices[] = {
	-01.0f,  01.0f,		 1.0f, 1.0f, 1.0f,		0.0f, 1.0f, // Top-left
     01.0f,  01.0f,		 1.0f, 1.0f, 1.0f,		1.0f, 1.0f,// Top-right
     01.0f, -01.0f,		 1.0f, 1.0f, 1.0f,		1.0f, 0.0f,// Bottom-right

     01.0f, -01.0f,		 1.0f, 1.0f, 1.0f,		1.0f, 0.0f,// Bottom-right
    -01.0f, -01.0f,		 1.0f, 1.0f, 1.0f,		0.0f, 0.0f,// Bottom-left
    -01.0f,  01.0f,		 1.0f, 1.0f, 1.0f,		0.0f, 1.0f// Top-left
	};

	for(int i =0 ; i < sizeof(vertices) / sizeof(float); i++)
	{
		vertices[i] =  tempVertices[i];
	}

	glGenVertexArrays(1,&vertexArray);
	glBindVertexArray(vertexArray);
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,  sizeof(vertices), vertices, GL_STATIC_DRAW);


	
	GLint posAttrib = glGetAttribLocation( shaderProgram, "position" );
	glEnableVertexAttribArray( posAttrib );
	glVertexAttribPointer( posAttrib, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), 0 );

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib,3,GL_FLOAT,GL_FALSE,7*sizeof(float),(void*)(2*sizeof(float)));

	GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(5*sizeof(float)));
		this->shaderProgram = shaderProgram;
	
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture(GL_TEXTURE_2D, texture);
	//glBindTexture(GL_TEXTURE_2D, tex);
	//float color[] = {1.0f, 0.0f, 0.0f, 1.0f};
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color
	// IMAGAE LOADING
		FIBITMAP* bitmap = FreeImage_Load(
			FreeImage_GetFileType(fileLoc, 0),
			fileLoc);
		FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);

		int nWidth = FreeImage_GetWidth(pImage);
		int nHeight = FreeImage_GetHeight(pImage);
		this->width = nWidth;
		this->height = nHeight;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
			0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

		FreeImage_Unload(pImage);
	//END IMAGE LOADING);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glGenerateMipmap(GL_TEXTURE_2D);
	
	 uniTrans = glGetUniformLocation( shaderProgram, "trans" );
	 uniSourceX = glGetUniformLocation( shaderProgram, "sourceX" );
	 uniSourceY = glGetUniformLocation( shaderProgram, "sourceY" );
	 uniRows = glGetUniformLocation( shaderProgram, "rows" );
	 uniColumns = glGetUniformLocation( shaderProgram, "columns" );
	 uniTint = glGetUniformLocation(shaderProgram, "tint");

	 this->texture = texture;
	//*/
}
Text2D::~Text2D()
{
	glDeleteBuffers( 1, &vertexBuffer );
	glDeleteVertexArrays( 1, &vertexArray );
}
void Text2D::DrawString(float x, float y, std::string text)
{

	for(int i = 0; i < text.length(); i++)
	{
		x+=64;
		//make new translation matrix
		glm::mat4 trans;//translate to the new xy coords, and add w/2 h/2 to switch origin to the top left
		trans = glm::translate(trans, glm::vec3(x + 64.0/2.0,y + 64.0/2.0 ,0));
		//convert matrix position to vec4
		glm::vec4 result = trans * glm::vec4(1,1,1,1);
		//convert coords to OpenGL style coords
		glm::mat4 finalMat = ConvCoords(result);
		//scale the matrix to compensate for the size of the image on the screen
		finalMat = glm::scale(finalMat, glm::vec3(1.0*64.0/GameWindow::width, 1.0*64.0/GameWindow::height, 1.0));

		glUniformMatrix4fv( uniTrans, 1, GL_FALSE, glm::value_ptr(finalMat));
		this->Draw(GlyphToCoords(text[i]));
	}
}
void Text2D::DrawString(float x, float y, std::string text, Color* color)
{
	glUniform3f(uniTint, color->R/255.0f,color->G/255.0f,color->B/255.0f);
	DrawString(x,y,text);
}
void Text2D::Draw(MINX_Rectangle* sourceRect)
{
	int columns = width / sourceRect->Width;
	int rows = height / sourceRect->Height;
	glUniform1f( uniSourceX, sourceRect->X / width);
	glUniform1f( uniSourceY, sourceRect->Y / height);
	glUniform1f( uniColumns, columns);
	glUniform1f( uniRows, rows);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(vertexArray);
	glDrawArrays(GL_TRIANGLES,0,6);
}
glm::mat4 Text2D::ConvCoords(glm::vec4 coords)
{
	glm::mat4 trans;
	coords.x +=-GameWindow::width/2.0;
	coords.y +=-GameWindow::height/2.0;
	coords.x *= 2.0/GameWindow::width;
	coords.y *= -(2.0/GameWindow::height);
	return glm::translate(trans,glm::vec3(coords.x, coords.y, coords.z));
}
MINX_Rectangle* Text2D::GlyphToCoords(char glyph)
{
	switch (glyph)
	{
	case 'a':
		return new MINX_Rectangle(0,0,64,64);
		break;
	case 'b':
		return new MINX_Rectangle(64,0,64,64);
		break;
	case 'c':
		return new MINX_Rectangle(128,0,64,64);
		break;
	case 'd':
		return new MINX_Rectangle(192,0,64,64);
		break;
	case 'e':
		return new MINX_Rectangle(256,0,64,64);
		break;
	case 'f':
		return new MINX_Rectangle(320,0,64,64);
		break;
	case 'g':
		return new MINX_Rectangle(384,0,64,64);
		break;
	case 'h':
		return new MINX_Rectangle(448,0,64,64);
		break;
	case 'i':
		return new MINX_Rectangle(512,0,64,64);
		break;
	case 'j':
		return new MINX_Rectangle(576,0,64,64);
		break;
	case 'k':
		return new MINX_Rectangle(640,0,64,64);
		break;
	case 'l':
		return new MINX_Rectangle(704,0,64,64);
		break;
	case 'm':
		return new MINX_Rectangle(768,0,64,64);
		break;
	case 'n':
		return new MINX_Rectangle(832,0,64,64);
		break;
	case 'o':
		return new MINX_Rectangle(896,0,64,64);
		break;
	case 'p':
		return new MINX_Rectangle(960,0,64,64);
		break;
	case 'q':
		return new MINX_Rectangle(0,64,64,64);
		break;
	case 'r':
		return new MINX_Rectangle(64,64,64,64);
		break;
	case 's':
		return new MINX_Rectangle(128,64,64,64);
		break;
	case 't':
		return new MINX_Rectangle(192,64,64,64);
		break;
	case 'u':
		return new MINX_Rectangle(256,64,64,64);
		break;
	case 'v':
		return new MINX_Rectangle(320,64,64,64);
		break;
	case 'w':
		return new MINX_Rectangle(384,64,64,64);
		break;
	case 'x':
		return new MINX_Rectangle(448,64,64,64);
		break;
	case 'y':
		return new MINX_Rectangle(512,64,64,64);
		break;
	case 'z':
		return new MINX_Rectangle(576,64,64,64);
		break;
	case ' ':
		return new MINX_Rectangle(640,64,64,64);
		break;
	}
}