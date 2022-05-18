#include "palette.h"

#include "render.h"

using namespace crp;

void TileRender::draw_entities(Scene* scene)
{
	for (Entity* entity : scene->entities)
	{
		tcod::print(*console, { entity->x, entity->y }, entity->ch, WHITE, BLACK);
	}
}