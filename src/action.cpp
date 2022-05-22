#include "action.h"
#include <iostream>
using namespace crp;

Validate Action::perform()
{
	return Validate::INVALID; // Always invalid because this is a blank action
}

Validate CameraMovementAction::perform()
{
	if (!map->cameraLock)
	{
		map->cameraX += dx;
		map->cameraY += dy;
	}
	return Validate::INVALID;
}

Validate CameraLockAction::perform()
{
	if (map->cameraLock)
		map->cameraLock = false;
	else
	{
		map->cameraLock = true;
		map->cameraX = entity->x;
		map->cameraY = entity->y;
	}
	return Validate::INVALID;
}

Validate MovementAction::perform()
{
	// Check collision
	if (!map->tiles[entity->x + dx][entity->y + dy].walkable)
		return Validate::INVALID;

	// Move player in given direction
	entity->x += dx;
	entity->y += dy;
	if (map->cameraLock)
	{
		map->cameraX = entity->x;
		map->cameraY = entity->y;
	}
	return Validate::VALID;
}

Validate QuitAction::perform()
{
	// TODO - Add autosaving
	return Validate::QUIT;
}