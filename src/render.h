#pragma once


// Dependancies
#include <string>
#include <libtcod.hpp>
#include "entity.h"
#include "scene.h"

namespace crp
{
	// 2D Tile Renderer
	class TileRender
	{
	public:
		// Pointer to active console to draw onto
		TCOD_Console* console;

		TileRender(TCOD_Console* console) : console(console){};

		void draw_entities(GameMap* map);

		void draw_tiles(GameMap* map);
		
		void draw_screen_text(std::string text, int x, int y);

		void draw_world_text(std::string text, GameMap* map, int x, int y);
	private:
		bool inCamBounds(GameMap* map, int x, int y);
	};
}