#pragma once

// Dependancies
#include <libtcod.hpp>
#include <SDL2/SDL.h>

namespace crp
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

	// Contains map tile data
	class MapTile : public Tile
	{
	public:
		MapTile() : Tile() {}
		MapTile(bool walk, int ch, tcod::ColorRGB col) : Tile(walk, ch, col) {}
	};

	// Contains world tile generation settings
	class WorldTile : public Tile
	{
	public:
		// Temp Parameters
		bool grassy;
		bool rocky;

		WorldTile() : grassy(false), rocky(false), Tile() {}
		WorldTile(bool walk, int ch, tcod::ColorRGB col, bool grassy, bool rocky) : grassy(grassy), rocky(rocky), Tile(walk, ch, col) {}
	};
}
