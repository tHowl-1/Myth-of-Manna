#include "action.h"

using namespace crp;

Validate Action::perform()
{
	return Validate::INVALID; // Always invalid because this is a blank action
}

Validate MapMovementAction::perform()
{
	int dest_x = entity->x + dx, dest_y = entity->y + dy;
	// Check collision
	if (!map->inBounds(dest_x, dest_y))
		return Validate::INVALID; // Out of bounds
	if (!map->mapTiles[dest_x][dest_y].walkable)
		return Validate::INVALID; // Blocked by a tile
	if (map->get_blocking_entity(dest_x, dest_y) != nullptr)
		return Validate::INVALID;

	// Move player in given direction
	entity->move(dx, dy);
	entity->dx = dx;
	entity->dy = dy;
	return Validate::VALID;
}

Validate WorldMovementAction::perform()
{
	int dest_x = party->x + dx, dest_y = party->y + dy;
	// Check collision
	if (!world->inBounds(dest_x, dest_y))
		return Validate::INVALID; // Out of bounds
	if (!world->regionTiles[dest_x][dest_y].worldTile.walkable)
		return Validate::INVALID; // Blocked by a tile

	// Move player in given direction
	party->move(dx, dy);
	party->dx = dx;
	party->dy = dy;
	return Validate::VALID;
}

Validate WorldCreateAction::perform()
{
	Entity* player = new Entity(0, 0, ord("@"), WHITE, true);
	delete *world;
	*world = new World(player, new Params(true, false));
	return Validate::INVALID;
}

Validate MeleeAction::perform()
{
	int dest_x = entity->x + dx, dest_y = entity->y + dy;
	Entity* target = map->get_blocking_entity(dest_x, dest_y);
	if (target == nullptr)
		return Validate::INVALID;

	// TODO - check currently held weapon
	return Validate::VALID;
}

Validate BumpAction::perform()
{
	int dest_x = entity->x + dx, dest_y = entity->y + dy;
	if (map->get_blocking_entity(dest_x, dest_y))
		return MeleeAction(entity, map, dx, dy).perform();
	else
		return MapMovementAction(entity, map, dx, dy).perform();
}

Validate QuitAction::perform()
{
	// TODO - Add autosaving
	return Validate::QUIT;
}

Validate EnterMapAction::perform()
{
	world->get_active_map()->activeEntities.push_back(world->player);
	world->playerParty->inMap = true;
	return Validate::INVALID;
}

Validate ExitMapAction::perform()
{
	world->get_active_map()->activeEntities.clear();
	world->playerParty->inMap = false;
	return Validate::INVALID;
}

Validate PlaceTileAction::perform()
{
	int dest_x = entity->x + dx, dest_y = entity->y + dy;
	map->mapTiles[dest_x][dest_y] = wall;
	return Validate::INVALID;
}

