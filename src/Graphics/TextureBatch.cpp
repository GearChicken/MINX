/*
MINX - A C++ Graphics and Input Wrapper Library
Copyright (C) 2013-2014  MINX Team

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

#include "TextureBatch.h"

using namespace MINX;
using namespace MINX::Graphics;

TextureBatch::TextureBatch(GLuint shaderProgram)
{
	this->shaderProgram= shaderProgram;
	batches = std::vector<BatchData*>();

	posCoord = glGetAttribLocation(shaderProgram, "position");
	texCoord = glGetAttribLocation(shaderProgram, "texcoord");
	tintCoord = glGetAttribLocation(shaderProgram, "tint");
	uniformTexture = glGetUniformLocation(shaderProgram, "tex");

	glGenVertexArrays(1, &vertexArray);
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &tintBuffer);

	/**
	*	Create Pixel Texture
	*/
	glActiveTexture( GL_TEXTURE0 );
	glGenTextures(1, &pixelTexture);
	glBindTexture(GL_TEXTURE_2D, pixelTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char texture[] = {
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


	glBindVertexArray(vertexArray);


	glEnableVertexAttribArray(posCoord);
	glEnableVertexAttribArray(texCoord);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(posCoord, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), 0);
	glVertexAttribPointer(texCoord, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void**)(3*sizeof(GLfloat)));


	glEnableVertexAttribArray(tintCoord);
	glBindBuffer(GL_ARRAY_BUFFER, tintBuffer);
	glVertexAttribPointer(tintCoord, 4, GL_FLOAT, GL_FALSE, 0 , 0);

	float renderTargetWidth, renderTargetHeight;

	if(Game::activeRenderTarget == NULL)
	{
		renderTargetWidth = GameWindow::GetWidth();
		renderTargetHeight = GameWindow::GetHeight();
	}
	else
	{
		renderTargetWidth = Game::activeRenderTarget->GetWidth();
		renderTargetHeight = Game::activeRenderTarget->GetHeight();
	}


	glm::mat4 projectionMatrix;
	projectionMatrix = glm::ortho(1.0f, (float)renderTargetWidth-1.0f, (float)renderTargetHeight-1.0f, 1.0f);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projectionMatrix"), 1, false, glm::value_ptr(projectionMatrix));

	std::vector<GLfloat> pointData;
	for (auto batch : batches)
	{
		//texturesToDraw[i]->width;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, batch->texture);


		// Calculate total buffer size
		int bufferSize = batch->posPoints.size() + batch->texPoints.size();

		pointData = std::vector<GLfloat>();

		for(int spriteID = 0; spriteID < batch->spriteCount; ++spriteID)
		{
			for(int p = 0; p < 4; ++p)
			{
				pointData.push_back(batch->posPoints[spriteID * 12 + p * 3 + 0]);
				pointData.push_back(batch->posPoints[spriteID * 12 + p * 3 + 1]);
				pointData.push_back(batch->posPoints[spriteID * 12 + p * 3 + 2]);

				pointData.push_back(batch->texPoints[spriteID * 8 + p * 2 + 0]);
				pointData.push_back(batch->texPoints[spriteID * 8 + p * 2 + 1]);

				//std::cout << "X: " << batch->posPoints[spriteID * 4 + p * 3 + 0] << " Y:" << batch->posPoints[spriteID * 4 + p * 3 + 1] << " Z: " << batch->posPoints[spriteID * 4 + p * 3 + 2] << " U: " << batch->texPoints[spriteID * 4 + p * 2 + 0] << " V: " << batch->texPoints[spriteID * 4 + p * 2 + 1] << "\n";

			}
		}
		/*
		for(int i = 0; i < pointData.size(); i +=5)
		{
		std::cout << "X: " << pointData[i] << " Y:" << pointData[i+1] << " Z: " << pointData[i+2] << " U: " << pointData[i+3] << " V: " << pointData[i+4] << "\n";
		}
		std::cout << std::endl;
		//*/
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * bufferSize, (GLvoid*)&pointData[0], GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, tintBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * batch->tintPoints.size(), (GLvoid*)&batch->tintPoints[0], GL_DYNAMIC_DRAW);
		glDrawArrays(GL_QUADS, 0, batch->posPoints.size()/3);
	}

	glDisableVertexAttribArray(posCoord);
	glDisableVertexAttribArray(texCoord);
	glDisableVertexAttribArray(tintCoord);

	batches.clear();
	glBindTexture(GL_TEXTURE_2D, 0);
}



