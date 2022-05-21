#include "palette.h"

#include "render.h"

using namespace crp;

// Draw all entities in a scene
void TileRender::draw_entities(Scene* scene)
{
	for (Entity* entity : scene->entities)
	{
		console->at(entity->x, entity->y).ch = entity->character;
		console->at(entity->x, entity->y).fg = entity->color;
	}
}

// Draw all tiles in a scene
void TileRender::draw_tiles(GameMap* map)
{
	for (int i = 0; i < map->width; i++)
	{
		for (int j = 0; j < map->height; j++)
		{
			console->at(i, j).ch = map->tiles[i][j].character;
			console->at(i, j).fg = map->tiles[i][j].color;
		}
	}

}

// Draw a string at a location on screen
void TileRender::draw_text(std::string text, int x, int y)
{
	tcod::print((*console), { x, y }, text, WHITE, BLACK);
}