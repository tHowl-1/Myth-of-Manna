#pragma once

// Dependancies
#include <libtcod.hpp>
#include <SDL2/SDL.h>

namespace mom
{
	class Tile
	{
	public:
		bool walkable;
		int character;
		tcod::ColorRGB color;
		
		Tile() : walkable(true), character(0x00), color(tcod::ColorRGB{ 0, 0, 0 }) {}
		Tile(bool walk, int ch, tcod::ColorRGB col) : walkable(walk), character(ch), color(col) {}
	};
}