void TextureBatch::Draw(Texture2D* texture, float x, float y)
{
	glm::mat4 projectionMatrix;
	int width = texture->GetWidth();
	int height = texture->GetHeight();
	
	
	

	//make new translation matrix
	projectionMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));

	BatchData* currentBatch = GetBatchForTexture(texture->texture);

	if(currentBatch == NULL)
	{
		currentBatch = new BatchData();
		currentBatch->texture = texture->texture;
		currentBatch->posPoints = std::vector<GLfloat>();
		currentBatch->texPoints = std::vector<GLfloat>();
		currentBatch->tintPoints = std::vector<GLfloat>();
		currentBatch->spriteCount = 0;
		batches.push_back(currentBatch);
	}

	glm::vec4 tl = projectionMatrix * glm::vec4(-width /2.0f, height / 2.0f, 0, 1);
	glm::vec4 tr = projectionMatrix * glm::vec4(width/2.0f, height/2.0f,0, 1);
	glm::vec4 br = projectionMatrix * glm::vec4(width/2.0f, -height/2.0f,0, 1);
	glm::vec4 bl = projectionMatrix * glm::vec4(-width/2.0f, -height/2.0f,0, 1);
	//Top Left
	currentBatch->AddPoint(Vector2(tl.x, tl.y), Vector2(0,0));
	//Top Right
	currentBatch->AddPoint(Vector2(tr.x,tr.y), Vector2(1,0));
	//Bottom Right
	currentBatch->AddPoint(Vector2(br.x,br.y), Vector2(1,1));
	//Bottom Left
	currentBatch->AddPoint(Vector2(bl.x, bl.y), Vector2(0, 1));

	//Add Tint
	currentBatch->AddTint(Color());

}

void TextureBatch::Draw(Texture2D* texture, float x, float y, Rectangle sourceRect)
{
	glm::mat4 projectionMatrix;
	int width = texture->GetWidth();
	int height = texture->GetHeight();
	
	

	//make new translation matrix
	projectionMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));


	BatchData* currentBatch = GetBatchForTexture(texture->texture);

	if(currentBatch == NULL)
	{
		currentBatch = new BatchData();
		currentBatch->texture = texture->texture;
		currentBatch->posPoints = std::vector<GLfloat>();
		currentBatch->texPoints = std::vector<GLfloat>();
		currentBatch->tintPoints = std::vector<GLfloat>();
		currentBatch->spriteCount = 0;
		batches.push_back(currentBatch);
	}

	glm::vec4 tl = projectionMatrix * glm::vec4(-width /2.0f, height / 2.0f, 0, 1);
	glm::vec4 tr = projectionMatrix * glm::vec4(width/2.0f, height/2.0f,0, 1);
	glm::vec4 br = projectionMatrix * glm::vec4(width/2.0f, -height/2.0f,0, 1);
	glm::vec4 bl = projectionMatrix * glm::vec4(-width/2.0f, -height/2.0f,0, 1);
	//Top Left
	currentBatch->AddPoint(Vector2(tl.x, tl.y), Vector2(0,0));
	//Top Right
	currentBatch->AddPoint(Vector2(tr.x,tr.y), Vector2(1,0));
	//Bottom Right
	currentBatch->AddPoint(Vector2(br.x,br.y), Vector2(1,1));
	//Bottom Left
	currentBatch->AddPoint(Vector2(bl.x, bl.y), Vector2(0, 1));

	//Add Tint
	currentBatch->AddTint(Color());
}

