/*
    MINX - A C++ Graphics and Input Wrapper Library
    Copyright (C) 2014  MINX Team

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
#include "ShaderFactory.h"
using namespace MINX;
using namespace MINX::Graphics;

ShaderFactory* ShaderFactory::instance = NULL;

ShaderFactory::ShaderFactory()
{
	shaderPrograms = std::vector<GLuint>();

	std::string vertexSource = "#version 330\n"
		"in vec4 coord;"
		"out vec2 texpos;"
		"uniform mat4 trans;"
		"void main() {"
		"	texpos = coord.zw;" 
		"	gl_Position = trans * vec4(coord.xy, 0.0, 1.0);"
		"}";
	std::string fragmentSource =
		"#version 330\n"
		"in vec2 texpos;"
		"uniform sampler2D tex;"
		"uniform vec3 color;"
		"void main() {"
		"	gl_FragColor = texture(tex, texpos) * vec4(color,1.0);"
		"}";
	LoadShader(vertexSource, fragmentSource);

	std::string fontVertexSource =
		"#version 120\n"
		"attribute vec4 coord;"
		"varying vec2 texpos;"
		"void main() {"
		"	gl_Position = vec4(coord.xy, 0.0, 1.0);"
		"	texpos = coord.zw;" 
		"}";

	std::string fontFragmentSource =
		"#version 120\n"
		"varying vec2 texpos;"
		"uniform sampler2D tex;"
		"uniform vec4 color;"
		"void main() {"
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

std::string loadFileToCharArray(char* fileLocation)
{
	std::string content;
    std::ifstream fileStream(fileLocation, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << fileLocation << ". File does not exist." << std::endl;
		return "";
    }
    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
	return content;
}
void ShaderFactory::LoadShaderFromFile(char* vertexLocation, char* fragmentLocation)
{
	this->LoadShader(loadFileToCharArray(vertexLocation), loadFileToCharArray(fragmentLocation));
}
void ShaderFactory::LoadShader(std::string vertexSource, std::string fragmentSource)
{
	const char* vertexChars = vertexSource.c_str();
	const char* fragmentChars = fragmentSource.c_str();
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexChars, NULL);	//Create a new Vertex Shader and set it to the value of vertex source
	glCompileShader(vertexShader);	// compile the vertex shader

	GLint status;
	glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &status );
	//Check if the shader compiled succesfully
	
	std::cout << status << " Vertex Shader\n";

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentChars, NULL); //Create a new Fragment shader and set it to the value of fragment source
	glCompileShader(fragmentShader);	//compile the vertexShader
	
	glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &status );
	std::cout << status << " Fragment Shader\n";

	
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	
	glLinkProgram(shaderProgram);
	shaderPrograms.push_back(shaderProgram);
}