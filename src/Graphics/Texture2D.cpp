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
		FIBITMAP* bitmap = FreeImage_Load(
			FreeImage_GetFileType(fileLoc, 0),
			fileLoc);
		FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);

		int nWidth = FreeImage_GetWidth(pImage);
		int nHeight = FreeImage_GetHeight(pImage);
		this->width = nWidth;
		this->height = nHeight;
	float tempVertices[] = {
	-nWidth/2.0f,   nHeight /2.0f,		 1.0f, 1.0f, 1.0f,		0.0f, 1.0f, // Top-left
     nWidth/2.0f,   nHeight /2.0f,		 1.0f, 1.0f, 1.0f,		1.0f, 1.0f,// Top-right
     nWidth/2.0f,  -nHeight /2.0f,		 1.0f, 1.0f, 1.0f,		1.0f, 0.0f,// Bottom-right
			   
     nWidth/2.0f,  -nHeight /2.0f,		 1.0f, 1.0f, 1.0f,		1.0f, 0.0f,// Bottom-right
    -nWidth/2.0f,  -nHeight /2.0f,		 1.0f, 1.0f, 1.0f,		0.0f, 0.0f,// Bottom-left
    -nWidth/2.0f,   nHeight /2.0f,		 1.0f, 1.0f, 1.0f,		0.0f, 1.0f// Top-left
	};

	for(int i =0 ; i < sizeof(vertices) / sizeof(float); i++)
	{
		vertices[i] =  tempVertices[i];
	}
	glGenTextures(1, &texture);
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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
			0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

		FreeImage_Unload(pImage);
	//END IMAGE LOADING);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glGenerateMipmap(GL_TEXTURE_2D);
	
	 uniTransformMatrix = glGetUniformLocation( shaderProgram, "trans" );
	 uniSourceX = glGetUniformLocation( shaderProgram, "sourceX" );
	 uniSourceY = glGetUniformLocation( shaderProgram, "sourceY" );
	 uniRows = glGetUniformLocation( shaderProgram, "rows" );
	 uniColumns = glGetUniformLocation( shaderProgram, "columns" );
	 uniTint = glGetUniformLocation(shaderProgram, "tint");

	glUniform3f(uniTint, 1.0f, 1.0f, 1.0f);
	//*/
}
Texture2D::Texture2D(void* pixelData, int nWidth, int nHeight, GLint format, GLuint shaderProgram)
{
	float tempVertices[] = {
	-nWidth/2.0f,   nHeight /2.0f,		 1.0f, 1.0f, 1.0f,		0.0f, 1.0f, // Top-left
     nWidth/2.0f,   nHeight /2.0f,		 1.0f, 1.0f, 1.0f,		1.0f, 1.0f,// Top-right
     nWidth/2.0f,  -nHeight /2.0f,		 1.0f, 1.0f, 1.0f,		1.0f, 0.0f,// Bottom-right
			   
     nWidth/2.0f,  -nHeight /2.0f,		 1.0f, 1.0f, 1.0f,		1.0f, 0.0f,// Bottom-right
    -nWidth/2.0f,  -nHeight /2.0f,		 1.0f, 1.0f, 1.0f,		0.0f, 0.0f,// Bottom-left
    -nWidth/2.0f,   nHeight /2.0f,		 1.0f, 1.0f, 1.0f,		0.0f, 1.0f// Top-left
	};

	for(int i =0 ; i < sizeof(vertices) / sizeof(float); i++)
	{
		vertices[i] =  tempVertices[i];
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &texture);
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

		this->width = nWidth;
		this->height = nHeight;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, nWidth, nHeight,
			0, GL_ALPHA, GL_UNSIGNED_BYTE, pixelData);

	//END IMAGE LOADING);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glGenerateMipmap(GL_TEXTURE_2D);
	
	 uniTransformMatrix = glGetUniformLocation( shaderProgram, "trans" );
	 uniSourceX = glGetUniformLocation( shaderProgram, "sourceX" );
	 uniSourceY = glGetUniformLocation( shaderProgram, "sourceY" );
	 uniRows = glGetUniformLocation( shaderProgram, "rows" );
	 uniColumns = glGetUniformLocation( shaderProgram, "columns" );
	 uniTint = glGetUniformLocation(shaderProgram, "tint");
	 
	glUniform3f(uniTint, 1.0f, 1.0f, 1.0f);
	//*/
}
Texture2D::Texture2D(void* pixelData, int nWidth, int nHeight, GLint format, GLuint shaderProgram)
{
	float tempVertices[] = {
	-08.0f,  08.0f,		 1.0f, 1.0f, 1.0f,		0.0f, 1.0f, // Top-left
     08.0f,  08.0f,		 1.0f, 1.0f, 1.0f,		1.0f, 1.0f,// Top-right
     08.0f, -08.0f,		 1.0f, 1.0f, 1.0f,		1.0f, 0.0f,// Bottom-right
			   
     08.0f, -08.0f,		 1.0f, 1.0f, 1.0f,		1.0f, 0.0f,// Bottom-right
    -08.0f, -08.0f,		 1.0f, 1.0f, 1.0f,		0.0f, 0.0f,// Bottom-left
    -08.0f,  08.0f,		 1.0f, 1.0f, 1.0f,		0.0f, 1.0f// Top-left
	};

	for(int i =0 ; i < sizeof(vertices) / sizeof(float); i++)
	{
		vertices[i] =  tempVertices[i];
	}
	glGenTextures(1, &texture);
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

		this->width = nWidth;
		this->height = nHeight;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, nWidth, nHeight,
			0, GL_ALPHA, GL_UNSIGNED_BYTE, pixelData);

	//END IMAGE LOADING);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glGenerateMipmap(GL_TEXTURE_2D);
	
	 uniTransformMatrix = glGetUniformLocation( shaderProgram, "trans" );
	 uniSourceX = glGetUniformLocation( shaderProgram, "sourceX" );
	 uniSourceY = glGetUniformLocation( shaderProgram, "sourceY" );
	 uniRows = glGetUniformLocation( shaderProgram, "rows" );
	 uniColumns = glGetUniformLocation( shaderProgram, "columns" );
	 uniTint = glGetUniformLocation(shaderProgram, "tint");
	//*/
}
Texture2D::~Texture2D()
{
	glDeleteBuffers( 1, &vertexBuffer );
	glDeleteVertexArrays( 1, &vertexArray );
	glDeleteTextures(1, &texture);
}
void Texture2D::Draw(float x, float y)
{
	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::width-1.0f, (float)GameWindow::height-1.0f, 1.0f);
	
	//make new translation matrix
	modelviewMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));
	modelviewMatrix = glm::scale(modelviewMatrix, glm::vec3(1.0f, -1.0f, 1.0f));

	glUniformMatrix4fv( uniTransformMatrix, 1, GL_FALSE, glm::value_ptr(modelviewMatrix));

	this->Draw();
}
void Texture2D::Draw(float x, float y, float scaleX, float scaleY)
{
	
	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::width-1.0f, (float)GameWindow::height-1.0f, 1.0f);
	
	//make new translation matrix
	modelviewMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));
	
	//scale the coordinates up by the specified amounts
	modelviewMatrix = glm::scale(modelviewMatrix, glm::vec3(scaleX, -scaleY, 1.0));
	
	glUniformMatrix4fv( uniTransformMatrix, 1, GL_FALSE, glm::value_ptr(modelviewMatrix));

	this->Draw();

}
void Texture2D::Draw(float x, float y, float rotationAngle)
{
	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::width-1.0f, (float)GameWindow::height-1.0f, 1.0f);
	
	//make new translation matrix
	modelviewMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));

	modelviewMatrix = glm::rotate(modelviewMatrix, rotationAngle,glm::vec3(0,0,1));
	modelviewMatrix = glm::scale(modelviewMatrix, glm::vec3(1.0f, -1.0f, 1.0f));

	glUniformMatrix4fv( uniTransformMatrix, 1, GL_FALSE, glm::value_ptr(modelviewMatrix));

	this->Draw();
}
void Texture2D::Draw(float x, float y, float scaleX, float scaleY, float rotationAngle)
{
	
	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::width-1.0f, (float)GameWindow::height-1.0f, 1.0f);
	
	//make new translation matrix
	modelviewMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));

	modelviewMatrix = glm::rotate(modelviewMatrix, rotationAngle,glm::vec3(0,0,1));

	//scale the coordinates up by the specified amounts
	modelviewMatrix = glm::scale(modelviewMatrix, glm::vec3(scaleX, scaleY, 1.0));

	glUniformMatrix4fv( uniTransformMatrix, 1, GL_FALSE, glm::value_ptr(modelviewMatrix));

	this->Draw();
}

