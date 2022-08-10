#include "action.h"
#include "components/physics.h"
#include "components/render.h"

using namespace mom;

Validate Action::perform()
{
	return Validate::INVALID; // Always invalid because this is a blank action
}

Validate MapMovementAction::perform()
{
	// Get Player Position
	Event* positionEvent = new Event(PositionEvent);
	performer->eventPass(positionEvent);
	int dest_x = positionEvent->x + dx, dest_y = positionEvent->y + dy;
	delete positionEvent;

	// Check collision
	Event* collideEvent = new Event(CollideEvent, dest_x, dest_y);
	bool collideFail = false;
	if (!map->inBounds(dest_x, dest_y))
		collideFail = true;
	if (!map->mapTiles[dest_x][dest_y].walkable)
		collideFail = true;
	map->mapEventPass(collideEvent);
	if (!collideEvent->check)
		collideFail = true;
	delete collideEvent;
	if (collideFail)
		return Validate::INVALID;

	// Move player in given direction
	Event* movementEvent = new Event(MovementEvent, dest_x, dest_y, dx, dy);
	map->mapEventPass(movementEvent);
	delete movementEvent;
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
	Entity* player = new Entity(new Physics(0, 0, true), new Render(ord("@"), WHITE));
	delete *world;
	*world = new World(player, new Params(true, false));
	return Validate::INVALID;
}

Validate MeleeAction::perform()
{


	// TODO - check currently held weapon
	return Validate::VALID;
}

Validate BumpAction::perform()
{
	//int dest_x = entity->x + dx, dest_y = entity->y + dy;
	//if (map->get_blocking_entity(dest_x, dest_y))
	//	return MeleeAction(entity, map, dx, dy).perform();
	//else
	return MapMovementAction(performer, map, dx, dy).perform();
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
	// Get Player Position and Direction
	Event* positionEvent = new Event(PositionEvent);
	performer->eventPass(positionEvent);
	int dest_x = positionEvent->x + positionEvent->dx, dest_y = positionEvent->y + positionEvent->dy;
	delete positionEvent;

	map->mapTiles[dest_x][dest_y] = wall;
	return Validate::INVALID;
}

