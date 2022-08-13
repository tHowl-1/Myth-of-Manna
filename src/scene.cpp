#include "scene.h"
#include "components/physics.h"
#include "components/render.h"

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


World::World()
{
	for (int i = 0; i < TILED_SIZE; i++)
	{
		for (int j = 0; j < TILED_SIZE; j++)
		{
			regionTiles[i][j] = nullptr;
		}
	}
	player = nullptr;
}


World::World(WorldTile newWorldTiles[TILED_SIZE][TILED_SIZE], Entity* newPlayer)
{
	for (int i = 0; i < TILED_SIZE; i++)
	{
		for (int j = 0; j < TILED_SIZE; j++)
		{
			regionTiles[i][j] = nullptr;
			worldTiles[i][j] = newWorldTiles[i][j];
		}
	}

	player = newPlayer;
	playerParty = new Party(new Physics(24, 24, true), new Render(ord("&"), WHITE));
	playerParty->partyMembers[0] = player;
}


World::~World()
{
	if (player != nullptr)
	{
		delete player;
	}
}

Map* World::get_map_at(int x, int y)
{
	if (regionTiles[x][y] == nullptr)
	{
		regionTiles[x][y] = new Map();
	}
	return regionTiles[x][y];
}

Map* World::get_active_map()
{
	Event positionEvent = Event(PositionEvent);
	playerParty->eventPass(&positionEvent);
	return get_map_at(positionEvent.x, positionEvent.y);
}

void World::eventPass(Event* actionEvent)
{
	playerParty->eventPass(actionEvent);
}