void Texture2D::Draw(float x, float y, float scaleX, float scaleY, float rotationAngle, Color* tintColor)
{
	
	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::width-1.0f, (float)GameWindow::height-1.0f, 1.0f);
	
	//make new translation matrix
	modelviewMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));

	modelviewMatrix = glm::rotate(modelviewMatrix, rotationAngle,glm::vec3(0,0,1));

	//scale the coordinates up by the specified amounts
	modelviewMatrix = glm::scale(modelviewMatrix, glm::vec3(scaleX, -scaleY, 1.0));

	glUniformMatrix4fv( uniTransformMatrix, 1, GL_FALSE, glm::value_ptr(modelviewMatrix));

	glUniform3f(uniTint, tintColor->R/255.0f,tintColor->G/255.0f,tintColor->B/255.0f);
	this->Draw();
}


void Texture2D::Draw(float x, float y, Rectangle* sourceRect)
{
	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::width-1.0f, (float)GameWindow::height-1.0f, 1.0f);
	
	//make new translation matrix
	modelviewMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));
	modelviewMatrix = glm::scale(modelviewMatrix, glm::vec3(1.0f, -1.0f, 1.0f));


	glUniformMatrix4fv( uniTransformMatrix, 1, GL_FALSE, glm::value_ptr(modelviewMatrix));


	this->Draw(sourceRect);
}
void Texture2D::Draw(float x, float y, Rectangle* sourceRect, float scaleX, float scaleY)
{
	
	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::width-1.0f, (float)GameWindow::height-1.0f, 1.0f);
	
	//make new translation matrix
	modelviewMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));
	
	//scale the coordinates up by the specified amounts
	modelviewMatrix = glm::scale(modelviewMatrix, glm::vec3(scaleX, -scaleY, 1.0));
	
	glUniformMatrix4fv( uniTransformMatrix, 1, GL_FALSE, glm::value_ptr(modelviewMatrix));

	this->Draw(sourceRect);
}
void Texture2D::Draw(float x, float y, Rectangle* sourceRect, float rotationAngle)
{
	
	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::width-1.0f, (float)GameWindow::height-1.0f, 1.0f);
	
	//make new translation matrix
	modelviewMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));

	modelviewMatrix = glm::rotate(modelviewMatrix, rotationAngle,glm::vec3(0,0,1));
	modelviewMatrix = glm::scale(modelviewMatrix, glm::vec3(1.0f, -1.0f, 1.0f));

	glUniformMatrix4fv( uniTransformMatrix, 1, GL_FALSE, glm::value_ptr(modelviewMatrix));


	this->Draw(sourceRect);
}
void Texture2D::Draw(float x, float y, Rectangle* sourceRect, float scaleX, float scaleY, float rotationAngle)
{
	
	
	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::width-1.0f, (float)GameWindow::height-1.0f, 1.0f);
	
	//make new translation matrix
	modelviewMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));

	modelviewMatrix = glm::rotate(modelviewMatrix, rotationAngle,glm::vec3(0,0,1));

	//scale the coordinates up by the specified amounts
	modelviewMatrix = glm::scale(modelviewMatrix, glm::vec3(scaleX, -scaleY, 1.0));

	glUniformMatrix4fv( uniTransformMatrix, 1, GL_FALSE, glm::value_ptr(modelviewMatrix));


	this->Draw(sourceRect);
}

