#pragma once

// Forward Declarations
class Scene;

// Dependancies
#include <libtcod.hpp>
#include <SDL2/SDL.h>

#include "entity.h"
#include "render.h"
#include "action.h"

namespace crp
{
	//Catch all class to handle game state. This includes: render state, input handling,
	class BaseHandler
	{
	public:
		bool handle_events(SDL_Event* event, Entity* player);

		void on_render(TileRender* render, Scene* activeScene);
	};
}