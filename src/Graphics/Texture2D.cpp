
/*
# MINX

Copyright (c) 2013-2014 Liam Middlebrook, Benjamin Pylko

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

> 1\. The origin of this software must not be misrepresented; you must not
> claim that you wrote the original software. If you use this software
> in a product, an acknowledgment in the product documentation would be
> appreciated but is not required.
>
> 2\. Altered source versions must be plainly marked as such, and must not be
> misrepresented as being the original software.
>
> 3\. This notice may not be removed or altered from any source
> distribution.
>
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

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if(bitmap)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height,
			0, GL_BGRA, GL_UNSIGNED_BYTE, static_cast<void*>(FreeImage_GetBits(pImage)));
	}
	else
	{

		this->width = 1;
		this->height = 1;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height,
			0, GL_BGRA, GL_UNSIGNED_BYTE, static_cast<void*>(NULL));
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
	GLubyte* texelData = new GLubyte[width * height * 4];
	for (int i = 0; i < width * height; ++i)
	{
		texelData[4 * i + 0] = static_cast<GLubyte>(texData[i].R);
		texelData[4 * i + 1] = static_cast<GLubyte>(texData[i].G);
		texelData[4 * i + 2] = static_cast<GLubyte>(texData[i].B);
		texelData[4 * i + 3] = static_cast<GLubyte>(texData[i].A);
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

void Texture2D::SavetoPNG(char* filename)
{
	float renderTargetWidth, renderTargetHeight;

	renderTargetWidth = static_cast<float>(width);
	renderTargetHeight = static_cast<float>(height);

	glBindTexture(GL_TEXTURE_2D, texture);

	const size_t bytesPerPixel = 4;	// RGBA

	const size_t imageSizeInBytes = bytesPerPixel * static_cast<size_t>(renderTargetWidth) * static_cast<size_t>(renderTargetHeight);
	BYTE* pixels = static_cast<BYTE*>(malloc(imageSizeInBytes));

	glPixelStorei(GL_PACK_ALIGNMENT, 1);


	glGetTexImage(GL_TEXTURE_2D, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
	FIBITMAP* bitmap;
	bitmap = FreeImage_ConvertFromRawBits(pixels, static_cast<int>(renderTargetWidth), static_cast<int>(renderTargetHeight), 4 * static_cast<int>(renderTargetWidth),
		32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, false);
	FreeImage_Save(FREE_IMAGE_FORMAT::FIF_PNG, bitmap, filename);
	free(pixels);
}
