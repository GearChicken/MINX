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
#include "Texture2D.h"
#include <iostream>
using namespace MINX::Graphics;
using namespace MINX;
Texture2D::Texture2D(char* fileLoc, GLuint shaderProgram)
{
	this->attribute_coord = glGetAttribLocation(shaderProgram, "coord");
	uniTransformMatrix = glGetUniformLocation( shaderProgram, "trans" );
	uniSourceX = glGetUniformLocation( shaderProgram, "sourceX" );
	uniSourceY = glGetUniformLocation( shaderProgram, "sourceY" );
	uniRows = glGetUniformLocation( shaderProgram, "rows" );
	uniColumns = glGetUniformLocation( shaderProgram, "columns" );
	uniTint = glGetUniformLocation(shaderProgram, "color");
	uniform_tex = glGetUniformLocation(shaderProgram, "tex");

	glGenBuffers(1, &vertexBuffer);

	FIBITMAP* bitmap = FreeImage_Load(
		FreeImage_GetFileType(fileLoc, 0),
		fileLoc);
	FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);

	int nWidth = FreeImage_GetWidth(pImage);
	int nHeight = FreeImage_GetHeight(pImage);
	this->width = nWidth;
	this->height = nHeight;
	float tempVertices[] = {
		-nWidth/2.0f,   nHeight /2.0f,
		nWidth/2.0f,   nHeight /2.0f,
		nWidth/2.0f,  -nHeight /2.0f,
		-nWidth/2.0f,  -nHeight /2.0f
	};

	//copy vertex data over from temp data - doing this the lazy way fix later
	for(int i =0 ; i < sizeof(vertices) / sizeof(float); i++)
	{
		vertices[i] =  tempVertices[i];
	}


	this->shaderProgram = shaderProgram;
	glUseProgram(shaderProgram);

	glActiveTexture( GL_TEXTURE0 );
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(uniform_tex, 0);

	//glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
		0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));
	FreeImage_Unload(bitmap);
	FreeImage_Unload(pImage);
	//END IMAGE LOADING);

	//glGenerateMipmap(GL_TEXTURE_2D);
	
	glEnableVertexAttribArray(attribute_coord);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0 , 0);

	//*/
}
Texture2D::~Texture2D()
{
	glDeleteBuffers( 1, &vertexBuffer );
	glDeleteTextures(1, &texture);
}
void Texture2D::Draw(float x, float y)
{
	MakeProgramActive(NULL);

	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::width-1.0f, (float)GameWindow::height-1.0f, 1.0f);

	//make new translation matrix
	modelviewMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));

	glUniformMatrix4fv( uniTransformMatrix, 1, GL_FALSE, glm::value_ptr(modelviewMatrix));

	this->Draw();
}
void Texture2D::Draw(float x, float y, float scaleX, float scaleY)
{
	MakeProgramActive(NULL);


	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::width-1.0f, (float)GameWindow::height-1.0f, 1.0f);

	//make new translation matrix
	modelviewMatrix = glm::translate(projectionMatrix, glm::vec3(x + width*scaleX/2.0f, y + height*scaleY / 2.0f, 1));

	//scale the coordinates up by the specified amounts
	modelviewMatrix = glm::scale(modelviewMatrix, glm::vec3(scaleX, scaleY, 1.0));


	glUniformMatrix4fv( uniTransformMatrix, 1, GL_FALSE, glm::value_ptr(modelviewMatrix));

	this->Draw();

}
void Texture2D::Draw(float x, float y, float rotationAngle)
{
	MakeProgramActive(NULL);

	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::width-1.0f, (float)GameWindow::height-1.0f, 1.0f);

	//make new translation matrix
	modelviewMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));

	modelviewMatrix = glm::rotate(modelviewMatrix, rotationAngle,glm::vec3(0,0,1));

	glUniformMatrix4fv( uniTransformMatrix, 1, GL_FALSE, glm::value_ptr(modelviewMatrix));

	this->Draw();
}
void Texture2D::Draw(float x, float y, float scaleX, float scaleY, float rotationAngle)
{
	MakeProgramActive(NULL);


	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::width-1.0f, (float)GameWindow::height-1.0f, 1.0f);

	//make new translation matrix
	modelviewMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));

	modelviewMatrix = glm::rotate(modelviewMatrix, rotationAngle,glm::vec3(0,0,1));


	glUniformMatrix4fv( uniTransformMatrix, 1, GL_FALSE, glm::value_ptr(modelviewMatrix));

	this->Draw();
}

void Texture2D::Draw(float x, float y, float scaleX, float scaleY, float rotationAngle, Color tintColor)
{
	MakeProgramActive(NULL);


	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::width-1.0f, (float)GameWindow::height-1.0f, 1.0f);

	//make new translation matrix
	modelviewMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));

	modelviewMatrix = glm::rotate(modelviewMatrix, rotationAngle,glm::vec3(0,0,1));

	//scale the coordinates up by the specified amounts
	modelviewMatrix = glm::scale(modelviewMatrix, glm::vec3(scaleX, scaleY, 1.0));

	glUniformMatrix4fv( uniTransformMatrix, 1, GL_FALSE, glm::value_ptr(modelviewMatrix));

	glUniform3f(uniTint, tintColor.R/255.0f,tintColor.G/255.0f,tintColor.B/255.0f);
	this->Draw();
}


