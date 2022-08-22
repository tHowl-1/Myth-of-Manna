#pragma once

// Dependancies
#include <libtcod.hpp>
#include <SDL2/SDL.h>
#include <optional>

#include "event.h"

#include "components/world.h"
#include "components/physics.h"
#include "components/render.h"
#include "components/open.h"
#include "components/heal.h"
#include "components/inventory.h"
#include "components/description.h"

enum RenderPos:char
{
	Object,
	Item,
	Corpse,
	Actor,
};

const int MAX_MEMBERS = 6;

//Ai*			ai				= nullptr;
//Inventory*	inventory		= nullptr;
//Soul*			soul			= nullptr;

namespace mom
{
	class Entity
	{
	public:
		RenderPos sortPosition;

		//Components
		PhysicsC physics;
		RenderC render;
		DescriptionC description;
		WorldC world;
		OpenC open;
		HealC heal;
		InventoryC inventory;

		Entity() {}
		Entity(
			RenderPos sortPosition,
			PhysicsC physics,
			RenderC render,
			DescriptionC description,
			WorldC world,
			OpenC open,
			HealC heal,
			InventoryC inventory)
			:
			sortPosition(sortPosition),
			physics(physics),
			render(render),
			description(description),
			world(world),
			open(open),
			heal(heal),
			inventory(inventory)
		{}

		void eventPass(Event* actionEvent);

	};
}