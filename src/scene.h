#pragma once

// Dependancies
#include <vector>
#include <list>

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

	//Entity and tile container
	class Map
	{
	public:
		Tile mapTiles[TILED_SIZE][TILED_SIZE];

		// Monsters + Characters + items- in scene
		std::list<Entity*> activeEntityPointers;
		std::list<Entity> staticEntityStorage;

		Map();
		Map(Tile newMapTiles[TILED_SIZE][TILED_SIZE]);

		Entity* get_entity_at_location(Entity* self, int x, int y);
		void sort_entity_pointers_for_rendering();
		void spawn_entity_copy_at(Entity entity, int x, int y);
		void eventPass(Event* actionEvent);
		bool inBounds(int x, int y);
	};
	
	//Entity and GameMap container
	class World
	{
	public:
		Entity player;

		Map* regionTiles[TILED_SIZE][TILED_SIZE];
		WorldTile worldTiles[TILED_SIZE][TILED_SIZE];

		//std::vector<Entity> metaGameEntities;

		World();
		World(WorldTile newWorldTiles[TILED_SIZE][TILED_SIZE]);
		~World();

		Map* get_map_at(int x, int y);
		Map* get_active_map();
		void eventPass(Event* actionEvent);
		bool inBounds(int x, int y);
	};	
}

