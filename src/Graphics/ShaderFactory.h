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

#ifndef SHADER_FACTORY_H_
#define SHADER_FACTORY_H_

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
		class ShaderFactory
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
