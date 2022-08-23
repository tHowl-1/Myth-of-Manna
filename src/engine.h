﻿#pragma once

// Dependancies
#include <libtcod.hpp>
#include <SDL2/SDL.h>

// 16:9 aspect ratio, console/screem width and height in cells/pixels respectively
const int CON_W = 96, CON_H = 54;
const int SCREEN_W = CON_W * 16, SCREEN_H = CON_H * 16;

namespace mom
{
	// Forward Declarations
	class TileRender;
	class BaseHandler;
	class World;
	class ActionOrHandler;

	// Crossroads for game logic to pass through, trying to avoid using singletons :)
	class Engine
	{
	public:
		tcod::Tileset tileset;
		tcod::Console console;
		tcod::ContextPtr context;
		TCOD_ViewportOptions viewportOptions;

		TileRender* render;
		BaseHandler* activeHandler;
		World* activeWorld;

		bool QUIT_FLAG = false;

		Engine();

		~Engine();

		void validate_action(ActionOrHandler* actionOrHandler);

		void update();
		
	};
}