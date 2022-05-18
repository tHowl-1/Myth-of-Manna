#include "palette.h"

#include "render.h"

using namespace crp;

// Draw all entities in a scene
void TileRender::draw_entities(Scene* scene)
{
	for (Entity* entity : scene->entities)
	{
		// TODO - Replace this function with a console tile access change
		tcod::print(*console, { entity->x, entity->y }, entity->ch, *(entity->color), BLACK);
	}
}