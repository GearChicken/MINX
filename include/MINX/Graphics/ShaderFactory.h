
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

#ifndef SHADER_FACTORY_H_
#define SHADER_FACTORY_H_

#include "../API.h"

#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <GL/glew.h>

namespace MINX
{
	namespace Graphics
	{
		/** A Singleton Class for Handling Shaders
		*/
		class MINX_API ShaderFactory
		{
		public:

			/** Returns the instance of ShaderFactory. If one does not exist, it creates one.
			*/
			static ShaderFactory* GetInstance();
			
			/** Load a Shader from Source
			*	@param vertexSource The source of the vertexShader
			*	@param fragmentSource The source of the fragmentShader
			*/
			void LoadShader(std::string vertexSource, std::string fragmentSource);

			/** Load a Shader from files
			*	@param vertexLocation The file location of the vertexShader
			*	@param fragmentLocation The file location of the fragmentShader
			*/
			void LoadShaderFromFile(char* vertexLocation, char* fragmentLocation);
			
			/** Returns the Shader Program at the specified index
			*	@param index The index of the shader program to return
			*/
			inline GLuint GetShaderAtIndex(int index) { return shaderPrograms.at(index); };
		private:
			ShaderFactory();
			static ShaderFactory* instance;
			std::vector<GLuint> shaderPrograms;
		};
	}
}

#endif
