#pragma once

// Dependancies
#include <libtcod.hpp>
#include <SDL2/SDL.h>

#include "event.h"

const int MAX_MEMBERS = 6;

namespace mom
{
	class Entity
	{
	public:
		//Components
		class Physics*		physics		= nullptr;
		//Ai*			ai				= nullptr;
		//Consumable*	consumable		= nullptr;
		//Equippable*	equippable		= nullptr;
		//Inventory*	inventory		= nullptr;
		//Interactable* interactable	= nullptr;
		//Soul*			soul			= nullptr;
		class Render*		render		= nullptr;

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

		~Entity()
		{
			delete physics;
			delete render;
		}

		void eventPass(Event* actionEvent);

	};

	class Party
	{
	public:
		Entity* partyMembers[MAX_MEMBERS];
		bool inMap = false;

		int x;
		int y;

		int dx = 0;
		int dy = 0;

		int character;
		tcod::ColorRGB color;
		bool solid;

		Party();

		void move(int dx, int dy);
	};
}