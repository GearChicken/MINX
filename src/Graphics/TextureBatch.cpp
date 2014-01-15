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

#include "TextureBatch.h"

using namespace MINX;
using namespace MINX::Graphics;

TextureBatch::TextureBatch(GLuint shaderProgram)
{
	this->shaderProgram= shaderProgram;
	texturesToDraw = std::vector<TextureData>();

	attributeCoord = glGetAttribLocation(shaderProgram, "coord");
	uniformTransformMatrix = glGetUniformLocation( shaderProgram, "trans" );
	uniformTint = glGetUniformLocation(shaderProgram, "color");
	uniformTexture = glGetUniformLocation(shaderProgram, "tex");

	glGenBuffers(1, &vertexBuffer);

	
	glActiveTexture( GL_TEXTURE0 );
	glGenTextures(1, &pixelTexture);
	glBindTexture(GL_TEXTURE_2D, pixelTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	byte texture[] = {
		255, 255, 255, 255
	};

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1,
		0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	//*/
}

void TextureBatch::DrawLoadedTextures()
{
	glUseProgram(shaderProgram);
	
	glUniform4f(uniformTint, 1.0f, 1.0f, 1.0f, 1.0f);
	
	glEnableVertexAttribArray(attributeCoord);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	
	glVertexAttribPointer(attributeCoord, 4, GL_FLOAT, GL_FALSE, 0 , 0);

	std::vector<TextureData>::iterator min = texturesToDraw.begin();
	std::vector<TextureData>::iterator max = texturesToDraw.end();

	for (auto textureToDraw : texturesToDraw)
	{
		
		glUniformMatrix4fv( uniformTransformMatrix, 1, GL_FALSE, glm::value_ptr(textureToDraw.matrix));
		//texturesToDraw[i]->width;
			glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureToDraw.texture);
		int texWidth = textureToDraw.width;
		int texHeight = textureToDraw.height;
		
		glUniform4f(uniformTint, textureToDraw.color.R/255.0f, textureToDraw.color.G/255.0f, textureToDraw.color.B/255.0f, textureToDraw.color.A/255.0f);
		
		float xMin, xMax, yMin, yMax;
		Rectangle sourceRect = textureToDraw.sourceRect;
		if(sourceRect.Width == 0 && sourceRect.Height == 0)
		{
			sourceRect.Width = texWidth;
			sourceRect.Height = texHeight;
		}
		xMin = (double)sourceRect.X / texWidth;
		xMax = (double)sourceRect.Right() / texWidth;
		yMin = (double)sourceRect.Y / texHeight;
		yMax = (double)sourceRect.Bottom() / texHeight;

		GLfloat box[6][4] = {

		{-texWidth/2.0f,   texHeight /2.0f, xMin, yMin},
		{texWidth/2.0f,   texHeight /2.0f, xMax, yMin},
		{texWidth/2.0f,  -texHeight /2.0f, xMax, yMax},
		
		{texWidth/2.0f,  -texHeight /2.0f, xMax, yMax},
		{-texWidth/2.0f,  -texHeight /2.0f, xMin, yMax},
		{-texWidth/2.0f,   texHeight /2.0f, xMin, yMin}
		//*/
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	texturesToDraw.clear();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableVertexAttribArray(attributeCoord);
}



void TextureBatch::Draw(Texture2D* texture, float x, float y)
{
	glm::mat4 projectionMatrix;
	int width = texture->GetWidth();
	int height = texture->GetHeight();
	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::GetWidth()-1.0f, (float)GameWindow::GetHeight()-1.0f, 1.0f);

	//make new translation matrix
	projectionMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));
	
	struct TextureData texData = TextureData();
	texData.texture = texture->texture;
	texData.width =  width;
	texData.height = height;
	texData.matrix = projectionMatrix;
	texData.color = Color(255,255,255);
	texturesToDraw.push_back(texData);
}

void TextureBatch::Draw(Texture2D* texture, float x, float y, Rectangle sourceRect)
{
	glm::mat4 projectionMatrix;
	int width = texture->GetWidth();
	int height = texture->GetHeight();
	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::GetWidth()-1.0f, (float)GameWindow::GetHeight()-1.0f, 1.0f);

	//make new translation matrix
	projectionMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));
	
	struct TextureData texData = TextureData();
	texData.texture = texture->texture;
	texData.width =  width;
	texData.height = height;
	texData.matrix = projectionMatrix;
	texData.color = Color(255,255,255);
	texData.sourceRect = sourceRect;
	texturesToDraw.push_back(texData);
}

void TextureBatch::Draw(Texture2D* texture, float x, float y, float scaleX, float scaleY)
{
	glm::mat4 projectionMatrix;
	int width = texture->GetWidth();
	int height = texture->GetHeight();


	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::GetWidth()-1.0f, (float)GameWindow::GetHeight()-1.0f, 1.0f);

	//make new translation matrix
	projectionMatrix = glm::translate(projectionMatrix, glm::vec3(x + abs(width*scaleX/2.0f), y + abs(height*scaleY / 2.0f), 1));

	//scale the coordinates up by the specified amounts
	projectionMatrix = glm::scale(projectionMatrix, glm::vec3(scaleX, scaleY, 1.0));

	
	struct TextureData texData = TextureData();
	texData.texture = texture->texture;
	texData.width =  width;
	texData.height = height;
	texData.matrix = projectionMatrix;
	texData.color = Color(255,255,255);
	texturesToDraw.push_back(texData);

}

