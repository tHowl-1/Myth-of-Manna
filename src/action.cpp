#include "action.h"

#include "entity.h"
#include "scene.h"
#include "scene_comp.h"
#include "mapgen.h"
#include "entity_types.h"
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
	performer->eventPass(&mapMovementEvent);
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
	world->player.eventPass(&worldMovementEvent);
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
	// Get Player Performer and Direction
	Event positionEvent = Event(PositionEvent);
	performer->eventPass(&positionEvent);
	int dest_x = positionEvent.x + positionEvent.dx, dest_y = positionEvent.y + positionEvent.dy;

	map->mapTiles[dest_x][dest_y] = woodWall;
	return Validate::INVALID;
}

Validate SpawnPotionAction::perform()
{
	//Get Performer Position
	Event positionEvent = Event(PositionEvent);
	performer->eventPass(&positionEvent);

	map->spawn_entity_copy_at(Potion, positionEvent.x, positionEvent.y);
	MessageLog::getInstance().writeMessage(performer->description.name + " spawns a " + Potion.description.name + "!", WHITE);
	return Validate::VALID;
}

Validate GrabAction::perform()
{
	// Get Performer Position
	Event positionEvent = Event(PositionEvent);
	performer->eventPass(&positionEvent);
	
	// Fill Inventory
	Event inventoryFillEvent = Event(FillEvent);
	inventoryFillEvent.thing = map->get_entity_at_location(performer, positionEvent.x, positionEvent.y);
	if (inventoryFillEvent.thing != nullptr)
	{
		if (performer->inventory.storedEntities.size() >= performer->inventory.maxSize) {
			MessageLog::getInstance().writeMessage(performer->description.name + "'s inventory is full!", WHITE);
			return Validate::INVALID;
		}

		performer->eventPass(&inventoryFillEvent);

		// Emplace element into inventory
		Entity* item = (Entity*)inventoryFillEvent.thing;
		Event hideEvent = Event(ShowEvent);
		item->eventPass(&hideEvent);

		MessageLog::getInstance().writeMessage(performer->description.name + " picks up " + item->description.name, WHITE);

		// Remove element from active and static storage
		for (auto iterator = map->activeEntityPointers.begin(); iterator != map->activeEntityPointers.end(); iterator++) {
			if (*iterator == item) {
				map->activeEntityPointers.erase(iterator);
				break;
			}
		}
		for (auto iterator = map->staticEntityStorage.begin(); iterator != map->staticEntityStorage.end(); iterator++) {
			if (&(*iterator) == item) {
				map->staticEntityStorage.erase(iterator);
				break;
			}
		}
		return Validate::VALID;
	}
	MessageLog::getInstance().writeMessage("Nothing to pick up!", WHITE);
	return Validate::INVALID;
}

Validate DropAction::perform()
{
	//Get Performer Position
	/*Event positionEvent = Event(PositionEvent);
	performer->eventPass(&positionEvent);

	Event inventoryIndexRetrieveEvent = Event(IndexRetrieveEvent);
	inventoryIndexRetrieveEvent.amount = choice;
	performer->eventPass(&inventoryIndexRetrieveEvent);

	if (inventoryIndexRetrieveEvent.thing != nullptr)
	{
		Entity* item = (Entity*)inventoryIndexRetrieveEvent.thing;

		Event showEvent = Event(ShowEvent);
		item->eventPass(&showEvent);

		positionEvent.type = MovementEvent;
		item->eventPass(&positionEvent);
	}*/
	return Validate::VALID;
}

Validate DumpAction::perform()
{
	//Get Player Position
	//Event positionEvent = Event(PositionEvent);
	//performer->eventPass(&positionEvent);

	//// Fill Inventory
	//Event inventoryRetrieveEvent = Event(RetrieveEvent);
	//performer->eventPass(&inventoryRetrieveEvent);
	//if (inventoryRetrieveEvent.thing != nullptr)
	//{
	//	Entity* item = (Entity*)inventoryRetrieveEvent.thing;

	//	Event showEvent = Event(ShowEvent);
	//	item->eventPass(&showEvent);
	//	
	//	positionEvent.type = MovementEvent;
	//	item->eventPass(&positionEvent);
	//}
	return Validate::VALID;
}