void TextureBatch::Draw(Texture2D* texture, float x, float y, float scaleX, float scaleY)
{
	glm::mat4 projectionMatrix;
	int width = texture->GetWidth();
	int height = texture->GetHeight();


	
	

	//make new translation matrix
	projectionMatrix = glm::translate(projectionMatrix, glm::vec3(x + abs(width*scaleX/2.0f), y + abs(height*scaleY / 2.0f), 1));

	//scale the coordinates up by the specified amounts
	projectionMatrix = glm::scale(projectionMatrix, glm::vec3(scaleX, scaleY, 1.0));



	BatchData* currentBatch = GetBatchForTexture(texture->texture);

	if(currentBatch == NULL)
	{
		currentBatch = new BatchData();
		currentBatch->texture = texture->texture;
		currentBatch->posPoints = std::vector<GLfloat>();
		currentBatch->texPoints = std::vector<GLfloat>();
		currentBatch->tintPoints = std::vector<GLfloat>();
		currentBatch->spriteCount = 0;
		batches.push_back(currentBatch);
	}

	glm::vec4 tl = projectionMatrix * glm::vec4(-width /2.0f, height / 2.0f, 0, 1);
	glm::vec4 tr = projectionMatrix * glm::vec4(width/2.0f, height/2.0f,0, 1);
	glm::vec4 br = projectionMatrix * glm::vec4(width/2.0f, -height/2.0f,0, 1);
	glm::vec4 bl = projectionMatrix * glm::vec4(-width/2.0f, -height/2.0f,0, 1);
	//Top Left
	currentBatch->AddPoint(Vector2(tl.x, tl.y), Vector2(0,0));
	//Top Right
	currentBatch->AddPoint(Vector2(tr.x,tr.y), Vector2(1,0));
	//Bottom Right
	currentBatch->AddPoint(Vector2(br.x,br.y), Vector2(1,1));
	//Bottom Left
	currentBatch->AddPoint(Vector2(bl.x, bl.y), Vector2(0, 1));

	//Add Tint
	currentBatch->AddTint(Color());
}

void TextureBatch::Draw(Texture2D* texture, float x, float y, float scaleX, float scaleY, Rectangle sourceRect)
{
	glm::mat4 projectionMatrix;
	int width = texture->GetWidth();
	int height = texture->GetHeight();


	
	

	//make new translation matrix
	projectionMatrix = glm::translate(projectionMatrix, glm::vec3(x + abs(width*scaleX/2.0f), y + abs(height*scaleY / 2.0f), 1));

	//scale the coordinates up by the specified amounts
	projectionMatrix = glm::scale(projectionMatrix, glm::vec3(scaleX, scaleY, 1.0));



	BatchData* currentBatch = GetBatchForTexture(texture->texture);

	if(currentBatch == NULL)
	{
		currentBatch = new BatchData();
		currentBatch->texture = texture->texture;
		currentBatch->posPoints = std::vector<GLfloat>();
		currentBatch->texPoints = std::vector<GLfloat>();
		currentBatch->tintPoints = std::vector<GLfloat>();
		currentBatch->spriteCount = 0;
		batches.push_back(currentBatch);
	}


	glm::vec4 tl = projectionMatrix * glm::vec4(-width /2.0f, height / 2.0f, 0, 1);
	glm::vec4 tr = projectionMatrix * glm::vec4(width/2.0f, height/2.0f,0, 1);
	glm::vec4 br = projectionMatrix * glm::vec4(width/2.0f, -height/2.0f,0, 1);
	glm::vec4 bl = projectionMatrix * glm::vec4(-width/2.0f, -height/2.0f,0, 1);
	//Top Left
	currentBatch->AddPoint(Vector2(tl.x, tl.y), Vector2(0,0));
	//Top Right
	currentBatch->AddPoint(Vector2(tr.x,tr.y), Vector2(1,0));
	//Bottom Right
	currentBatch->AddPoint(Vector2(br.x,br.y), Vector2(1,1));
	//Bottom Left
	currentBatch->AddPoint(Vector2(bl.x, bl.y), Vector2(0, 1));

	//Add Tint
	currentBatch->AddTint(Color());
}

