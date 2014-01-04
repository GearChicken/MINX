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
#include "Texture2D.h"
#include <iostream>
using namespace MINX::Graphics;
using namespace MINX;

Texture2D::Texture2D(char* fileLoc)
{
	FIBITMAP* bitmap = FreeImage_Load(
		FreeImage_GetFileType(fileLoc, 0),
		fileLoc);
	FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);


	this->width = FreeImage_GetWidth(pImage);
	this->height = FreeImage_GetHeight(pImage);

	glActiveTexture( GL_TEXTURE0 );
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height,
		0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));
	FreeImage_Unload(bitmap);
	FreeImage_Unload(pImage);

}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &texture);
}