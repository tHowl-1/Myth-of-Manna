#pragma once

// Dependancies
#include <libtcod.hpp>
#include <SDL2/SDL.h>

#include "entity.h"
#include "render.h"
#include "state_handling.h"
#include "scene.h"

// 16:9 aspect ratio, console/screem width and height in cells/pixels respectively - TODO Move constants into some engine class
const int CON_W = 80, CON_H = 45;
const int SCREEN_W = 1280, SCREEN_H = 720;

namespace crp
{
	// Crossroads for game logic to pass through, trying to avoid singletons :)
	class Engine
	{
	public:
		tcod::Tileset tileset;
		tcod::Console console;
		tcod::ContextPtr context;

		Entity* player;
		TileRender* render;
		BaseHandler* activeHandler;
		Scene* activeScene; // TODO Replace with gamemap and subsequently gameworld later on

		bool QUIT = false;

		Engine();

		void update();
		
	};
}