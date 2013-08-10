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
#ifndef MINX_GRAPHICS_H_
#define MINX_GRAPHICS_H_

#if defined(_WIN32) && !defined(DLLImport)
#define DLLImport __declspec(dllimport)
#else
#define DLLImport
#endif

#include <string>
#ifdef _WIN32
#include <SDL.h>
#include <SDL_ttf.h>
#include <MINX.h>
#else
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <MINX/MINX.h>
#endif
namespace MINX
{
	namespace Graphics
	{
		typedef unsigned char byte;
		struct DLLImport Color
		{
			byte R;
			byte G;
			byte B;
			byte A;
			Color(byte r, byte g, byte b, byte a);
			Color(byte r, byte g, byte b);
			bool operator==(const Color& compareTo);
			bool operator!=(const Color& compareTo);
			Color * operator*(const float& scale);
		};
		class DLLImport GameWindow
		{
			public:
				GameWindow(int width, int height, int bpp, Uint32 flags);
				SDL_Surface* screen;
				int width, height, bpp;
				Uint32 flags;
			private:
		};
		class DLLImport Texture2D
		{
			public:
				Texture2D(SDL_Surface * surface, GameWindow * gameWindow);
				~Texture2D();
				void Draw(int x, int y);
				void Draw(int x, int y, Color* tint);
				int width, height;
				SDL_Surface * tex;
			private:
				SDL_Surface * screen;
				
		};
		namespace DLLImport Primitives
		{
				Color* pixelToColor(Uint32 pixel, SDL_Surface* surface);
				Color* pixelToColor(int x, int y, SDL_Surface* surface);
				void colorToPixel(Color* color, int x, int y, SDL_Surface* surface);
				void drawRectangle(Color* color, int x, int y, int w, int h, SDL_Surface* surface);
				void drawOutlineRectangle(Color* color, int x, int y, int w, int h, SDL_Surface* surface);
		}
		void DLLImport DrawString(int x, int y, std::string text, SDL_Surface* screen, TTF_Font* font);
	}
}
#endif