void TextureBatch::Draw(Texture2D* texture, float x, float y, float rotationAngle)
{
	glm::mat4 projectionMatrix;
	int width = texture->GetWidth();
	int height = texture->GetHeight();

	
	

	//make new translation matrix
	projectionMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));

	projectionMatrix = glm::rotate(projectionMatrix, rotationAngle,glm::vec3(0,0,1));


	BatchData* currentBatch = GetBatchForTexture(texture->texture);

	if(currentBatch == NULL)
	{
		currentBatch = new BatchData();
		currentBatch->texture = texture->texture;
		currentBatch->posPoints = std::vector<GLfloat>();
		currentBatch->texPoints = std::vector<GLfloat>();
		currentBatch->tintPoints = std::vector<GLfloat>();
		currentBatch->spriteCount = 0;
		batches.push_back(currentBatch);
	}


	glm::vec4 tl = projectionMatrix * glm::vec4(-width /2.0f, height / 2.0f, 0, 1);
	glm::vec4 tr = projectionMatrix * glm::vec4(width/2.0f, height/2.0f,0, 1);
	glm::vec4 br = projectionMatrix * glm::vec4(width/2.0f, -height/2.0f,0, 1);
	glm::vec4 bl = projectionMatrix * glm::vec4(-width/2.0f, -height/2.0f,0, 1);
	//Top Left
	currentBatch->AddPoint(Vector2(tl.x, tl.y), Vector2(0,0));
	//Top Right
	currentBatch->AddPoint(Vector2(tr.x,tr.y), Vector2(1,0));
	//Bottom Right
	currentBatch->AddPoint(Vector2(br.x,br.y), Vector2(1,1));
	//Bottom Left
	currentBatch->AddPoint(Vector2(bl.x, bl.y), Vector2(0, 1));

	//Add Tint
	currentBatch->AddTint(Color());
}

void TextureBatch::Draw(Texture2D* texture, float x, float y, float rotationAngle, Rectangle sourceRect)
{
	glm::mat4 projectionMatrix;
	int width = texture->GetWidth();
	int height = texture->GetHeight();

	
	

	//make new translation matrix
	projectionMatrix = glm::translate(projectionMatrix, glm::vec3(x + width/2.0f, y + height / 2.0f, 1));

	projectionMatrix = glm::rotate(projectionMatrix, rotationAngle,glm::vec3(0,0,1));


	BatchData* currentBatch = GetBatchForTexture(texture->texture);

	if(currentBatch == NULL)
	{
		currentBatch = new BatchData();
		currentBatch->texture = texture->texture;
		currentBatch->posPoints = std::vector<GLfloat>();
		currentBatch->texPoints = std::vector<GLfloat>();
		currentBatch->tintPoints = std::vector<GLfloat>();
		currentBatch->spriteCount = 0;
		batches.push_back(currentBatch);
	}

	glm::vec4 tl = projectionMatrix * glm::vec4(-width /2.0f, height / 2.0f, 0, 1);
	glm::vec4 tr = projectionMatrix * glm::vec4(width/2.0f, height/2.0f,0, 1);
	glm::vec4 br = projectionMatrix * glm::vec4(width/2.0f, -height/2.0f,0, 1);
	glm::vec4 bl = projectionMatrix * glm::vec4(-width/2.0f, -height/2.0f,0, 1);
	//Top Left
	currentBatch->AddPoint(Vector2(tl.x, tl.y), Vector2(0,0));
	//Top Right
	currentBatch->AddPoint(Vector2(tr.x,tr.y), Vector2(1,0));
	//Bottom Right
	currentBatch->AddPoint(Vector2(br.x,br.y), Vector2(1,1));
	//Bottom Left
	currentBatch->AddPoint(Vector2(bl.x, bl.y), Vector2(0, 1));

	//Add Tint
	currentBatch->AddTint(Color());
}

