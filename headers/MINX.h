/*
    MINX - A C++ Graphics and Input Wrapper Library
    Copyright (C) 2013  MINX Team

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
#ifndef MINX_H_
#define MINX_H_
#include <string>
#include <SDL/SDL_ttf.h>
namespace MINX
{
	class Game;
	class GameTime
	{
		public:
			GameTime();
			long getElapsedMillis();
			long getDeltaTime();
			void update();
			void limitFPS(int desiredFPS);
		private:
			long totalTimeMillis;
			long deltaTimeMillis;
			long lastUpdate;
	};
	class GameComponent
	{
		public:
			GameComponent(Game * attachTo);
			virtual void Initialize();
			virtual void Update(GameTime * gameTime);
			bool enabled;
			Game * game;
			int updateOrder;
	};
	class Content
	{
		public:
			Content(Game * addTo);
			Texture2D* loadTexture(std::string name, std::string assetName);
			map<string, Texture2D*>* textures;
			TTF_Font* loadTTFFont(std::string name, int size, std::string assetName);
			map<string, TTF_Font*>* TTFFonts;
			Game * game;
	};
	class Game 
	{
		public:
			Game();
			virtual void Initialize();
			virtual void LoadContent();
			virtual void Update(GameTime * gameTime);
			virtual void UnloadContent();
			virtual void Draw(GameTime * gameTime);
			void Run();
			Graphics::GameWindow* gameWindow;
			vector<GameComponent*> * Components;
			queue<SDL_Event*> * keyboardEvents;
			queue<SDL_Event*> * mouseEvents;
			queue<SDL_Event*> * gamepadEvents;
			GameTime * getGameTime();
			bool isRunning;
		private:
			SDL_Event evt;
			GameTime* gameTime;
		protected:
			int desiredFPS;
			int windowWidth, windowHeight, windowBPP;
			Uint32 windowFlags;
			Content* content;
	};
	struct Point
	{
		Point(int x, int y);
		int X;
		int Y;
		bool operator==(const Point& compareTo);
		bool operator!=(const Point& compareTo);
	};
	struct Ray2
	{
		Ray2(float direction, float xPosition, float yPosition);
		Ray2(float direction);
		float dir;
		float xPos;
		float yPos;
		Ray2 operator-()const;
		bool operator==(const Ray2& compareTo);
		bool operator!=(const Ray2& compareTo);
	};
	struct Rectangle
	{
		Rectangle(int x, int y, int width, int height);
		int area();
		int X;
		int Y;
		int Width;
		int Height;
		int Top();
		int Bottom();
		int Left();
		int Right();
		bool intersects(Rectangle* rect2);
	};
	struct Vector2
	{
		Vector2(float x, float y);
		Vector2 operator+(const Vector2& addTo);
		Vector2 operator-(const Vector2& subtractFrom);
		Vector2 crossMultiply(const Vector2& multiplyBy);
		float operator*(const Vector2& multiplyBy);
		Vector2 operator*(const float& multiplyBy);
		Vector2 operator-()const;
		bool operator==(const Vector2& compareTo);
		bool operator!=(const Vector2& compareTo);
		float length();
		float lengthSquared();
		Vector2 normalize();
		float X;
		float Y;
	};
}
#endif
