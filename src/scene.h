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

const float waterLevel = 0.3f;
const float shoreLevel = 0.2f;
const float peakLevel = 0.95f;
const float rockyLevel = 0.7f;
const float forestLevel = 0.5f; 
const float hubLevel = 0.98f;
const float riverLevel = 0.8f;


namespace mom
{
	struct TilePosition
	{
		int x;
		int y;

		int id;

		TilePosition() : x(0), y(0), id(0) {}
		TilePosition(int x, int y, int id) : x(x), y(y), id(id) {}
	};

	struct PathTile
	{
		bool river;
		bool path;
		bool road;
	};

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
		Tile mapTiles[TILED_SIZE][TILED_SIZE];
		// Monsters + Characters - in scene
		std::vector<Entity*> activeEntities;
		Map();

		// Gets an entity at the given location if it is movement blocking
		void eventPass(Event* actionEvent);
		bool inBounds(int x, int y);
	};
	
	//Entity and GameMap container
	class World
	{
	public:
		Entity* player = nullptr;
		Party* playerParty = nullptr;

		Map* regionTiles[TILED_SIZE][TILED_SIZE];
		WorldTile worldTiles[TILED_SIZE][TILED_SIZE];

		// Characters - metagame npcs
		// Entity* staticEntities[MAX_ENTITIES];

		World();
		World(WorldTile newWorldTiles[TILED_SIZE][TILED_SIZE], Entity* newPlayer);

		~World();
		

		Map* get_map_at(int x, int y);
		Map* get_active_map();
		void eventPass(Event* actionEvent);
		bool inBounds(int x, int y);
	};	
}

