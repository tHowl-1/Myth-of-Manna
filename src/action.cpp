#include "action.h"

using namespace crp;

Validate Action::perform()
{
	return Validate::INVALID; // Always invalid because this is a blank action
}

Validate MovementAction::perform()
{
	// Check collision
	if (map->tiles[entity->x + dx][entity->y + dy].walkable == false)
		return Validate::INVALID;

	// Move player in given direction
	entity->x += dx;
	entity->y += dy;
	return Validate::VALID;
}

Validate QuitAction::perform()
{
	// TODO - Add autosaving
	return Validate::QUIT;
}