/*
# MINX

Copyright (c) 2013-2014 Liam Middlebrook, Benjamin Pylko

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

> 1\. The origin of this software must not be misrepresented; you must not
> claim that you wrote the original software. If you use this software
> in a product, an acknowledgment in the product documentation would be
> appreciated but is not required.
> 
> 2\. Altered source versions must be plainly marked as such, and must not be
> misrepresented as being the original software.
> 
> 3\. This notice may not be removed or altered from any source
> distribution.
>
 */

#include "API.h"

#include "GameTime.h"

#ifndef GAMECOMPONENT_H_
#define GAMECOMPONENT_H_

namespace MINX
{
	class MINX_API Game; //forward declaration to avoid circular dependency problems

	/** Represents any component of the Game.
	 */
	class MINX_API GameComponent
	{
		public:
			/** Creates the GameComponent
			 * @param attachTo A pointer to the Game to attach to.
			 */
			GameComponent(Game* attachTo);
			
			/** Destructs a GameComponent
			 */
			virtual ~GameComponent();
			
			/** Initializes the GameComponent.
			 */
			virtual void Initialize();
			
			/** Update()s the GameComponent.
			 * @param gameTime the GameTime to update the GameComponent with.
			 */
			virtual void Update(GameTime* gameTime);
			
			/** Whether or not this GameComponent is enabled.
			 */
			bool enabled;
			
			/** A pointer to the Game that this GameComponent is attached to.
			 */
			Game* game;
	};
}

#include "Game.h" //and now actually include Game.h, for use by GameComponent.cpp

#endif
