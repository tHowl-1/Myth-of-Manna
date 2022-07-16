#include "palette.h"

#include "render.h"

using namespace crp;



void TileRender::draw_entities(Map* map)
{
	int world_X, world_Y;
	int screen_X, screen_Y;
	for (Entity* entity : map->activeEntities)
	{
		world_X = entity->x;
		world_Y = entity->y;
		screen_X = world_X + MAP_OFFSET;
		screen_Y = world_Y + MAP_OFFSET;

		console->at(screen_X, screen_Y).ch = entity->character;
		console->at(screen_X, screen_Y).fg = entity->color;
	}
}

void TileRender::draw_map_tiles(Map* map)
{
	int screen_X, screen_Y;
	for (int world_X = 0; world_X < TILED_SIZE; world_X++)
	{
		for (int world_Y = 0; world_Y < TILED_SIZE; world_Y++)
		{
			screen_X = world_X + MAP_OFFSET;
			screen_Y = world_Y + MAP_OFFSET;
			console->at(screen_X, screen_Y).ch = map->mapTiles[world_X][world_Y].character;
			console->at(screen_X, screen_Y).fg = map->mapTiles[world_X][world_Y].color;
		}
	}
}

void TileRender::draw_parties(World* world)
{
	
	int world_X, world_Y;
	int screen_X, screen_Y;
	Party* party = world->playerParty;
	{
		world_X = party->x;
		world_Y = party->y;
		screen_X = world_X + MAP_OFFSET;
		screen_Y = world_Y + MAP_OFFSET;

		console->at(screen_X, screen_Y).ch = party->character;
		console->at(screen_X, screen_Y).fg = party->color;
	}
}

void TileRender::draw_world_tiles(World* world)
{
	int screen_X, screen_Y;
	for (int world_X = 0; world_X < TILED_SIZE; world_X++)
	{
		for (int world_Y = 0; world_Y < TILED_SIZE; world_Y++)
		{
			screen_X = world_X + MAP_OFFSET;
			screen_Y = world_Y + MAP_OFFSET;
			console->at(screen_X, screen_Y).ch = world->regionTiles[world_X][world_Y].worldTile.character;
			console->at(screen_X, screen_Y).fg = world->regionTiles[world_X][world_Y].worldTile.color;
		}
	}
}

void TileRender::draw_screen_text(std::string text, int x, int y)
{
	tcod::print((*console), { x, y }, text, WHITE, BLACK);
}

void TileRender::draw_world_text(std::string text, int x, int y)
{
	int screen_X = x + MAP_OFFSET, screen_Y = y + MAP_OFFSET;
	tcod::print((*console), { screen_X, screen_Y }, text, WHITE, BLACK);
}

void TileRender::draw_menu_marker(int choice, int x, int y, int offset)
{
	int screen_X = x - 2;
	int screen_Y = y + choice * offset;
	console->at(screen_X, screen_Y).ch = ord(">");
	console->at(screen_X, screen_Y).fg = WHITE;
}

void TileRender::draw_panel(int x, int y, int w, int h)
{
	tcod::draw_frame(*console, { x, y, w, h }, { ord("╔"), ord("═"), ord("╗"), ord("║"), ord(" "), ord("║"), ord("╚"), ord("═"), ord("╝") }, { { 255, 255, 255 } }, { {0, 0, 0} });
}