void TextureBatch::Draw(Texture2D* texture, float x, float y, float scaleX, float scaleY, float rotationAngle)
{
	glm::mat4 projectionMatrix;
	int width = texture->GetWidth();
	int height = texture->GetHeight();


	
	


	//make new translation matrix
	projectionMatrix = glm::translate(projectionMatrix, glm::vec3(x + abs(width*scaleX/2.0f), y + abs(height*scaleY / 2.0f), 1));

	projectionMatrix = glm::rotate(projectionMatrix, rotationAngle,glm::vec3(0,0,1));

	//scale the coordinates up by the specified amounts
	projectionMatrix = glm::scale(projectionMatrix, glm::vec3(scaleX, scaleY, 1.0));


	BatchData* currentBatch = GetBatchForTexture(texture->texture);

	if(currentBatch == NULL)
	{
		currentBatch = new BatchData();
		currentBatch->texture = texture->texture;
		currentBatch->posPoints = std::vector<GLfloat>();
		currentBatch->texPoints = std::vector<GLfloat>();
		currentBatch->tintPoints = std::vector<GLfloat>();
		currentBatch->spriteCount = 0;
		batches.push_back(currentBatch);
	}

	glm::vec4 tl = projectionMatrix * glm::vec4(-width /2.0f, height / 2.0f, 0, 1);
	glm::vec4 tr = projectionMatrix * glm::vec4(width/2.0f, height/2.0f,0, 1);
	glm::vec4 br = projectionMatrix * glm::vec4(width/2.0f, -height/2.0f,0, 1);
	glm::vec4 bl = projectionMatrix * glm::vec4(-width/2.0f, -height/2.0f,0, 1);
	//Top Left
	currentBatch->AddPoint(Vector2(tl.x, tl.y), Vector2(0,0));
	//Top Right
	currentBatch->AddPoint(Vector2(tr.x,tr.y), Vector2(1,0));
	//Bottom Right
	currentBatch->AddPoint(Vector2(br.x,br.y), Vector2(1,1));
	//Bottom Left
	currentBatch->AddPoint(Vector2(bl.x, bl.y), Vector2(0, 1));

	//Add Tint
	currentBatch->AddTint(Color());
}

void TextureBatch::Draw(Texture2D* texture, float x, float y, float scaleX, float scaleY, float rotationAngle, Rectangle sourceRect)
{
	glm::mat4 projectionMatrix;
	int width = texture->GetWidth();
	int height = texture->GetHeight();


	
	


	//make new translation matrix
	projectionMatrix = glm::translate(projectionMatrix, glm::vec3(x + abs(width*scaleX/2.0f), y + abs(height*scaleY / 2.0f), 1));

	projectionMatrix = glm::rotate(projectionMatrix, rotationAngle,glm::vec3(0,0,1));


	//scale the coordinates up by the specified amounts
	projectionMatrix = glm::scale(projectionMatrix, glm::vec3(scaleX, scaleY, 1.0));


	BatchData* currentBatch = GetBatchForTexture(texture->texture);

	if(currentBatch == NULL)
	{
		currentBatch = new BatchData();
		currentBatch->texture = texture->texture;
		currentBatch->posPoints = std::vector<GLfloat>();
		currentBatch->texPoints = std::vector<GLfloat>();
		currentBatch->tintPoints = std::vector<GLfloat>();
		currentBatch->spriteCount = 0;
		batches.push_back(currentBatch);
	}


	glm::vec4 tl = projectionMatrix * glm::vec4(-width /2.0f, height / 2.0f, 0, 1);
	glm::vec4 tr = projectionMatrix * glm::vec4(width/2.0f, height/2.0f,0, 1);
	glm::vec4 br = projectionMatrix * glm::vec4(width/2.0f, -height/2.0f,0, 1);
	glm::vec4 bl = projectionMatrix * glm::vec4(-width/2.0f, -height/2.0f,0, 1);
	//Top Left
	currentBatch->AddPoint(Vector2(tl.x, tl.y), Vector2(0,0));
	//Top Right
	currentBatch->AddPoint(Vector2(tr.x,tr.y), Vector2(1,0));
	//Bottom Right
	currentBatch->AddPoint(Vector2(br.x,br.y), Vector2(1,1));
	//Bottom Left
	currentBatch->AddPoint(Vector2(bl.x, bl.y), Vector2(0, 1));

	//Add Tint
	currentBatch->AddTint(Color());
}

