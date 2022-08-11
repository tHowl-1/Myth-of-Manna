#pragma once

// Dependancies
#include <libtcod.hpp>
#include <SDL2/SDL.h>

#include "event.h"

const int MAX_MEMBERS = 6;

namespace mom
{
	class Physics;
	class Render;

	class Entity
	{
	public:
		//Components
		Physics*	physics		= nullptr;
		//Ai*			ai				= nullptr;
		//Consumable*	consumable		= nullptr;
		//Equippable*	equippable		= nullptr;
		//Inventory*	inventory		= nullptr;
		//Interactable* interactable	= nullptr;
		//Soul*			soul			= nullptr;
		Render*		render		= nullptr;

		Entity(
			Physics* physics,
			//Ai* ai,
			//Consumable* consumable,
			//Equippable* equippable,
			//Inventory* inventory,
			//Interactable* interactable,
			//Soul* soul,
			Render* render)
			:
			physics(physics),
			//ai(ai),
			//consumable(consumable),
			//equippable(equippable),
			//inventory(inventory),
			//interactable(interactable),
			//soul(soul),
			render(render)
		{}

		~Entity();
		

		void eventPass(Event* actionEvent);

	};

	class Party
	{
	public:
		bool inMap = false;
		Entity* partyMembers[MAX_MEMBERS];

		//Components
		Physics* physics = nullptr;
		Render* render = nullptr;
		/*class Group* group = nullptr;*/

		Party(
			Physics* physics,
			//Group* group,
			Render* render)
			:
			physics(physics),
			//group(group),
			render(render)
		{}

		~Party();

		void eventPass(Event* actionEvent);

	};
}