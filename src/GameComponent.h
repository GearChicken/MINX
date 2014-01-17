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
#ifndef GAMECOMPONENT_H_
#define GAMECOMPONENT_H_

#include "GameTime.h"

namespace MINX
{
	class Game; //forward declaration to avoid circular dependency problems

	/** Represents any component of the Game.
	 */
	class GameComponent
	{
		public:
			/** Creates the GameComponent
			 * @param attachTo A pointer to the Game to attach to.
			 */
			GameComponent(Game * attachTo);
			/** Initializes the GameComponent.
			 */
			virtual void Initialize();
			/** Update()s the GameComponent.
			 * @param gameTime the GameTime to update the GameComponent with.
			 */
			virtual void Update(GameTime * gameTime);
			/** Whether or not this GameComponent is enabled.
			 */
			bool enabled;
			/** A pointer to the Game that this GameComponent is attached to.
			 */
			Game * game;
			/** An integer that specifies the order in which this GameComponent should be called.
			*/
			int updateOrder;
	};
}

#include "Game.h" //and now actually include Game.h, for use by GameComponent.cpp

#endif
