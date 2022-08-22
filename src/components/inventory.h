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

		InventoryC() : null(true) {}
		InventoryC(int size) : size((size > MAX_ITEMS) ? MAX_ITEMS : size) {}

		void receiveEvent(Event* actionEvent)
		{
			switch (actionEvent->type)
			{
			case RetrieveEvent:
				
				currentSize--;
				break;
			case FillEvent:

				currentSize++;
				break;
			default:
				break;
			}
		}
	};
}
