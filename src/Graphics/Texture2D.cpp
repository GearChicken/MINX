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
#include "Texture2D.h"
#include <iostream>
using namespace MINX::Graphics;
using namespace MINX;

Texture2D::Texture2D(char* fileLoc)
{
	FIBITMAP* bitmap = FreeImage_Load(
		FreeImage_GetFileType(fileLoc, 0),
		fileLoc);
	FIBITMAP* pImage;
	if(!bitmap)
	{
		std::cout << "ERROR:\nImage: " << fileLoc << " failed to load!\n"
			"Replacing with default missing texture!" << std::endl;
	}
	else
	{
		pImage = FreeImage_ConvertTo32Bits(bitmap);

		this->width = FreeImage_GetWidth(pImage);
		this->height = FreeImage_GetHeight(pImage);
	}

	glActiveTexture( GL_TEXTURE0 );
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if(bitmap)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height,
			0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));
	}
	else
	{
		
		this->width = 1;
		this->height = 1;
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height,
			0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)NULL);
	}
	FreeImage_Unload(bitmap);
	FreeImage_Unload(pImage);

}

Texture2D::Texture2D(Color* texData, int width, int height)
{
	this->width = width;
	this->height = height;

	glActiveTexture( GL_TEXTURE0 );
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Convert the MINX::Graphics::Colors into GLubytes
	GLubyte* texelData = new GLubyte[width*height*4];
	for (int i = 0; i < width*height; ++i)
	{
		texelData[4*i+0] = (GLubyte)texData[i].R;
		texelData[4*i+1] = (GLubyte)texData[i].G;
		texelData[4*i+2] = (GLubyte)texData[i].B;
		texelData[4*i+3] = (GLubyte)texData[i].A;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, texelData);
	delete[] texelData;
}


Texture2D::Texture2D(GLuint texture, int width, int height)
{
	this->width = width;
	this->height=height;

	this->texture = texture;
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &texture);
}