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
#ifndef CONTENT_H_
#define CONTENT_H_
#include <map>
#include "SDL/SDL.h"
#include "Game.h"
#include "Graphics/Texture2D.h"
#include <string>
#include <vector>
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"

using namespace MINX::Graphics;
using namespace MINX;
using namespace std;

namespace MINX
{
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
}
#endif
