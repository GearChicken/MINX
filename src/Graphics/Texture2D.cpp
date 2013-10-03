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
Texture2D::Texture2D(char* fileLoc, GLuint shaderProgram, GLuint textures[], int texID)
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
	glBindTexture(GL_TEXTURE_2D, (textures)[texID]);
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

	 this->texID = texID;
	 this->textures = textures;
	//*/
}
Texture2D::~Texture2D()
{
	glDeleteBuffers( 1, &vertexBuffer );
	glDeleteVertexArrays( 1, &vertexArray );
}
void Texture2D::Draw(float x, float y)
{
	glm::mat4 trans;
	double wScale = width/GameWindow::width;
	//trans = glm::scale(trans, glm::vec3(1.0/width, 1.0/height, 1.0));
	//trans = glm::scale(trans, glm::vec3(width/GameWindow::width, height/GameWindow::height, 1.0));
	trans = glm::translate(trans, glm::vec3(x + width/2.0,y + height/2.0 ,0));
	glm::vec4 result = trans * glm::vec4(1,1,1,1);
	glm::mat4 finalMat = ConvCoords(result);
	finalMat = glm::scale(finalMat, glm::vec3(1.0*width/GameWindow::width, 1.0*height/GameWindow::height, 1.0));

	glUniformMatrix4fv( uniTrans, 1, GL_FALSE, glm::value_ptr(finalMat));
	//trans = MINXCoordstoGLCoords(trans);
	//glUniformMatrix4fv( uniTrans, 1, GL_FALSE, glm::value_ptr( trans ) );
	//glUniform3f(uniTint, .75,0,.75);
	this->Draw();
}
void Texture2D::Draw(float x, float y, float scaleX, float scaleY)
{
	glm::mat4 trans;
	trans = glm::scale(trans, glm::vec3(scaleX, scaleY, 1));
	trans = glm::translate(trans, glm::vec3(x,y,0));
	trans = MINXCoordstoGLCoords(trans);
	glUniformMatrix4fv( uniTrans, 1, GL_FALSE, glm::value_ptr( trans ) );
	//glUniform3f(uniTint, .75,0,.75);
	this->Draw();
}
void Texture2D::Draw(float x, float y, float rotationAngle)
{
	glm::mat4 trans;
	trans = glm::rotate(trans, rotationAngle,glm::vec3(1,1,0));
	trans = glm::translate(trans, glm::vec3(x,y,0));
	trans = MINXCoordstoGLCoords(trans);
	glUniformMatrix4fv( uniTrans, 1, GL_FALSE, glm::value_ptr( trans ) );
	//glUniform3f(uniTint, .75,0,.75);
	this->Draw();
}
void Texture2D::Draw(float x, float y, float scaleX, float scaleY, float rotationAngle)
{
	glm::mat4 trans;
	trans = glm::scale(trans, glm::vec3(scaleX, scaleY, 1));
	trans = glm::rotate(trans, rotationAngle,glm::vec3(1,1,0));
	trans = glm::translate(trans, glm::vec3(x,y,0));
	trans = MINXCoordstoGLCoords(trans);
	glUniformMatrix4fv( uniTrans, 1, GL_FALSE, glm::value_ptr( trans ) );
	//glUniform3f(uniTint, .75,0,.75);
	this->Draw();
}

void Texture2D::Draw(float x, float y, float scaleX, float scaleY, float rotationAngle, Color* tintColor)
{
	glm::mat4 trans;

	trans = glm::scale(trans, glm::vec3(scaleX, scaleY, 1));
	trans = glm::rotate(trans, rotationAngle,glm::vec3(0,0,1));
	trans = glm::translate(trans, glm::vec3(x,y,0));
	trans = MINXCoordstoGLCoords(trans);
	glUniformMatrix4fv( uniTrans, 1, GL_FALSE, glm::value_ptr( trans ) );
	glUniform3f(uniTint, tintColor->R/255.0f,tintColor->G/255.0f,tintColor->B/255.0f);
	this->Draw();
}


