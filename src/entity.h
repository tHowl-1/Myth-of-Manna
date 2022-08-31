#pragma once

// Dependancies
#include <libtcod.hpp>
#include <SDL2/SDL.h>
#include <optional>

#include "components/world.h"
#include "components/physics.h"
#include "components/render.h"
#include "components/open.h"
#include "components/heal.h"
#include "components/inventory.h"
#include "components/description.h"
#include "components/stats.h"

/// <summary>
/// The entity class is the main representation of items, objects, and actors in the game.
/// </summary>

enum RenderPos:char
{
	Object,
	Item,
	Corpse,
	Actor,
};

const int MAX_MEMBERS = 6;

//Ai*			ai				= nullptr;

namespace mom
{
	// Forward Declarations
	class Event;

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
		StatsC stats;


		Entity()
		{
			sortPosition = Object;
			physics = PhysicsC();
			render = RenderC();
			description = DescriptionC();
			world = WorldC();
			open = OpenC();
			heal = HealC();
			inventory = InventoryC();
			stats = StatsC();
		}
		Entity(
			RenderPos sortPosition,
			PhysicsC physics,
			RenderC render,
			DescriptionC description,
			WorldC world,
			OpenC open,
			HealC heal,
			InventoryC inventory,
			StatsC stats)
			:
			sortPosition(sortPosition),
			physics(physics),
			render(render),
			description(description),
			world(world),
			open(open),
			heal(heal),
			inventory(inventory),
			stats(stats)
		{}
		Entity(const Entity& oldEntity)
		{
			sortPosition = oldEntity.sortPosition;
			physics = oldEntity.physics;
			render = oldEntity.render;
			description = oldEntity.description;
			world = oldEntity.world;
			open = oldEntity.open;
			heal = oldEntity.heal;
			inventory = oldEntity.inventory;
			stats = oldEntity.stats;
		}

		void eventPass(Event* actionEvent);

	};
}