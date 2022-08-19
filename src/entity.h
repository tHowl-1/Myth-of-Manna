#pragma once

// Dependancies
#include <libtcod.hpp>
#include <SDL2/SDL.h>

#include "event.h"

#include "components/world.h"
#include "components/physics.h"
#include "components/render.h"

const int MAX_MEMBERS = 6;

//Ai*			ai				= nullptr;
//Consumable*	consumable		= nullptr;
//Equippable*	equippable		= nullptr;
//Inventory*	inventory		= nullptr;
//Interactable* interactable	= nullptr;
//Soul*			soul			= nullptr;

namespace mom
{
	class Entity
	{
	public:
		//Components
		WorldC world;
		PhysicsC physics;
		RenderC render;

		Entity() {}
		Entity(
			WorldC world,
			PhysicsC physics,
			RenderC render)
			:
			world(world),
			physics(physics),
			render(render)
		{}

		void eventPass(Event* actionEvent);

	};
}