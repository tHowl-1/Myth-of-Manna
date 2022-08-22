#pragma once

#include <string>

#include "../event.h"

const int MAX_ITEMS = 10;

using namespace mom;

namespace mom
{
	class Entity;

	class InventoryC
	{
	public:
		bool null = false;

		Entity* storedEntities[MAX_ITEMS];
		
		int size;

		int currentSize = 0;

		InventoryC() : null(true)
		{
			for (int i = 0; i < MAX_ITEMS; i++) {
				storedEntities[i] = nullptr;
			}
		}

		InventoryC(int size) : size((size > MAX_ITEMS) ? MAX_ITEMS : size) {
			for (int i = 0; i < MAX_ITEMS; i++) {
				storedEntities[i] = nullptr;
			}
		}

		void receiveEvent(Event* actionEvent)
		{
			switch (actionEvent->type)
			{
			case RetrieveEvent:
				actionEvent->thing = storedEntities[currentSize - 1];
				storedEntities[currentSize - 1] = nullptr;
				currentSize--;
				break;
			case FillEvent:
				storedEntities[currentSize] = (Entity*)actionEvent->thing;
				currentSize++;
				break;
			case IndexRetrieveEvent:
				// TODO - IMPLEMENT
				break;
			default:
				break;
			}
		}
	};
}
