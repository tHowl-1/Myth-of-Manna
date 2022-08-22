#include "palette.h"
#include "event.h"
#include "logging.h"
#include <sstream>

#include "rendering.h"

using namespace mom;

void TileRender::draw_entities(Map* map)
{
	int world_X, world_Y;
	int screen_X, screen_Y;

	for (Entity* entity : map->activeEntityPointers)
	{
		Event renderEvent = Event(RenderEvent);
		entity->eventPass(&renderEvent);
		world_X = renderEvent.x;
		world_Y = renderEvent.y;
		screen_X = world_X + MAP_OFFSET;
		screen_Y = world_Y + MAP_OFFSET;

		console->at(screen_X, screen_Y).ch = renderEvent.character;
		console->at(screen_X, screen_Y).fg = renderEvent.color;
	}
}

void TileRender::draw_map_tiles(Map* map, int offset)
{
	int screen_X, screen_Y;
	for (int world_X = 0; world_X < TILED_SIZE; world_X++)
	{
		for (int world_Y = 0; world_Y < TILED_SIZE; world_Y++)
		{
			screen_X = world_X + MAP_OFFSET + offset;
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

	{
		Event renderEvent = Event(WorldRenderEvent);
		world->player.eventPass(&renderEvent);
		world_X = renderEvent.x;
		world_Y = renderEvent.y;
		screen_X = world_X + MAP_OFFSET;
		screen_Y = world_Y + MAP_OFFSET;

		console->at(screen_X, screen_Y).ch = renderEvent.character;
		console->at(screen_X, screen_Y).fg = renderEvent.color;
	}
}

void TileRender::draw_world_tiles(World* world, int offset)
{
	int screen_X, screen_Y;
	for (int world_X = 0; world_X < TILED_SIZE; world_X++)
	{
		for (int world_Y = 0; world_Y < TILED_SIZE; world_Y++)
		{
			screen_X = world_X + MAP_OFFSET + offset;
			screen_Y = world_Y + MAP_OFFSET;

			console->at(screen_X, screen_Y).ch = world->worldTiles[world_X][world_Y].character;
			console->at(screen_X, screen_Y).fg = world->worldTiles[world_X][world_Y].color;
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

void TileRender::draw_check_box(bool value, int x, int y)
{
	int screen_X = x;
	int screen_Y = y;
	console->at(screen_X, screen_Y).fg = WHITE;
	if (value)
		console->at(screen_X, screen_Y).ch = ord("◘");
	else
		console->at(screen_X, screen_Y).ch = ord("•");
}

void TileRender::draw_progress_bar(float value, int x, int y, int w)
{
	int screen_X = x;
	int screen_Y = y;
	console->at(screen_X, screen_Y).ch = ord("[");
	console->at(screen_X, screen_Y).fg = WHITE;
	for (int i = 1; i < w - 1; i++)
	{
		console->at(screen_X + i, screen_Y).fg = WHITE; 
		if (i <= int(value * (w - 2))) //
			console->at(screen_X + i, screen_Y).ch = ord("■");
		else
			console->at(screen_X + i, screen_Y).ch = ord("·");
	}
	console->at(screen_X + w - 1, screen_Y).ch = ord("]");
	console->at(screen_X + w - 1, screen_Y).fg = WHITE;
}

void TileRender::draw_panel(int x, int y, int w, int h)
{
	tcod::draw_frame(*console, { x, y, w, h }, { ord("╔"), ord("═"), ord("╗"), ord("║"), ord(" "), ord("║"), ord("╚"), ord("═"), ord("╝") }, { { 255, 255, 255 } }, { {0, 0, 0} });
}

void TileRender::draw_messages(int x, int y, int h)
{
	int position = 0;
	for (auto messageIterator = MessageLog::getInstance().log.begin(); messageIterator != MessageLog::getInstance().log.end(); messageIterator++)
	{
		if (position > h)
			break;
		Message currentMessage = *messageIterator;
		std::stringstream stream(currentMessage.messageText);
		tcod::print((*console), { x, y - position }, currentMessage.messageText + " x" + std::to_string(currentMessage.count), currentMessage.messageColor, BLACK);
		position++;
	}
}

void TileRender::draw_inventory_list(World* world, int x, int y, int h)
{
	int position = 0;
	for (auto item : world->player.inventory.storedEntities)
	{
		tcod::print((*console), { x, y + position }, item->description.name, WHITE, BLACK);
		position += 2;
	}
}