void Texture2D::Draw(float x, float y, Rectangle* sourceRect)
{
	MakeProgramActive(sourceRect);

	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::width-1.0f, (float)GameWindow::height-1.0f, 1.0f);

	//make new translation matrix
	modelviewMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));


	glUniformMatrix4fv( uniTransformMatrix, 1, GL_FALSE, glm::value_ptr(modelviewMatrix));


	this->Draw(sourceRect);
}
void Texture2D::Draw(float x, float y, Rectangle* sourceRect, float scaleX, float scaleY)
{
	MakeProgramActive(sourceRect);


	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::width-1.0f, (float)GameWindow::height-1.0f, 1.0f);

	//make new translation matrix
	modelviewMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));

	//scale the coordinates up by the specified amounts
	modelviewMatrix = glm::scale(modelviewMatrix, glm::vec3(scaleX, scaleY, 1.0));

	glUniformMatrix4fv( uniTransformMatrix, 1, GL_FALSE, glm::value_ptr(modelviewMatrix));

	this->Draw(sourceRect);
}
void Texture2D::Draw(float x, float y, Rectangle* sourceRect, float rotationAngle)
{
	MakeProgramActive(sourceRect);


	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::width-1.0f, (float)GameWindow::height-1.0f, 1.0f);

	//make new translation matrix
	modelviewMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));

	modelviewMatrix = glm::rotate(modelviewMatrix, rotationAngle,glm::vec3(0,0,1));

	glUniformMatrix4fv( uniTransformMatrix, 1, GL_FALSE, glm::value_ptr(modelviewMatrix));


	this->Draw(sourceRect);
}
void Texture2D::Draw(float x, float y, Rectangle* sourceRect, float scaleX, float scaleY, float rotationAngle)
{
	MakeProgramActive(sourceRect);



	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::width-1.0f, (float)GameWindow::height-1.0f, 1.0f);

	//make new translation matrix
	modelviewMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));

	modelviewMatrix = glm::rotate(modelviewMatrix, rotationAngle,glm::vec3(0,0,1));

	//scale the coordinates up by the specified amounts
	modelviewMatrix = glm::scale(modelviewMatrix, glm::vec3(scaleX, scaleY, 1.0));

	glUniformMatrix4fv( uniTransformMatrix, 1, GL_FALSE, glm::value_ptr(modelviewMatrix));


	this->Draw(sourceRect);
}

void Texture2D::Draw(float x, float y, Rectangle* sourceRect, float scaleX, float scaleY, float rotationAngle, Color tintColor)
{

	MakeProgramActive(sourceRect);

	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::width-1.0f, (float)GameWindow::height-1.0f, 1.0f);

	//make new translation matrix
	modelviewMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));

	modelviewMatrix = glm::rotate(modelviewMatrix, rotationAngle,glm::vec3(0,0,1));

	//scale the coordinates up by the specified amounts
	modelviewMatrix = glm::scale(modelviewMatrix, glm::vec3(scaleX, scaleY, 1.0));

	glUniformMatrix4fv( uniTransformMatrix, 1, GL_FALSE, glm::value_ptr(modelviewMatrix));

	glUniform3f(uniTint, tintColor.R/255.0f,tintColor.G/255.0f,tintColor.B/255.0f);


	this->Draw(sourceRect);
}


void Texture2D::Draw(Rectangle* sourceRect)
{
	//MakeProgramActive(sourceRect);
	GLfloat box[6][4] = {

		{-width/2.0f,   height /2.0f, 0, 0},
		{width/2.0f,   height /2.0f, 1, 0},
		{width/2.0f,  -height /2.0f, 1, 1},
		
		{width/2.0f,  -height /2.0f, 1, 1},
		{-width/2.0f,  -height /2.0f, 0, 1},
		{-width/2.0f,   height /2.0f, 0, 0}
		//*/
    };
	glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
		
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableVertexAttribArray(this->attribute_coord);
}
void Texture2D::Draw()
{
	Rectangle* sourceRect = new Rectangle(0,0,width,height);

	//MakeProgramActive(NULL);
	GLfloat box[6][4] = {

		{-width/2.0f,   height /2.0f, 0, 0},
		{width/2.0f,   height /2.0f, 1, 0},
		{width/2.0f,  -height /2.0f, 1, 1},
		
		{width/2.0f,  -height /2.0f, 1, 1},
		{-width/2.0f,  -height /2.0f, 0, 1},
		{-width/2.0f,   height /2.0f, 0, 0}
		//*/
    };
	glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
		
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableVertexAttribArray(this->attribute_coord);

	delete sourceRect;
}
void Texture2D::MakeProgramActive(Rectangle* sourceRect)
{
	glUseProgram(shaderProgram);


	glUniform3f(uniTint, 1.0f, 1.0f, 1.0f);


	glBindTexture(GL_TEXTURE_2D, texture);
	
	glEnableVertexAttribArray(this->attribute_coord);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(this->attribute_coord, 4, GL_FLOAT, GL_FALSE, 0 , 0);
}