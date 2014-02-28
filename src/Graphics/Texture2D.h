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
#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GL/FreeImage.h>
#include "Color.h"
#include "GameWindow.h"
#include "../Rectangle.h"
namespace MINX
{
	namespace Graphics
	{
		/** A Sprite class that take a texture and draws it to the screen
		*/
		class Texture2D
		{
		public:
			/** Creates a new Texture2D object
			*	@param fileLoc The file to load the texture from.
			*/
			Texture2D(char* fileLoc);
			/** Creates a new Texture2D object
			*	@param texData An array of Colors to create the texture as
			*	@param width The Width of the Texture
			*	@param height The Height of the Texture
			*/
			Texture2D(Color* texData, int width, int height);
			/** Safely destroys a Texture2D object
			*/
			~Texture2D();
			/** The Width of the Texture
			*/
			inline int GetWidth() { return width; }
			/** The Height of the Texture
			*/
			inline int GetHeight() { return height; }
			/** An unsigned integer representing the address of the texture in OpenGL's texture system
			*/
			GLuint texture;
		private:	
			int width;
			int height;
		};

	}

}
#endif