void TextureBatch::Draw(Texture2D* texture, float x, float y, float scaleX, float scaleY, float rotationAngle, Color tintColor)
{
	glm::mat4 projectionMatrix;
	int width = texture->GetWidth();
	int height = texture->GetHeight();


	
	

	//make new translation matrix
	projectionMatrix = glm::translate(projectionMatrix, glm::vec3(x + abs(width*scaleX/2.0f), y + abs(height*scaleY / 2.0f), 1));

	projectionMatrix = glm::rotate(projectionMatrix, rotationAngle,glm::vec3(0,0,1));

	//scale the coordinates up by the specified amounts
	projectionMatrix = glm::scale(projectionMatrix, glm::vec3(scaleX, scaleY, 1.0));


	BatchData* currentBatch = GetBatchForTexture(texture->texture);

	if(currentBatch == NULL)
	{
		currentBatch = new BatchData();
		currentBatch->texture = texture->texture;
		currentBatch->posPoints = std::vector<GLfloat>();
		currentBatch->texPoints = std::vector<GLfloat>();
		currentBatch->tintPoints = std::vector<GLfloat>();
		currentBatch->spriteCount = 0;
		batches.push_back(currentBatch);
	}

	glm::vec4 tl = projectionMatrix * glm::vec4(-width /2.0f, height / 2.0f, 0, 1);
	glm::vec4 tr = projectionMatrix * glm::vec4(width/2.0f, height/2.0f,0, 1);
	glm::vec4 br = projectionMatrix * glm::vec4(width/2.0f, -height/2.0f,0, 1);
	glm::vec4 bl = projectionMatrix * glm::vec4(-width/2.0f, -height/2.0f,0, 1);
	//Top Left
	currentBatch->AddPoint(Vector2(tl.x, tl.y), Vector2(0,0));
	//Top Right
	currentBatch->AddPoint(Vector2(tr.x,tr.y), Vector2(1,0));
	//Bottom Right
	currentBatch->AddPoint(Vector2(br.x,br.y), Vector2(1,1));
	//Bottom Left
	currentBatch->AddPoint(Vector2(bl.x, bl.y), Vector2(0, 1));

	//Add Tint
	currentBatch->AddTint(Color());
}

void TextureBatch::Draw(Texture2D* texture, float x, float y, float scaleX, float scaleY, float rotationAngle, Color tintColor, Rectangle sourceRect)
{
	glm::mat4 projectionMatrix;
	int width = texture->GetWidth();
	int height = texture->GetHeight();


	
	


	//make new translation matrix
	projectionMatrix = glm::translate(projectionMatrix, glm::vec3(x + abs(width*scaleX/2.0f), y + abs(height*scaleY / 2.0f), 1));

	projectionMatrix = glm::rotate(projectionMatrix, rotationAngle,glm::vec3(0,0,1));

	//scale the coordinates up by the specified amounts
	projectionMatrix = glm::scale(projectionMatrix, glm::vec3(scaleX, scaleY, 1.0));


	BatchData* currentBatch = GetBatchForTexture(texture->texture);

	if(currentBatch == NULL)
	{
		currentBatch = new BatchData();
		currentBatch->texture = texture->texture;
		currentBatch->posPoints = std::vector<GLfloat>();
		currentBatch->texPoints = std::vector<GLfloat>();
		currentBatch->tintPoints = std::vector<GLfloat>();
		currentBatch->spriteCount = 0;
		batches.push_back(currentBatch);
	}

	glm::vec4 tl = projectionMatrix * glm::vec4(-width /2.0f, height / 2.0f, 0, 1);
	glm::vec4 tr = projectionMatrix * glm::vec4(width/2.0f, height/2.0f,0, 1);
	glm::vec4 br = projectionMatrix * glm::vec4(width/2.0f, -height/2.0f,0, 1);
	glm::vec4 bl = projectionMatrix * glm::vec4(-width/2.0f, -height/2.0f,0, 1);
	//Top Left
	currentBatch->AddPoint(Vector2(tl.x, tl.y), Vector2(0,0));
	//Top Right
	currentBatch->AddPoint(Vector2(tr.x,tr.y), Vector2(1,0));
	//Bottom Right
	currentBatch->AddPoint(Vector2(br.x,br.y), Vector2(1,1));
	//Bottom Left
	currentBatch->AddPoint(Vector2(bl.x, bl.y), Vector2(0, 1));

	//Add Tint
	currentBatch->AddTint(Color());
}

