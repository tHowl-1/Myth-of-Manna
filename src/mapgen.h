#pragma once

#include <libtcod.hpp>
#include <SDL2/SDL.h>

#include "tile.h"

namespace mom
{
	class World;
	class Map;
	struct Params;
	class Entity;

	class MapGenerator
	{
	public:
		// --------------------------------------------------------------------------
		//                               WORLD GENERATION
		// --------------------------------------------------------------------------
		TCODHeightMap* generateGradient(bool north, bool east, bool south, bool west, bool invert);

		TCODHeightMap* generateIslandGradient();

		TCODHeightMap* generatePolarGradient();

		TCODHeightMap* generateNoiseMap(TCODHeightMap* gradient, float frequency, float octaves, bool multiply, bool lerp);

		World* generateWorld(Params* params);

		// --------------------------------------------------------------------------
		//                               MAP GENERATION
		// --------------------------------------------------------------------------

		Map* MapGenerator::generateMap(WorldTile worldTile);

	};

}