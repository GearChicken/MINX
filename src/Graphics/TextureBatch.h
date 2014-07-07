
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
#ifndef _TEXTUREBATCH_H
#define _TEXTUREBATCH_H

#include "../API.h"

#include "Texture2D.h"
#include <vector>
#include "../MathHelper.h"
#include "../Vector2.h"
#include <iostream>

namespace MINX
{
	class MINX_API Game;
	namespace Graphics
	{
		/** A struct that is used to store the instance data of a texture to be drawn
		 */
		struct MINX_API BatchData
		{
			/** An unsigned integer representing the address of the texture in OpenGL's texture system
			 */
			GLuint texture;
			/** The color to tint the texture
			 */
			std::vector<GLfloat> posPoints;
			std::vector<GLfloat> texPoints;
			std::vector<GLfloat> tintPoints;
			int spriteCount;

			void AddPoint(Vector2 position, Vector2 texCoord);
			void AddTint(Color tint);
		};

		/** A batching system for drawing Texture2D's to the screen. Batches can use different shaders
		 */
		class MINX_API TextureBatch
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
			
			/** Adds a Rectangle with the specified Color to the list of texture instances to draw to the screen.
			 */
			void DrawPrimitiveRectangle(Rectangle rectangle, Color tint);

		private:
			
			GLuint vertexBuffer;
			GLuint tintBuffer;

			GLuint vertexArray;
			
			GLint posCoord;
			GLint texCoord;
			GLint tintCoord;
			
			GLint uniformTint;

			GLint uniformTransformMatrix;

			GLint uniformTexture;

			GLuint shaderProgram;

			GLuint pixelTexture;

			BatchData* GetBatchForTexture(GLuint texture);

			std::vector<BatchData*> batches;
		};
	}
}
#include "../Game.h"
#endif
