/*
# MINX

Copyright (c) 2013-2014 Liam Middlebrook, Benjamin Pylko

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

> 1\. The origin of this software must not be misrepresented; you must not
> claim that you wrote the original software. If you use this software
> in a product, an acknowledgment in the product documentation would be
> appreciated but is not required
>
> 2\. Altered source versions must be plainly marked as such, and must not be
> misrepresented as being the original software
>
> 3\. This notice may not be removed or altered from any source
> distribution
>
 */

#ifndef MINX_RENDERTARGET_HPP_
#define MINX_RENDERTARGET_HPP_

#include "../API.hpp"

#include <GL/glew.h>

#include "Texture2D.hpp"
#include "GameWindow.hpp"
#include "../Rectangle.hpp"

namespace MINX
{
	class MINX_API Game;

	namespace Graphics
	{
		/** Handles a framebuffer that can be switched to by using Game::SetRenderTarget()
		 */
		class MINX_API RenderTarget
		{
			public:
				/** Creates a RenderTarget with the specified width and height
				 */
				RenderTarget(int width, int height);

				/** Returns a pointer to a Texture2D containing the contents of this RenderTarget
				 */
				Texture2D* GetTexture();

				/** Returns the width of the RenderTarget
				 */
				inline int GetWidth() { return width; }

				/** Returns the height of the RenderTarget
				 */
				inline int GetHeight() { return height; }

				/** Clears the contents of the RenderTarget to the specified color
				 */
				void Clear(Color clearColor);

			private:
				int width, height;
				GLuint frameBuffer;
				GLuint frameBufferTex;
				Texture2D* texture;

			friend class MINX::Game;
		};

	}

}
#include "../Game.hpp"
#endif
