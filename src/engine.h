#pragma once

// Dependancies
#include <libtcod.hpp>
#include <SDL2/SDL.h>

// 16:9 aspect ratio, console/screem width and height in cells/pixels respectively
const int CON_W = 96, CON_H = 54;
const int SCREEN_W = CON_W * 16, SCREEN_H = CON_H * 16;

/// <summary>
/// The engine class is the core game class that handles information passed to all other components of the game and the core game loop
/// </summary>

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

		// This function handles all ingame action and handler changing
		void validate_action(ActionOrHandler* actionOrHandler);

		// Core update function happens every game loop
		void update();
		
	};
}