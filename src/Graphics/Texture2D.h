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
#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H
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
			*	@param shaderProgram The GLSL program that the Texture2D will use to draw.
			*	@param textures An array of GLuints that passes references to texture placeholders
			*	@param texID The index of the array of textures
			*/
			Texture2D(char* fileLoc, GLuint shaderProgram, GLuint* textures, int texID);
			~Texture2D();
			/** Draws the texture to the screen.
			*	@param x The X value to draw the texture to on the screen.
			*	@param y the Y value to draw the texture to on the screen.
			*/
			void Draw(float x, float y);
			/** Draws the texture to the screen.
			*	@param x The X value to draw the texture to on the screen.
			*	@param y the Y value to draw the texture to on the screen.
			*	@param rotation The value in radians to rotate the texture by. The origin is the center of the texture.
			*/
			void Draw(float x, float y, float rotation);
			/** Draws the texture to the screen.
			*	@param x The X value to draw the texture to on the screen.
			*	@param y the Y value to draw the texture to on the screen.
			*	@param scaleX The amount to horizontally scale the texture by.
			*	@param scaleY The amount to vertically scale the texture by.
			*/
			void Draw(float x, float y, float scaleX, float scaleY);
			/** Draws the texture to the screen.
			*	@param x The X value to draw the texture to on the screen.
			*	@param y the Y value to draw the texture to on the screen.
			*	@param scaleX The amount to horizontally scale the texture by.
			*	@param scaleY The amount to vertically scale the texture by.
			*	@param rotation The value in radians to rotate the texture by. The origin is the center of the texture.
			*/
			void Draw(float x, float y, float scaleX, float scaleY, float rotation);
			/** Draws the texture to the screen.
			*	@param x The X value to draw the texture to on the screen.
			*	@param y the Y value to draw the texture to on the screen.
			*	@param scaleX The amount to horizontally scale the texture by.
			*	@param scaleY The amount to vertically scale the texture by.
			*	@param rotation The value in radians to rotate the texture by. The origin is the center of the texture.
			*	@param tint The color to tint the image to.
			*/
			void Draw(float x, float y, float scaleX, float scaleY, float rotation, Color* tint);
			/** Draws the texture to the screen.
			*	@param x The X value to draw the texture to on the screen.
			*	@param y the Y value to draw the texture to on the screen.
			*	@param sourceRect The rectangle to get the pixelData from the texture.
			*/
			void Draw(float x, float y, MINX_Rectangle* sourceRect);
			/** Draws the texture to the screen.
			*	@param x The X value to draw the texture to on the screen.
			*	@param y the Y value to draw the texture to on the screen.
			*	@param sourceRect The rectangle to get the pixelData from the texture.
			*	@param rotation The value in radians to rotate the texture by. The origin is the center of the texture.
			*/
			void Draw(float x, float y, MINX_Rectangle* sourceRect, float rotation);
			/** Draws the texture to the screen.
			*	@param x The X value to draw the texture to on the screen.
			*	@param y the Y value to draw the texture to on the screen.
			*	@param sourceRect The rectangle to get the pixelData from the texture.
			*	@param scaleX The amount to horizontally scale the texture by.
			*	@param scaleY The amount to vertically scale the texture by.
			*	@param rotation The value in radians to rotate the texture by. The origin is the center of the texture.
			*/
			void Draw(float x, float y, MINX_Rectangle* sourceRect, float scaleX, float scaleY);
			/** Draws the texture to the screen.
			*	@param x The X value to draw the texture to on the screen.
			*	@param y the Y value to draw the texture to on the screen.
			*	@param sourceRect The rectangle to get the pixelData from the texture.
			*	@param scaleX The amount to horizontally scale the texture by.
			*	@param scaleY The amount to vertically scale the texture by.
			*	@param rotation The value in radians to rotate the texture by. The origin is the center of the texture.
			*/
			void Draw(float x, float y, MINX_Rectangle* sourceRect, float scaleX, float scaleY, float rotation);
			/** Draws the texture to the screen.
			*	@param x The X value to draw the texture to on the screen.
			*	@param y the Y value to draw the texture to on the screen.
			*	@param sourceRect The rectangle to get the pixelData from the texture.
			*	@param scaleX The amount to horizontally scale the texture by.
			*	@param scaleY The amount to vertically scale the texture by.
			*	@param rotation The value in radians to rotate the texture by. The origin is the center of the texture.
			*	@param tint The color to tint the image to.
			*/
			void Draw(float x, float y, MINX_Rectangle* sourceRect, float scaleX, float scaleY, float rotation, Color* tint);
		private:	
			void Draw();
			void Draw(MINX_Rectangle* sourceRect);
			double width;
			double height;
			float vertices[42];
			GLuint vertexBuffer;
			GLuint vertexArray;
			GLuint shaderProgram;
			GLint uniTransformMatrix;
			GLint uniViewMatrix;
			GLint uniProjectionMatrix;
			GLint uniTint;
			GLint uniSourceX;
			GLint uniSourceY;
			GLint uniRows;
			GLint uniColumns;
			int texID;
			GLuint* textures;
			glm::mat4 MINXCoordstoGLCoords(glm::mat4 trans);
			glm::mat4 ConvCoords(glm::vec4 coords);
			glm::mat4 modelMatrix;
			glm::mat4 viewMatrix;
			glm::mat4 projectionMatrix;
		};

	}

}
#endif