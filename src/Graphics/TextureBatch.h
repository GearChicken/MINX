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
#ifndef _TEXTUREBATCH_H
#define _TEXTUREBATCH_H

#include "Texture2D.h"
#include <vector>

namespace MINX
{
	namespace Graphics
	{
		/** A struct that is used to store the instance data of a texture to be drawn
		 */
		struct TextureData
		{
			GLuint texture;
			int width;
			int height;
			Color color;
			glm::mat4  matrix;
			Rectangle sourceRect;
		};

		/** A batching system for drawing Texture2D's to the screen. Batches can use different shaders
		 */
		class TextureBatch
		{

		public:
			
			/** Creates a new TextureBatch object
			*	@param shaderProgram The GLSL program to draw the batched textures with.
			*/
			TextureBatch(GLuint shaderProgram);
			
			/** Draws the batched textures to the screen
			*/
			void DrawLoadedTextures();

			
			/** Adds the texture to the list of texture instances to draw to the screen.
			*	@param texture The texture to draw the the screen
			*	@param x The X value to draw the texture to on the screen.
			*	@param y the Y value to draw the texture to on the screen.
			*/
			void Draw(Texture2D* texture, float x, float y);

			/** Adds the texture to the list of texture instances to draw to the screen.
			*	@param texture The texture to draw the the screen
			*	@param x The X value to draw the texture to on the screen.
			*	@param y the Y value to draw the texture to on the screen.
			*	@param sourceRect The Source Rectangle for Texture Clipping
			*/
			void Draw(Texture2D* texture, float x, float y, Rectangle sourceRectangle);
			
			/** Adds the texture to the list of texture instances to draw to the screen.
			*	@param texture The texture to draw the the screen
			*	@param x The X value to draw the texture to on the screen.
			*	@param y the Y value to draw the texture to on the screen.
			*	@param rotation The value in radians to rotate the texture by. The origin is the center of the texture.
			*/
			void Draw(Texture2D* texture, float x, float y, float rotation);

			/** Adds the texture to the list of texture instances to draw to the screen.
			*	@param texture The texture to draw the the screen
			*	@param x The X value to draw the texture to on the screen.
			*	@param y the Y value to draw the texture to on the screen.
			*	@param rotation The value in radians to rotate the texture by. The origin is the center of the texture.
			*	@param sourceRect The Source Rectangle for Texture Clipping
			*/
			void Draw(Texture2D* texture, float x, float y, float rotation, Rectangle sourceRectangle);

			/** Adds the texture to the list of texture instances to draw to the screen.
			*	@param texture The texture to draw the the screen
			*	@param x The X value to draw the texture to on the screen.
			*	@param y the Y value to draw the texture to on the screen.
			*	@param scaleX The amount to horizontally scale the texture by.
			*	@param scaleY The amount to vertically scale the texture by.
			*/
			void Draw(Texture2D* texture, float x, float y, float scaleX, float scaleY);

			/** Adds the texture to the list of texture instances to draw to the screen.
			*	@param texture The texture to draw the the screen
			*	@param x The X value to draw the texture to on the screen.
			*	@param y the Y value to draw the texture to on the screen.
			*	@param scaleX The amount to horizontally scale the texture by.
			*	@param scaleY The amount to vertically scale the texture by.
			*	@param sourceRect The Source Rectangle for Texture Clipping
			*/
			void Draw(Texture2D* texture, float x, float y, float scaleX, float scaleY, Rectangle sourceRectangle);
			
			/** Adds the texture to the list of texture instances to draw to the screen.
			*	@param texture The texture to draw the the screen
			*	@param x The X value to draw the texture to on the screen.
			*	@param y the Y value to draw the texture to on the screen.
			*	@param scaleX The amount to horizontally scale the texture by.
			*	@param scaleY The amount to vertically scale the texture by.
			*	@param rotation The value in radians to rotate the texture by. The origin is the center of the texture.
			*/
			void Draw(Texture2D* texture, float x, float y, float scaleX, float scaleY, float rotation);
			
			/** Adds the texture to the list of texture instances to draw to the screen.
			*	@param texture The texture to draw the the screen
			*	@param x The X value to draw the texture to on the screen.
			*	@param y the Y value to draw the texture to on the screen.
			*	@param scaleX The amount to horizontally scale the texture by.
			*	@param scaleY The amount to vertically scale the texture by.
			*	@param rotation The value in radians to rotate the texture by. The origin is the center of the texture.
			*	@param sourceRect The Source Rectangle for Texture Clipping
			*/
			void Draw(Texture2D* texture, float x, float y, float scaleX, float scaleY, float rotation, Rectangle sourceRectangle);

			/** Adds the texture to the list of texture instances to draw to the screen.
			*	@param texture The texture to draw the the screen
			*	@param x The X value to draw the texture to on the screen.
			*	@param y the Y value to draw the texture to on the screen.
			*	@param scaleX The amount to horizontally scale the texture by.
			*	@param scaleY The amount to vertically scale the texture by.
			*	@param rotation The value in radians to rotate the texture by. The origin is the center of the texture.
			*	@param tint The color to tint the image to.
			*/
			void Draw(Texture2D* texture, float x, float y, float scaleX, float scaleY, float rotation, Color tint);

			/** Adds the texture to the list of texture instances to draw to the screen.
			*	@param texture The texture to draw the the screen
			*	@param x The X value to draw the texture to on the screen.
			*	@param y the Y value to draw the texture to on the screen.
			*	@param scaleX The amount to horizontally scale the texture by.
			*	@param scaleY The amount to vertically scale the texture by.
			*	@param rotation The value in radians to rotate the texture by. The origin is the center of the texture.
			*	@param tint The color to tint the image to.
			*	@param sourceRect The Source Rectangle for Texture Clipping
			*/
			void Draw(Texture2D* texture, float x, float y, float scaleX, float scaleY, float rotation, Color tint, Rectangle sourceRectangle);
			
			/** Adds the texture to the list of texture instances to draw to the screen.
			*	@param texture The texture to draw the the screen
			*	@param matrix The 4x4 Matrix to draw the texture with.
			*/
			void Draw(Texture2D* texture, glm::mat4 transformMatrix);
			
			/** Adds the texture to the list of texture instances to draw to the screen.
			*	@param texture The texture to draw the the screen
			*	@param matrix The 4x4 Matrix to draw the texture with.
			*	@param sourceRect The Source Rectangle for Texture Clipping
			*/
			void Draw(Texture2D* texture, glm::mat4 transformMatrix, Rectangle sourceRectangle);

			/** Adds the texture to the list of texture instances to draw to the screen.
			*	@param texture The texture to draw the the screen
			*	@param matrix The 4x4 Matrix to draw the texture with.
			*	@param tint The color to tint the image to.
			*/
			void Draw(Texture2D* texture, glm::mat4 transformMatrix, Color tint);

			/** Adds the texture to the list of texture instances to draw to the screen.
			*	@param texture The texture to draw the the screen
			*	@param matrix The 4x4 Matrix to draw the texture with.
			*	@param tint The color to tint the image to.
			*	@param sourceRect The Source Rectangle for Texture Clipping
			*/
			void Draw(Texture2D* texture, glm::mat4 transformMatrix, Color tint, Rectangle sourceRectangle);

			void DrawPrimitiveRectangle(Rectangle rectangle, Color tint);

		private:

			GLuint vertexBuffer;

			GLint attributeCoord;
			
			GLint uniformTint;

			GLint uniformTransformMatrix;

			GLint uniformTexture;

			GLuint shaderProgram;

			GLuint pixelTexture;

			std::vector<TextureData> texturesToDraw;
		};
	}
}

#endif