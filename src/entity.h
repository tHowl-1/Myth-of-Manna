#pragma once

// Forward Declarations
// List of used components
class Ai;
class Consumable;
class Equippable;
class Interactable;
class Inventory;
class Soul;

// Dependancies
#include <libtcod.hpp>
#include <SDL2/SDL.h>

const int MAX_MEMBERS = 6;

namespace crp
{
	class Entity
	{
	public:
		//Basic attributes
		int x;
		int y;

		int dx = 0;
		int dy = 0;

		int health = 25;

		int baseCharacter;
		tcod::ColorRGB baseColor;

		int character;
		tcod::ColorRGB color;

		bool solid;

		//Components
		Ai* ai = nullptr;
		Consumable* consumable = nullptr;
		Equippable* equippable = nullptr;
		Inventory* inventory = nullptr;
		Interactable* interactable = nullptr;
		Soul* soul = nullptr;

		//Skills

		Entity(int x, int y, int ch, const tcod::ColorRGB col, bool solid) : x(x), y(y), baseCharacter(ch), character(ch), baseColor(col), color(col), solid(solid){}

		void move(int dx, int dy);
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