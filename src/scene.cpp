#include "scene.h"
#include "entity_types.h"
#include "mapgen.h"

using namespace mom;

// Checks if an x, y coordinate is within the bounds of the map
bool Map::inBounds(int x, int y)
{
	return (x >= 0 && x < TILED_SIZE && y >= 0 && y < TILED_SIZE);
}

bool World::inBounds(int x, int y)
{
	return (x >= 0 && x < TILED_SIZE&& y >= 0 && y < TILED_SIZE);
}

void Map::eventPass(Event* actionEvent)
{
	for (Entity* entity : activeEntities)
		entity->eventPass(actionEvent);
}

Map::Map()
{
	for (int i = 0; i < TILED_SIZE; i++)
	{
		for (int j = 0; j < TILED_SIZE; j++)
		{
			if ((i + j) % 2 == 0)
				mapTiles[i][j] = blue;
			else
				mapTiles[i][j] = red;
		}
	}
}

Map::~Map()
{
	for (int i = 1; i < MAX_ENTITIES; i++)
	{
		delete activeEntities[i];
	}
}

Map::Map(Tile newMapTiles[TILED_SIZE][TILED_SIZE])
{
	for (int i = 0; i < TILED_SIZE; i++)
	{
		for (int j = 0; j < TILED_SIZE; j++)
		{
			mapTiles[i][j] = newMapTiles[i][j];
		}
	}
}

World::World()
{
	activeMap = nullptr;
	player = Player;
}


World::World(WorldTile newWorldTiles[TILED_SIZE][TILED_SIZE])
{
	for (int i = 0; i < TILED_SIZE; i++)
	{
		for (int j = 0; j < TILED_SIZE; j++)
		{
			worldTiles[i][j] = newWorldTiles[i][j];
		}
	}
	activeMap = nullptr;
	player = Player;
}

Map* World::get_map_at(int x, int y)
{
	if (activeMap == nullptr)
	{
		MapGenerator newMapGen = MapGenerator();
		activeMap = newMapGen.generateMap(worldTiles[x][y]);
	}
	return activeMap;
}

Map* World::get_active_map()
{
	Event positionEvent = Event(WorldPositionEvent);
	player.eventPass(&positionEvent);
	return get_map_at(positionEvent.x, positionEvent.y);
}

void World::eventPass(Event* actionEvent)
{
	player.eventPass(actionEvent);
}

World::~World()
{
	if (activeMap != nullptr)
		delete activeMap;
}
