#pragma once

#include <list>

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

		std::list<Entity*> storedEntities;
		
		int maxSize;

		InventoryC() : null(true) {}
		InventoryC(int size) : maxSize((size > MAX_ITEMS) ? MAX_ITEMS : size) {}
		~InventoryC();

		void receiveEvent(Event* actionEvent);
	};
}
