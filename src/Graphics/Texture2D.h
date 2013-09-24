#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GL/FreeImage.h>
#include "Color.h"
namespace MINX
{
	namespace Graphics
	{
		class Texture2D
		{
		public:
			Texture2D(char* fileLoc, GLuint shaderProgram, int instanceNum);
			~Texture2D();
			void Draw(int x, int y);
			void Draw(int x, int y, float rotation);
			void Draw(int x, int y, float scaleX, float scaleY);
			void Draw(int x, int y, float scaleX, float scaleY, float rotation);
			void Draw(int x, int y, float scaleX, float scaleY, float rotation, Color* tint);
		private:	
			void Draw();
			float vertices[42];
			GLuint vertexBuffer;
			GLuint vertexArray;
			GLuint shaderProgram;
			GLint uniTrans;
			GLint uniTint;
		};

	}

}
#endif