void TextureBatch::Draw(Texture2D* texture, glm::mat4 transformMatrix)
{
	int width = texture->GetWidth();
	int height = texture->GetHeight();


	BatchData* currentBatch = GetBatchForTexture(texture->texture);

	if(currentBatch == NULL)
	{
		currentBatch = new BatchData();
		currentBatch->texture = texture->texture;
		currentBatch->posPoints = std::vector<GLfloat>();
		currentBatch->texPoints = std::vector<GLfloat>();
		currentBatch->tintPoints = std::vector<GLfloat>();
		currentBatch->spriteCount = 0;
		batches.push_back(currentBatch);
	}

	glm::vec4 tl = transformMatrix * glm::vec4(-width /2.0f, height / 2.0f, 0, 1);
	glm::vec4 tr = transformMatrix * glm::vec4(width/2.0f, height/2.0f,0, 1);
	glm::vec4 br = transformMatrix * glm::vec4(width/2.0f, -height/2.0f,0, 1);
	glm::vec4 bl = transformMatrix * glm::vec4(-width/2.0f, -height/2.0f,0, 1);
	//Top Left
	currentBatch->AddPoint(Vector2(tl.x, tl.y), Vector2(0,0));
	//Top Right
	currentBatch->AddPoint(Vector2(tr.x,tr.y), Vector2(1,0));
	//Bottom Right
	currentBatch->AddPoint(Vector2(br.x,br.y), Vector2(1,1));
	//Bottom Left
	currentBatch->AddPoint(Vector2(bl.x, bl.y), Vector2(0, 1));

	//Add Tint
	currentBatch->AddTint(Color());
}

void TextureBatch::Draw(Texture2D* texture, glm::mat4 transformMatrix, Rectangle sourceRect)
{
	int width = texture->GetWidth();
	int height = texture->GetHeight();


	BatchData* currentBatch = GetBatchForTexture(texture->texture);

	if(currentBatch == NULL)
	{
		currentBatch = new BatchData();
		currentBatch->texture = texture->texture;
		currentBatch->posPoints = std::vector<GLfloat>();
		currentBatch->texPoints = std::vector<GLfloat>();
		currentBatch->tintPoints = std::vector<GLfloat>();
		currentBatch->spriteCount = 0;
		batches.push_back(currentBatch);
	}

	glm::vec4 tl = transformMatrix * glm::vec4(-width /2.0f, height / 2.0f, 0, 1);
	glm::vec4 tr = transformMatrix * glm::vec4(width/2.0f, height/2.0f,0, 1);
	glm::vec4 br = transformMatrix * glm::vec4(width/2.0f, -height/2.0f,0, 1);
	glm::vec4 bl = transformMatrix * glm::vec4(-width/2.0f, -height/2.0f,0, 1);
	//Top Left
	currentBatch->AddPoint(Vector2(tl.x, tl.y), Vector2(0,0));
	//Top Right
	currentBatch->AddPoint(Vector2(tr.x,tr.y), Vector2(1,0));
	//Bottom Right
	currentBatch->AddPoint(Vector2(br.x,br.y), Vector2(1,1));
	//Bottom Left
	currentBatch->AddPoint(Vector2(bl.x, bl.y), Vector2(0, 1));

	//Add Tint
	currentBatch->AddTint(Color());
}

