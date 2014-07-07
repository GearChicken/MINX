
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
#include "ShaderFactory.h"
using namespace MINX;
using namespace MINX::Graphics;

ShaderFactory* ShaderFactory::instance = NULL;

ShaderFactory::ShaderFactory()
{
	shaderPrograms = std::vector<GLuint>();

	std::string vertexSource =
		"#version 120\n"
		"attribute vec4 coord;"
		"varying vec2 texpos;"
		"uniform mat4 trans;"
		"void main()"
		"{"
		"	texpos = coord.zw;" 
		"	gl_Position = trans * vec4(coord.xy, 0.0, 1.0);"
		"}";
	std::string fragmentSource =
		"#version 120\n"
		"varying vec2 texpos;"
		"uniform sampler2D tex;"
		"uniform vec4 color;"
		"void main()"
		"{"
		"	gl_FragColor = texture2D(tex, texpos) * color;"
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