void TextureBatch::Draw(Texture2D* texture, float x, float y, float scaleX, float scaleY, Rectangle sourceRect)
{
	glm::mat4 projectionMatrix;
	int width = texture->GetWidth();
	int height = texture->GetHeight();


	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::GetWidth()-1.0f, (float)GameWindow::GetHeight()-1.0f, 1.0f);
	
	//make new translation matrix
	projectionMatrix = glm::translate(projectionMatrix, glm::vec3(x + abs(width*scaleX/2.0f), y + abs(height*scaleY / 2.0f), 1));

	//scale the coordinates up by the specified amounts
	projectionMatrix = glm::scale(projectionMatrix, glm::vec3(scaleX, scaleY, 1.0));

	
	struct TextureData texData = TextureData();
	texData.texture = texture->texture;
	texData.width =  width;
	texData.height = height;
	texData.matrix = projectionMatrix;
	texData.color = Color(255,255,255);
	texData.sourceRect = sourceRect;
	texturesToDraw.push_back(texData);

}

void TextureBatch::Draw(Texture2D* texture, float x, float y, float rotationAngle)
{
	glm::mat4 projectionMatrix;
	int width = texture->GetWidth();
	int height = texture->GetHeight();

	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::GetWidth()-1.0f, (float)GameWindow::GetHeight()-1.0f, 1.0f);

	//make new translation matrix
	projectionMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));

	projectionMatrix = glm::rotate(projectionMatrix, rotationAngle,glm::vec3(0,0,1));
	
	struct TextureData texData = TextureData();
	texData.texture = texture->texture;
	texData.width =  width;
	texData.height = height;
	texData.matrix = projectionMatrix;
	texData.color = Color(255,255,255);
	texturesToDraw.push_back(texData);
}

void TextureBatch::Draw(Texture2D* texture, float x, float y, float rotationAngle, Rectangle sourceRect)
{
	glm::mat4 projectionMatrix;
	int width = texture->GetWidth();
	int height = texture->GetHeight();

	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::GetWidth()-1.0f, (float)GameWindow::GetHeight()-1.0f, 1.0f);

	//make new translation matrix
	projectionMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));

	projectionMatrix = glm::rotate(projectionMatrix, rotationAngle,glm::vec3(0,0,1));
	
	struct TextureData texData = TextureData();
	texData.texture = texture->texture;
	texData.width =  width;
	texData.height = height;
	texData.matrix = projectionMatrix;
	texData.color = Color(255,255,255);
	texData.sourceRect = sourceRect;
	texturesToDraw.push_back(texData);
}

void TextureBatch::Draw(Texture2D* texture, float x, float y, float scaleX, float scaleY, float rotationAngle)
{
	glm::mat4 projectionMatrix;
	int width = texture->GetWidth();
	int height = texture->GetHeight();


	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::GetWidth()-1.0f, (float)GameWindow::GetHeight()-1.0f, 1.0f);

	
	//make new translation matrix
	projectionMatrix = glm::translate(projectionMatrix, glm::vec3(x + abs(width*scaleX/2.0f), y + abs(height*scaleY / 2.0f), 1));

	projectionMatrix = glm::rotate(projectionMatrix, rotationAngle,glm::vec3(0,0,1));
	
	//scale the coordinates up by the specified amounts
	projectionMatrix = glm::scale(projectionMatrix, glm::vec3(scaleX, scaleY, 1.0));
	
	struct TextureData texData = TextureData();
	texData.texture = texture->texture;
	texData.width =  width;
	texData.height = height;
	texData.matrix = projectionMatrix;
	texData.color = Color(255,255,255);
	texturesToDraw.push_back(texData);
}

void TextureBatch::Draw(Texture2D* texture, float x, float y, float scaleX, float scaleY, float rotationAngle, Rectangle sourceRect)
{
	glm::mat4 projectionMatrix;
	int width = texture->GetWidth();
	int height = texture->GetHeight();


	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::GetWidth()-1.0f, (float)GameWindow::GetHeight()-1.0f, 1.0f);

	
	//make new translation matrix
	projectionMatrix = glm::translate(projectionMatrix, glm::vec3(x + abs(width*scaleX/2.0f), y + abs(height*scaleY / 2.0f), 1));

	projectionMatrix = glm::rotate(projectionMatrix, rotationAngle,glm::vec3(0,0,1));

	
	//scale the coordinates up by the specified amounts
	projectionMatrix = glm::scale(projectionMatrix, glm::vec3(scaleX, scaleY, 1.0));
	
	struct TextureData texData = TextureData();
	texData.texture = texture->texture;
	texData.width =  width;
	texData.height = height;
	texData.matrix = projectionMatrix;
	texData.color = Color(255,255,255);
	texData.sourceRect = sourceRect;
	texturesToDraw.push_back(texData);
}

