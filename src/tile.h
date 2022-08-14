#pragma once

// Dependancies
#include <libtcod.hpp>
#include <SDL2/SDL.h>

namespace mom
{
	class Tile
	{
	public:
		bool walkable = true;

		bool flooded = false;
		bool transparent = true;
		bool flammable = false;

		std::string tileName = "";
		int character;
		tcod::ColorRGB color;
		
		Tile() : walkable(true), flooded(true), transparent(true), flammable(false), character(0x00), color(tcod::ColorRGB{ 0, 0, 0 }) {}
		Tile(std::string tileName, bool walkable, bool flooded, bool transparent, bool flammable, int ch, tcod::ColorRGB col) : tileName(tileName), walkable(walkable), flooded(flooded), transparent(transparent), flammable(flammable), character(ch), color(col) {}
	};

	class WorldTile
	{
	public:
		bool walkable = true;
		float cost = 1.0f;

		std::string tileName = "";
		int character = 0;
		tcod::ColorRGB color;

		WorldTile() : tileName(""), walkable(true),  character(0x00), color(tcod::ColorRGB{ 0, 0, 0 }), cost(1.0f) {}
		WorldTile(std::string name, int character, tcod::ColorRGB color, bool walkable, float cost)
			: walkable(walkable), color(color), character(character), tileName(name), cost(cost) {}
	};

	class Feature
	{
	public:

	};
}
