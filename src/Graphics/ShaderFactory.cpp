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
#include "ShaderFactory.h"
using namespace MINX;
using namespace MINX::Graphics;

ShaderFactory* ShaderFactory::instance = NULL;

ShaderFactory::ShaderFactory()
{
	shaderPrograms = std::vector<GLuint>();

	std::string vertexSource =
		"#version 120\n"
		"attribute vec4 position;"
		"attribute vec2 texcoord;"
		"attribute vec4 tint;"
		"varying vec2 texCoord;"
		"varying vec4 tintColor;"
		"uniform mat4 projMat;"
		"void main()"
		"{"
		"    gl_Position = position;"
		"    texCoord = texcoord;"
		"    tintColor = tint;"
		"}";
	std::string fragmentSource =
		"#version 120\n"
		"uniform sampler2D tex;"
		"varying vec2 texCoord;"
		"varying vec4 tintColor;"
		"void main()"
		"{"
		"    gl_FragColor = texture2D(tex, texCoord) * tintColor;"
		"}";
	LoadShader(vertexSource, fragmentSource);

	std::string fontVertexSource =
		"#version 120\n"
		"attribute vec4 coord;"
		"varying vec2 texpos;"
		"void main()"
		"{"
		"	gl_Position = vec4(coord.xy, 0.0, 1.0);"
		"	texpos = coord.zw;" 
		"}";

	std::string fontFragmentSource =
		"#version 120\n"
		"varying vec2 texpos;"
		"uniform sampler2D tex;"
		"uniform vec4 color;"
		"void main()"
		"{"
		"	gl_FragColor = vec4(1,1,1,texture2D(tex, texpos).a)* color;"
		"}";

	LoadShader(fontVertexSource, fontFragmentSource);

}

ShaderFactory* ShaderFactory::GetInstance()
{
	if(instance == NULL)
	{
		instance = new ShaderFactory();
	}
	return instance;
}

std::string loadFileToString(char* fileLocation)
{
	//Load in the file
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	//Make sure the file loaded in
	if(!fileStream.is_open())
	{
		std::cout << "Could not read file: " << fileLocation << " File does NOT Exist" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::string line = "";

	//Get every line of the file
	while(!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	// return a string with the files contents
	fileStream.close();
	return content;
}

void ShaderFactory::LoadShaderFromFile(char* vertexLocation, char* fragmentLocation)
{
	this->LoadShader(loadFileToString(vertexLocation), loadFileToString(fragmentLocation));
}

void ShaderFactory::LoadShader(std::string vertexSource, std::string fragmentSource)
{
	//Convert the vertexShader string to a c-string and print it to console
	const char* vertexChars = vertexSource.c_str();
	std::cout << vertexChars << "\n\n";


	//Create a vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Give the shader the proper source code and compile it
	glShaderSource(vertexShader, 1, &vertexChars, NULL);
	glCompileShader(vertexShader);

	//Print out whether or not the shader compiled successfuly!
	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	std::cout << status << " Vertex Shader\n\n";

	GLint logLen;
	char* shaderLog;
	if(!status)
	{
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLen);

		shaderLog = new char[logLen+1];
		glGetShaderInfoLog(vertexShader, logLen, NULL, shaderLog);
		std::cout << "Shader Error Log:\n" << shaderLog << "\n\n";
		delete shaderLog;
	}


	//Convert the fragmentShader string to a c-string and print it to console
	const char* fragmentChars = fragmentSource.c_str();
	std::cout << fragmentChars << "\n\n";
	//Create a fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Give the shader the proper source code and compile it
	glShaderSource(fragmentShader, 1, &fragmentChars, NULL);
	glCompileShader(fragmentShader);


	//Print out whether or not the shader compiled successfuly!
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	std::cout << status << " Fragment Shader\n\n";

	if(!status)
	{
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLen);

		shaderLog = new char[logLen+1];
		glGetShaderInfoLog(fragmentShader, logLen, NULL, shaderLog);
		std::cout << "Shader Error Log:\n" << shaderLog << "\n" << std::endl;
		delete shaderLog;
	}
	//Create a full shader program and attach the vertex and fragment shaders to it
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	//Link the shader program together and add it to the vector of loaded shaders
	glLinkProgram(shaderProgram);
	shaderPrograms.push_back(shaderProgram);
}
