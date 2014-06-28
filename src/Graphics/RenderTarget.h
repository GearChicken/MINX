/*
    MINX - A C++ Graphics and Input Wrapper Library
    Copyright (C) 2014  MINX Team

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
#ifndef _RENDER_TARGET_H_
#define _RENDER_TARGET_H_

#include "../API.h"

#include <GL/gl.h>
#include <GL/glew.h>

#include "Texture2D.h"
#include "../Rectangle.h"

namespace MINX
{
	class MINX_API Game;
	namespace Graphics
	{
		class MINX_API RenderTarget
		{
		public:
			RenderTarget(int width, int height);
			Texture2D* GetTexture();
			inline int GetWidth() { return width; }
			inline int GetHeight() { return height; }
		private:
			int width, height;
			GLuint frameBuffer;
			GLuint frameBufferTex;
			Texture2D* texture;
			friend class MINX::Game;
		};

	}

}
#include "../Game.h"
#endif
