#include "action.h"
#include "components/physics.h"
#include "components/render.h"
#include "mapgen.h"
#include "logging.h"
#include "game_exceptions.h"

using namespace mom;

Validate Action::perform()
{
	return Validate::INVALID; // Always invalid because this is a blank action
}

Validate MapMovementAction::perform()
{
	// Set Player Direction
	Event mapMovementEvent = Event(DirectionEvent, 0, 0, dx, dy);
	performer->eventPass(&mapMovementEvent);

	// Get Player Position and Direction
	mapMovementEvent.type = PositionEvent;
	performer->eventPass(&mapMovementEvent);
	int dest_x = mapMovementEvent.x + mapMovementEvent.dx, dest_y = mapMovementEvent.y + mapMovementEvent.dy;

	// Check collision
	mapMovementEvent.type = CollideEvent;
	bool collideFail = false;
	if (!map->inBounds(dest_x, dest_y))
		collideFail = true;
	else if (!map->mapTiles[dest_x][dest_y].walkable)
		collideFail = true;
	map->eventPass(&mapMovementEvent);
	if (!mapMovementEvent.check)
		collideFail = true;
	if (collideFail)
		return Validate::INVALID;

	// Move player in given direction
	mapMovementEvent.type = MovementEvent;
	map->eventPass(&mapMovementEvent);
	return Validate::VALID;
}

Validate WorldMovementAction::perform()
{
	// Set Party Direction
	Event worldMovementEvent = Event(WorldDirectionEvent, 0, 0, dx, dy);
	world->player.eventPass(&worldMovementEvent);

	// Get Party Position and Direction
	worldMovementEvent.type = WorldPositionEvent;
	world->player.eventPass(&worldMovementEvent);
	int dest_x = worldMovementEvent.x + worldMovementEvent.dx, dest_y = worldMovementEvent.y + worldMovementEvent.dy;

	// Check collision
	if (!world->inBounds(dest_x, dest_y))
		return Validate::INVALID; // Out of bounds
	if (!world->worldTiles[dest_x][dest_y].walkable)
		return Validate::INVALID; // Blocked by water

	//Message Writing
	std::string strDirection = "ERROR";
	if (dx == 0 && dy == -1)
		strDirection = "north";
	else if (dx == 0 && dy == 1)
		strDirection = "south";
	else if (dx == -1 && dy == 0)
		strDirection = "west";
	else if (dx == 1 && dy == 0)
		strDirection = "east";

	MessageLog::getInstance().writeMessage("You move " + strDirection, WHITE);

	// Move player in given direction
	worldMovementEvent.type = WorldMovementEvent;
	world->eventPass(&worldMovementEvent);
	return Validate::VALID;
}

Validate WorldCreateAction::perform()
{
	delete *world;
	MapGenerator newWorldGen = MapGenerator();
	*world = newWorldGen.generateWorld(params);
	MessageLog::getInstance().clearLog();
	delete params;
	return Validate::INVALID;
}

Validate MeleeAction::perform()
{
	// TODO - check currently held weapon
	return Validate::VALID;
}

Validate BumpAction::perform()
{
	return MapMovementAction(performer, map, dx, dy).perform();
}

Validate QuitAction::perform()
{
	// TODO - Add autosaving
	return Validate::QUIT;
}

Validate EnterMapAction::perform()
{
	Event enterEvent = Event(EnterWorldEvent);
	world->player.eventPass(&enterEvent);
	world->get_active_map()->activeEntityPointers.push_back(&world->player);
	return Validate::INVALID;
}

Validate ExitMapAction::perform()
{
	Event exitEvent = Event(ExitWorldEvent);
	world->player.eventPass(&exitEvent);
	return Validate::INVALID;
}

Validate PlaceTileAction::perform()
{
	// Get Player Position and Direction
	Event positionEvent = Event(PositionEvent);
	performer->eventPass(&positionEvent);
	int dest_x = positionEvent.x + positionEvent.dx, dest_y = positionEvent.y + positionEvent.dy;

	map->mapTiles[dest_x][dest_y] = woodWall;
	return Validate::INVALID;
}


