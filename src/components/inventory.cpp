#include "inventory.h"

#include "../entity.h"
#include "../entity_types.h"

InventoryC::~InventoryC()
{
	for (auto entity : storedEntities)
		delete entity;
}

void InventoryC::receiveEvent(Event* actionEvent)
{
	switch (actionEvent->type)
	{
	/*case RetrieveEvent:
		actionEvent->thing = &storedEntities;
		break;*/
	case FillEvent:
		if (storedEntities.size() >= maxSize)
			break;
		storedEntities.push_back(new Entity(*(Entity*)actionEvent->thing));
		break;
	case IndexRetrieveEvent:
		// TODO - IMPLEMENT
		break;
	default:
		break;
	}
}