void TextureBatch::Draw(Texture2D* texture, glm::mat4 transformMatrix, Color tintColor)
{
	int width = texture->GetWidth();
	int height = texture->GetHeight();


	BatchData* currentBatch = GetBatchForTexture(texture->texture);

	if(currentBatch == NULL)
	{
		currentBatch = new BatchData();
		currentBatch->texture = texture->texture;
		currentBatch->posPoints = std::vector<GLfloat>();
		currentBatch->texPoints = std::vector<GLfloat>();
		currentBatch->tintPoints = std::vector<GLfloat>();
		currentBatch->spriteCount = 0;
		batches.push_back(currentBatch);
	}

	glm::vec4 tl = transformMatrix * glm::vec4(-width /2.0f, height / 2.0f, 0, 1);
	glm::vec4 tr = transformMatrix * glm::vec4(width/2.0f, height/2.0f,0, 1);
	glm::vec4 br = transformMatrix * glm::vec4(width/2.0f, -height/2.0f,0, 1);
	glm::vec4 bl = transformMatrix * glm::vec4(-width/2.0f, -height/2.0f,0, 1);
	//Top Left
	currentBatch->AddPoint(Vector2(tl.x, tl.y), Vector2(0,0));
	//Top Right
	currentBatch->AddPoint(Vector2(tr.x,tr.y), Vector2(1,0));
	//Bottom Right
	currentBatch->AddPoint(Vector2(br.x,br.y), Vector2(1,1));
	//Bottom Left
	currentBatch->AddPoint(Vector2(bl.x, bl.y), Vector2(0, 1));

	//Add Tint
	currentBatch->AddTint(Color());
}

void TextureBatch::Draw(Texture2D* texture, glm::mat4 transformMatrix, Color tintColor, Rectangle sourceRect)
{
	int width = texture->GetWidth();
	int height = texture->GetHeight();


	BatchData* currentBatch = GetBatchForTexture(texture->texture);

	if(currentBatch == NULL)
	{
		currentBatch = new BatchData();
		currentBatch->texture = texture->texture;
		currentBatch->posPoints = std::vector<GLfloat>();
		currentBatch->texPoints = std::vector<GLfloat>();
		currentBatch->tintPoints = std::vector<GLfloat>();
		currentBatch->spriteCount = 0;
		batches.push_back(currentBatch);
	}	currentBatch->AddTint(Color());

}

void TextureBatch::DrawPrimitiveRectangle(Rectangle rectangle, Color tintColor)
{

	glm::mat4 projectionMatrix;
	int width = 1;
	int height = 1;


	
	

	//make new translation matrix
	projectionMatrix = glm::translate(projectionMatrix, glm::vec3(rectangle.X + abs(width*rectangle.Width/2.0f), rectangle.Y + abs(height*rectangle.Height / 2.0f), 1));

	//scale the coordinates up by the specified amounts
	projectionMatrix = glm::scale(projectionMatrix, glm::vec3(rectangle.Width, rectangle.Height, 1.0));



	BatchData* currentBatch = GetBatchForTexture(pixelTexture);

	if(currentBatch == NULL)
	{
		currentBatch = new BatchData();
		currentBatch->texture = pixelTexture;
		currentBatch->posPoints = std::vector<GLfloat>();
		currentBatch->texPoints = std::vector<GLfloat>();
		currentBatch->tintPoints = std::vector<GLfloat>();
		currentBatch->spriteCount = 0;
		batches.push_back(currentBatch);
	}	currentBatch->AddTint(Color());

}

void BatchData::AddPoint(Vector2 position, Vector2 texCoord)
{
	posPoints.push_back(position.X);
	posPoints.push_back(position.Y);
	posPoints.push_back(0);

	texPoints.push_back(texCoord.X);
	texPoints.push_back(texCoord.Y);
}

void BatchData::AddTint(Color tint)
{
	for (int i = 0; i < 4; i++)
	{
		tintPoints.push_back(tint.R / 255.0f);
		tintPoints.push_back(tint.G / 255.0f);
		tintPoints.push_back(tint.B / 255.0f);
		tintPoints.push_back(tint.A / 255.0f);
	}
	spriteCount += 1;
}

BatchData* TextureBatch::GetBatchForTexture(GLuint texture)
{
	for(auto batch : batches)
	{
		if(batch->texture == texture)
		{
			return batch;
		}
	}
	return NULL;
}