void Texture2D::Draw(float x, float y, MINX_Rectangle* sourceRect)
{

	//make new translation matrix
	glm::mat4 trans;//translate to the new xy coords, and add w/2 h/2 to switch origin to the top left
	trans = glm::translate(trans, glm::vec3(x + sourceRect->Width/2.0,y + sourceRect->Height/2.0 ,0));
	//convert matrix position to vec4
	glm::vec4 result = trans * glm::vec4(1,1,1,1);
	//convert coords to OpenGL style coords
	glm::mat4 finalMat = ConvCoords(result);
	//scale the matrix to compensate for the size of the image on the screen
	finalMat = glm::scale(finalMat, glm::vec3(1.0*sourceRect->Width/GameWindow::width, 1.0*sourceRect->Height/GameWindow::height, 1.0));

	glUniformMatrix4fv( uniTrans, 1, GL_FALSE, glm::value_ptr(finalMat));

	this->Draw(sourceRect);
}
void Texture2D::Draw(float x, float y, MINX_Rectangle* sourceRect, float scaleX, float scaleY)
{
	//make new translation matrix
	glm::mat4 trans;//translate to the new xy coords, and add w/2 h/2 to switch origin to the top left
	trans = glm::translate(trans, glm::vec3(x + sourceRect->Width/2.0,y + sourceRect->Height/2.0 ,0));
	//convert matrix position to vec4
	glm::vec4 result = trans * glm::vec4(1,1,1,1);
	//convert coords to OpenGL style coords
	glm::mat4 finalMat = ConvCoords(result);
	//scale the matrix to compensate for the size of the image on the screen
	finalMat = glm::scale(finalMat, glm::vec3(scaleX*sourceRect->Width/GameWindow::width, scaleY*sourceRect->Height/GameWindow::height, 1.0));

	glUniformMatrix4fv( uniTrans, 1, GL_FALSE, glm::value_ptr(finalMat));
	this->Draw(sourceRect);
}
void Texture2D::Draw(float x, float y, MINX_Rectangle* sourceRect, float rotationAngle)
{
	//make new translation matrix
	glm::mat4 trans;//translate to the new xy coords, and add w/2 h/2 to switch origin to the top left
	trans = glm::translate(trans, glm::vec3(x + sourceRect->Width/2.0,y + sourceRect->Height/2.0 ,0));
	//convert matrix position to vec4
	glm::vec4 result = trans * glm::vec4(1,1,1,1);
	//convert coords to OpenGL style coords
	glm::mat4 finalMat = ConvCoords(result);
	finalMat = glm::rotate(finalMat, rotationAngle,glm::vec3(0,0,1));
	//scale the matrix to compensate for the size of the image on the screen
	finalMat = glm::scale(finalMat, glm::vec3(1.0*sourceRect->Width/GameWindow::width, 1.0*sourceRect->Height/GameWindow::height, 1.0));
	glUniformMatrix4fv( uniTrans, 1, GL_FALSE, glm::value_ptr(finalMat));
	this->Draw(sourceRect);
}
void Texture2D::Draw(float x, float y, MINX_Rectangle* sourceRect, float scaleX, float scaleY, float rotationAngle)
{
	//make new translation matrix
	glm::mat4 trans;//translate to the new xy coords, and add w/2 h/2 to switch origin to the top left
	trans = glm::translate(trans, glm::vec3(x + sourceRect->Width/2.0,y + sourceRect->Height/2.0 ,0));
	//convert matrix position to vec4
	glm::vec4 result = trans * glm::vec4(1,1,1,1);
	//convert coords to OpenGL style coords
	glm::mat4 finalMat = ConvCoords(result);
	finalMat = glm::rotate(finalMat, rotationAngle,glm::vec3(1,1,0));
	//scale the matrix to compensate for the size of the image on the screen
	finalMat = glm::scale(finalMat, glm::vec3(scaleX*sourceRect->Width/GameWindow::width, scaleY*sourceRect->Height/GameWindow::height, 1.0));
	glUniformMatrix4fv( uniTrans, 1, GL_FALSE, glm::value_ptr(finalMat));
	this->Draw(sourceRect);
}

void Texture2D::Draw(float x, float y, MINX_Rectangle* sourceRect, float scaleX, float scaleY, float rotationAngle, Color* tintColor)
{
	//make new translation matrix
	glm::mat4 trans;//translate to the new xy coords, and add w/2 h/2 to switch origin to the top left
	trans = glm::translate(trans, glm::vec3(x + sourceRect->Width/2.0,y + sourceRect->Height/2.0 ,0));
	//convert matrix position to vec4
	glm::vec4 result = trans * glm::vec4(1,1,1,1);
	//convert coords to OpenGL style coords
	glm::mat4 finalMat = ConvCoords(result);
	finalMat = glm::rotate(finalMat, rotationAngle,glm::vec3(0,0,1));
	//scale the matrix to compensate for the size of the image on the screen
	finalMat = glm::scale(finalMat, glm::vec3(scaleX*sourceRect->Width/GameWindow::width, scaleY*sourceRect->Height/GameWindow::height, 1.0));
	glUniformMatrix4fv( uniTrans, 1, GL_FALSE, glm::value_ptr(finalMat));
	glUniform3f(uniTint, tintColor->R/255.0f,tintColor->G/255.0f,tintColor->B/255.0f);
	this->Draw(sourceRect);
}


void Texture2D::Draw(MINX_Rectangle* sourceRect)
{
	int columns = width / sourceRect->Width;
	int rows = height / sourceRect->Height;
	glUniform1f( uniSourceX, sourceRect->X / width);
	glUniform1f( uniSourceY, sourceRect->Y / height);
	glUniform1f( uniColumns, columns);
	glUniform1f( uniRows, rows);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, (textures)[texID]);
	glBindVertexArray(vertexArray);
	glDrawArrays(GL_TRIANGLES,0,6);
}
void Texture2D::Draw()
{
	glUniform1f( uniSourceX, 0.0);
	glUniform1f( uniSourceY, 0.0);
	glUniform1f( uniColumns, 1.0);
	glUniform1f( uniRows, 1.0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, (textures)[texID]);
	glBindVertexArray(vertexArray);
	glDrawArrays(GL_TRIANGLES,0,6);
}
glm::mat4 Texture2D::MINXCoordstoGLCoords(glm::mat4 trans)
{
	trans = glm::translate(trans, glm::vec3(-GameWindow::width/2.0, -GameWindow::height/2.0, 0.0));
	trans = glm::scale(trans, glm::vec3(1,-1,1.0));
	trans = glm::scale(trans, glm::vec3(2.0/GameWindow::width, 2.0/GameWindow::height, 1.0));
	glm::vec4 result = trans * glm::vec4(1.0,1.0,1.0,1.0);
	std::cout << "x: " << result.x << " y: " << result.y << std::endl;
	return trans;
}
glm::mat4 Texture2D::ConvCoords(glm::vec4 coords)
{
	glm::mat4 trans;
	coords.x +=-GameWindow::width/2.0;
	coords.y +=-GameWindow::height/2.0;
	coords.x *= 2.0/GameWindow::width;
	coords.y *= -(2.0/GameWindow::height);
	std::cout << "x: " << coords.x << " y: " << coords.y << std::endl;
	return glm::translate(trans,glm::vec3(coords.x, coords.y, coords.z));
}