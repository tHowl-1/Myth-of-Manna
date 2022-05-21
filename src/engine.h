#pragma once

// Dependancies
#include <libtcod.hpp>
#include <SDL2/SDL.h>

#include "entity.h"
#include "render.h"
#include "validate.h"
#include "state_handling.h"
#include "scene.h"

// FIXME - Still not sure about where to put these constant values (maybe their own header file with the action enumerator?)
// 16:9 aspect ratio, console/screem width and height in cells/pixels respectively
const int CON_W = 80, CON_H = 45;
const int SCREEN_W = 1280, SCREEN_H = 720;

namespace crp
{
	// Crossroads for game logic to pass through, trying to avoid using singletons :)
	class Engine
	{
	public:
		tcod::Tileset tileset;
		tcod::Console console;
		tcod::ContextPtr context;

		Entity* player;
		TileRender* render;
		BaseHandler* activeHandler;
		GameMap* activeScene;

		bool QUIT_FLAG = false;

		Engine();

		~Engine();

		void validate_action(ActionOrHandler* action);

		void update();
		
	};
}