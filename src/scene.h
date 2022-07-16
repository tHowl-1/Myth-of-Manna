#pragma once

// Dependancies
#include <vector>
#include <unordered_map>
#include <random>
#include "tile.h"
#include "tile_types.h"
#include "entity.h"

const int TILED_SIZE = 50;
const int MAX_ENTITIES = 256;

namespace crp
{
	class Params
	{
	public:
		// World Generation Paramaters:
		bool isPlains = false;
		bool isRock = false;

		Params( bool isPlains, bool isRock) : isPlains(isPlains), isRock(isRock) {}
	};

	//Entity and tile container
	class Map
	{
	public:
		MapTile mapTiles[TILED_SIZE][TILED_SIZE];
		// Monsters + Characters - in scene
		std::vector<Entity*> activeEntities;
		Map();
		Map(WorldTile* parentTile);

		// Gets an entity at the given location if it is movement blocking
		Entity* get_blocking_entity(int x, int y);
		bool inBounds(int x, int y);
	};

	struct Region
	{
		Map* regionMap = nullptr;
		WorldTile worldTile;
	};
	
	//Entity and GameMap container
	class World
	{
	public:
		Entity* player; 
		Party* playerParty;
		Params* params;
		Region regionTiles[TILED_SIZE][TILED_SIZE];
		// Characters - metagame npcs
		Entity* staticEntities[MAX_ENTITIES];

		World();
		World(Entity* newPlayer, Params* newParams);

		~World();
 
		Map* get_map_at(int x, int y);
		Map* get_active_map();
		Party* get_blocking_party(int x, int y);
		bool inBounds(int x, int y);
	};	
}

