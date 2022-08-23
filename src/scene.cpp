#include "scene.h"

#include <iostream>

#include "game_exceptions.h"
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
	for (Entity* entity : activeEntityPointers)
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
	for (int i = 0; i < TILED_SIZE; i++)
	{
		for (int j = 0; j < TILED_SIZE; j++)
		{
			regionTiles[i][j] = nullptr;
			worldTiles[i][j] = grassland;
		}
	}
	player = Player;
}


World::World(WorldTile newWorldTiles[TILED_SIZE][TILED_SIZE])
{
	for (int i = 0; i < TILED_SIZE; i++)
	{
		for (int j = 0; j < TILED_SIZE; j++)
		{
			regionTiles[i][j] = nullptr;
			worldTiles[i][j] = newWorldTiles[i][j];
		}
	}
	player = Player;
}

Map* World::get_map_at(int x, int y)
{
	if (regionTiles[x][y] == nullptr)
	{
		MapGenerator newMapGen = MapGenerator();
		regionTiles[x][y] = newMapGen.generateMap(worldTiles[x][y]);
	}
	return regionTiles[x][y];
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
	for (int i = 0; i < TILED_SIZE; i++)
	{
		for (int j = 0; j < TILED_SIZE; j++)
		{
			if (regionTiles[i][j] != nullptr)
				delete regionTiles[i][j];
		}
	}
}

Entity* Map::get_entity_at_location(Entity* self, int x, int y)
{
	for (auto entity : activeEntityPointers) {
		Event positionEvent = Event(PositionEvent);
		entity->eventPass(&positionEvent);
		if (positionEvent.x == x && positionEvent.y == y && entity != self)
			return entity;
	}
	return nullptr;
}

void Map::spawn_entity_copy_at(Entity entity, int x, int y)
{
	staticEntityStorage.push_back(Entity(entity));

	// Instantiate location:
	Event movementEvent = Event(MovementEvent);
	movementEvent.x = x;
	movementEvent.y = y;
	movementEvent.dx = 0;
	movementEvent.dy = 0;
	staticEntityStorage.back().eventPass(&movementEvent);

	// Copy pointer to pointer array:
	activeEntityPointers.push_back(&(staticEntityStorage.back()));
}

void Map::sort_entity_pointers_for_rendering()
{
	activeEntityPointers.sort([](Entity* a, Entity* b) {
		return a->sortPosition < b->sortPosition;
		}); 
}