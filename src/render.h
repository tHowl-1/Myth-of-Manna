#pragma once

// Forward Declarations
#include "entity.h"
#include "scene.h"

// Dependancies
#include <libtcod.hpp>


namespace crp
{
	// 2D Tile Renderer
	class TileRender
	{
	public:
		TCOD_Console* console;

		TileRender(TCOD_Console* console) : console(console){};

		void draw_entities(Scene* scene);
	};
}