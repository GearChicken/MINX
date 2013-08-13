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

#ifdef _WIN32
#define DLLImport __declspec(dllimport)
#else
#define DLLImport
#endif

#include <map>
#include <queue>
#include <string>
#include <vector>
#ifdef _WIN32
#include <SDL_ttf.h>
#else
#include <SDL/SDL_ttf.h>
#endif
namespace MINX
{
	class Game;
	namespace Graphics
	{
		class Texture2D;
		class GameWindow;
	}
	namespace Audio
	{
		class AudioClip;
	}
	class DLLImport GameTime
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
	class DLLImport GameComponent
	{
		public:
			GameComponent(Game * attachTo);
			virtual void Initialize();
			virtual void Update(GameTime * gameTime);
			bool enabled;
			Game * game;
			int updateOrder;
	};
	class DLLImport Content
	{
		public:
			Content(Game * addTo);
			Graphics::Texture2D* loadTexture(std::string name, std::string assetName);
			std::map<std::string, Graphics::Texture2D*>* textures;
			TTF_Font* loadTTFFont(std::string name, int size, std::string assetName);
			std::map<std::string, TTF_Font*>* TTFFonts;
			Audio::AudioClip* loadAudioClip(std::string name, std::string assetName, bool autoplay, bool loop);
			std::map<std::string, Audio::AudioClip*>* audioClips;
			Game * game;
	};
	class DLLImport Game 
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
			std::vector<GameComponent*> * Components;
			std::queue<SDL_Event*> * keyboardEvents;
			std::queue<SDL_Event*> * mouseEvents;
			std::queue<SDL_Event*> * gamepadEvents;
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
	struct DLLImport Point
	{
		Point(int x, int y);
		int X;
		int Y;
		bool operator==(const Point& compareTo);
		bool operator!=(const Point& compareTo);
	};
	struct DLLImport Ray2
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
	struct DLLImport Rectangle
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
	struct DLLImport Vector2
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
#ifdef _WIN32
#include <MINX_Audio.h>
#include <MINX_Graphics.h>
#include <MINX_Input.h>
#else
#include <MINX/MINX_Audio.h>
#include <MINX/MINX_Graphics.h>
#include <MINX/MINX_Input.h>
#endif
#endif
