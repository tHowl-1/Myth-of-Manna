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

	class WorldTile
	{
	public:
		bool flooded = false;
		bool walkable = true;
		bool forested = false;

		std::string tileName = "";
		int character = 0;
		tcod::ColorRGB color;

		WorldTile() : tileName(""), forested(false), flooded(false), walkable(true), character(0x00), color(tcod::ColorRGB{ 0, 0, 0 }) {}
		WorldTile(std::string name, int character, tcod::ColorRGB color, bool flooded, bool walkable, bool forested)
			: flooded(flooded), walkable(walkable), forested(forested), color(color), character(character), tileName(name) {}
	};

	class Feature
	{
	public:

	};
}
