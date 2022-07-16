#include "scene.h"

using namespace crp;

// Checks if an x, y coordinate is within the bounds of the map
bool Map::inBounds(int x, int y)
{
	return (x >= 0 && x < TILED_SIZE && y >= 0 && y < TILED_SIZE);
}

bool World::inBounds(int x, int y)
{
	return (x >= 0 && x < TILED_SIZE&& y >= 0 && y < TILED_SIZE);
}

Entity* Map::get_blocking_entity(int x, int y)
{
	for (Entity* entity : activeEntities)
		if (entity->x == x && entity->y == y && entity->solid)
			return entity;
	return nullptr;
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

Map::Map(WorldTile* parentTile)
{
	for (int i = 0; i < TILED_SIZE; i++)
	{
		for (int j = 0; j < TILED_SIZE; j++)
		{
			if ((i + j) % 2 == 0)
				mapTiles[i][j] = yellow;
			else
				mapTiles[i][j] = green;
		}
	}
}

World::World()
{
	player = nullptr;
	params = nullptr;
	for (int i = 0; i < TILED_SIZE; i++)
	{
		for (int j = 0; j < TILED_SIZE; j++)
		{
			regionTiles[i][j].regionMap = nullptr;
			regionTiles[i][j].worldTile = plains;
		}
	}
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		staticEntities[i] = nullptr;
	}
}

World::World(Entity* newPlayer, Params* newParams)
{
	params = newParams;
	// Generate world based on params
	if (params->isPlains)
	{
		for (int i = 0; i < TILED_SIZE; i++)
		{
			for (int j = 0; j < TILED_SIZE; j++)
			{
				regionTiles[i][j].worldTile = plains;
			}
		}
	}
	else if (params->isRock)
	{
		for (int i = 0; i < TILED_SIZE; i++)
		{
			for (int j = 0; j < TILED_SIZE; j++)
			{
				regionTiles[i][j].worldTile = rock;
			}
		}
	}
	else
	{
		for (int i = 0; i < TILED_SIZE; i++)
		{
			for (int j = 0; j < TILED_SIZE; j++)
			{
				regionTiles[i][j].worldTile = water;
			}
		}
	}
	for (int i = 0; i < TILED_SIZE; i++)
	{
		for (int j = 0; j < TILED_SIZE; j++)
		{
			regionTiles[i][j].regionMap = nullptr;
		}
	}
	player = newPlayer;
	playerParty = new Party();
	playerParty->character = ord("&");
	playerParty->partyMembers[0] = player;
	staticEntities[0] = player;
}

World::~World()
{
	if (params != nullptr)
	{
		delete params;
	}
	if (player != nullptr)
	{
		delete player;
	}
}

Map* World::get_map_at(int x, int y)
{
	if (regionTiles[x][y].regionMap == nullptr)
	{
		regionTiles[x][y].regionMap = new Map(&regionTiles[x][y].worldTile);
	}
	return regionTiles[x][y].regionMap;
}

Map* World::get_active_map()
{
	return get_map_at(playerParty->x, playerParty->y);
}

Party* World::get_blocking_party(int x, int y)
{
	return nullptr;
}