void Texture2D::Draw(float x, float y, Rectangle* sourceRect, float scaleX, float scaleY, float rotationAngle, Color* tintColor)
{
	
	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::width-1.0f, (float)GameWindow::height-1.0f, 1.0f);
	
	//make new translation matrix
	modelviewMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));

	modelviewMatrix = glm::rotate(modelviewMatrix, rotationAngle,glm::vec3(0,0,1));

	//scale the coordinates up by the specified amounts
	modelviewMatrix = glm::scale(modelviewMatrix, glm::vec3(scaleX, -scaleY, 1.0));

	glUniformMatrix4fv( uniTransformMatrix, 1, GL_FALSE, glm::value_ptr(modelviewMatrix));

	glUniform3f(uniTint, tintColor->R/255.0f,tintColor->G/255.0f,tintColor->B/255.0f);


	this->Draw(sourceRect);
}


void Texture2D::Draw(Rectangle* sourceRect)
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
void Texture2D::Draw()
{ 
	Rectangle* sourceRect = new Rectangle(0,0,width,height);

	glUniform1f( uniSourceX, 0.0);
	glUniform1f( uniSourceY, 0.0);
	glUniform1f( uniColumns, 1.0);
	glUniform1f( uniRows, 1.0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(vertexArray);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	delete sourceRect;
}