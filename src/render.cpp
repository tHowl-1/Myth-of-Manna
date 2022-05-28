#include "palette.h"

#include "render.h"

using namespace crp;

bool TileRender::inCamBounds(GameMap* map, int x, int y)
{
	int screen_X = map->cameraX, screen_Y = map->cameraY;
	return (x >= 0 && x < console->w&& y >= 0 && y < console->h);
}

// Draw all entities in a scene
void TileRender::draw_entities(GameMap* map)
{
	int world_X, world_Y;
	int screen_X, screen_Y;
	for (Entity* entity : map->entities)
	{
		world_X = entity->x;
		world_Y = entity->y;
		screen_X = world_X - map->cameraX + (console->w / 2);
		screen_Y = world_Y - map->cameraY + (console->h / 2);
		if (inCamBounds(map, screen_X, screen_Y))
		{
			console->at(screen_X, screen_Y).ch = entity->character;
			console->at(screen_X, screen_Y).fg = entity->color;
		}
	}
}

// Draw all tiles in a scene
void TileRender::draw_tiles(GameMap* map)
{
	int world_X, world_Y;
	for (int screen_X = 0; screen_X < console->w; screen_X++)
	{
		for (int screen_Y = 0; screen_Y < console->h; screen_Y++)
		{
			world_X = map->cameraX - (console->w / 2) + screen_X;
			world_Y = map->cameraY - (console->h / 2) + screen_Y;
			if (map->inBounds(world_X, world_Y))
			{
				console->at(screen_X, screen_Y).ch = (*map->tiles[world_X][world_Y]).character;
				console->at(screen_X, screen_Y).fg = (*map->tiles[world_X][world_Y]).color;
			}
		}
	}
}

// Draw a string at a location on screen
void TileRender::draw_screen_text(std::string text, int x, int y)
{
	tcod::print((*console), { x, y }, text, WHITE, BLACK);
}

// Draw a string at a map location
void TileRender::draw_world_text(std::string text, GameMap* map, int x, int y)
{
	int screen_X = x - map->cameraX + (console->w / 2), screen_Y = y - map->cameraY + (console->h / 2);
	if (inCamBounds(map, screen_X, screen_Y))
		tcod::print((*console), { screen_X, screen_Y }, text, WHITE, BLACK);
}