void TextureBatch::Draw(Texture2D* texture, float x, float y, float scaleX, float scaleY, float rotationAngle, Color tintColor)
{
	glm::mat4 projectionMatrix;
	int width = texture->GetWidth();
	int height = texture->GetHeight();


	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::GetWidth()-1.0f, (float)GameWindow::GetHeight()-1.0f, 1.0f);
	
	//make new translation matrix
	projectionMatrix = glm::translate(projectionMatrix, glm::vec3(x + abs(width*scaleX/2.0f), y + abs(height*scaleY / 2.0f), 1));

	projectionMatrix = glm::rotate(projectionMatrix, rotationAngle,glm::vec3(0,0,1));

	//scale the coordinates up by the specified amounts
	projectionMatrix = glm::scale(projectionMatrix, glm::vec3(scaleX, scaleY, 1.0));
	
	struct TextureData texData = TextureData();
	texData.texture = texture->texture;
	texData.width =  width;
	texData.height = height;
	texData.matrix = projectionMatrix;
	texData.color = tintColor;
	texturesToDraw.push_back(texData);
}

void TextureBatch::Draw(Texture2D* texture, float x, float y, float scaleX, float scaleY, float rotationAngle, Color tintColor, Rectangle sourceRect)
{
	glm::mat4 projectionMatrix;
	int width = texture->GetWidth();
	int height = texture->GetHeight();


	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::GetWidth()-1.0f, (float)GameWindow::GetHeight()-1.0f, 1.0f);

	
	//make new translation matrix
	projectionMatrix = glm::translate(projectionMatrix, glm::vec3(x + abs(width*scaleX/2.0f), y + abs(height*scaleY / 2.0f), 1));

	projectionMatrix = glm::rotate(projectionMatrix, rotationAngle,glm::vec3(0,0,1));

	//scale the coordinates up by the specified amounts
	projectionMatrix = glm::scale(projectionMatrix, glm::vec3(scaleX, scaleY, 1.0));
	
	struct TextureData texData = TextureData();
	texData.texture = texture->texture;
	texData.width =  width;
	texData.height = height;
	texData.matrix = projectionMatrix;
	texData.color = tintColor;
	texData.sourceRect = sourceRect;
	texturesToDraw.push_back(texData);
}

void TextureBatch::Draw(Texture2D* texture, glm::mat4 transformMatrix)
{
	int width = texture->GetWidth();
	int height = texture->GetHeight();

	struct TextureData texData = TextureData();
	texData.texture = texture->texture;
	texData.width =  width;
	texData.height = height;
	texData.matrix = transformMatrix;
	texData.color = Color(255,255,255);
	texturesToDraw.push_back(texData);
}

void TextureBatch::Draw(Texture2D* texture, glm::mat4 transformMatrix, Rectangle sourceRect)
{
	int width = texture->GetWidth();
	int height = texture->GetHeight();

	struct TextureData texData = TextureData();
	texData.texture = texture->texture;
	texData.width =  width;
	texData.height = height;
	texData.matrix = transformMatrix;
	texData.color = Color(255,255,255);
	texData.sourceRect = sourceRect;
	texturesToDraw.push_back(texData);
}

void TextureBatch::Draw(Texture2D* texture, glm::mat4 transformMatrix, Color tintColor)
{
	int width = texture->GetWidth();
	int height = texture->GetHeight();

	struct TextureData texData = TextureData();
	texData.texture = texture->texture;
	texData.width =  width;
	texData.height = height;
	texData.matrix = transformMatrix;
	texData.color = tintColor;
	texturesToDraw.push_back(texData);
}

void TextureBatch::Draw(Texture2D* texture, glm::mat4 transformMatrix, Color tintColor, Rectangle sourceRect)
{
	int width = texture->GetWidth();
	int height = texture->GetHeight();

	struct TextureData texData = TextureData();
	texData.texture = texture->texture;
	texData.width =  width;
	texData.height = height;
	texData.matrix = transformMatrix;
	texData.color = tintColor;
	texData.sourceRect = sourceRect;
	texturesToDraw.push_back(texData);
}

void TextureBatch::DrawPrimitiveRectangle(Rectangle rectangle, Color tintColor)
{
	
	glm::mat4 projectionMatrix;
	int width = 1;
	int height = 1;


	//setup the ortho projection matrix
	projectionMatrix = glm::ortho(1.0f, (float)GameWindow::GetWidth()-1.0f, (float)GameWindow::GetHeight()-1.0f, 1.0f);

	//make new translation matrix
	projectionMatrix = glm::translate(projectionMatrix, glm::vec3(rectangle.X + abs(width*rectangle.Width/2.0f), rectangle.Y + abs(height*rectangle.Height / 2.0f), 1));

	//scale the coordinates up by the specified amounts
	projectionMatrix = glm::scale(projectionMatrix, glm::vec3(rectangle.Width, rectangle.Height, 1.0));

	
	struct TextureData texData = TextureData();
	texData.texture = pixelTexture;
	texData.width =  width;
	texData.height = height;
	texData.matrix = projectionMatrix;
	texData.color = tintColor;
	texturesToDraw.push_back(texData);
}