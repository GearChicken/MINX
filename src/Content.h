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
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Audio/AudioClip.h"
#include "Graphics/Texture2D.h"
#include <string>
#include <vector>

using namespace MINX::Graphics;
using namespace MINX::Audio;
using namespace MINX;
using namespace std;

namespace MINX
{
	namespace Content
	{
			/** Loads a texture
			 * @param name The filename
			 * @param gameWindow A pointer to the GameWindow that the texture will be drawn on
			 * @return A pointer to the texture loaded, This is also stored in the textures map
			 */
			Texture2D* loadTexture(std::string name, GameWindow* window);
			
			/** Loads a font
			 * @param name The filename
			 * @return A pointer to the texture loaded, This is also stored in the the textures map
			 */
			TTF_Font* loadTTFFont(std::string name, int size);
			
			/** Loads a sound
			 * @param name The filename
			 * @param autoplay  Autoplay the sound file
			 * @param loop  loop the sound file
			 * @return A pointer to the sound loaded, This is also stored in the the sounds map
			 */
			AudioClip* loadAudioClip(std::string name, bool autoplay, bool loop);
	};
}
#include "Game.h"
#endif
