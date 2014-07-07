
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
#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H

#include "../API.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

#include <FreeImage.h>

#include "Color.h"
#include "GameWindow.h"
#include "../Rectangle.h"
namespace MINX
{
	namespace Graphics
	{
		/** A Sprite class that take a texture and draws it to the screen
		*/
		class MINX_API Texture2D
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

			Texture2D(GLuint texture, int width, int height);
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
		    void SavetoPNG(char* filename);
		private:	
			int width;
			int height;
		};

	}

}
#endif
