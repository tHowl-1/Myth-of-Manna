#pragma once

// Dependancies
#include <libtcod.hpp>
#include <SDL2/SDL.h>

namespace crp
{
	class Entity
	{
	public:
		int x;
		int y;
		int character;
		tcod::ColorRGB color;

		Entity(int x, int y, int ch, const tcod::ColorRGB col) : x(x), y(y), character(ch), color(col){}
	};

	//class Actor : public Entity

	//class Item : public Entity
}