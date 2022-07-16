#pragma once

// Forward Declarations
// List of used components
class Task;
class Skills;

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

		int character;
		tcod::ColorRGB color;
		bool solid;

		//Components
		Task* task = nullptr;
		Skills* skills = nullptr;

		//Skills

		Entity(int x, int y, int ch, const tcod::ColorRGB col, bool solid) : x(x), y(y), character(ch), color(col), solid(solid){}

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