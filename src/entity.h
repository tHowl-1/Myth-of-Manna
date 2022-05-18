#pragma once

// Dependancies
#include <string>
#include <libtcod.hpp>
#include <SDL2/SDL.h>

namespace crp
{
	class Entity
	{
	public:
		int x;
		int y;
		std::string ch;
		const tcod::ColorRGB* color; // TODO - If we want dynamic coloring this will have to be non-const and not a pointer...

		Entity(int x, int y, std::string ch, const tcod::ColorRGB* col) : x(x), y(y), ch(ch), color(col){}
	};

	//class Actor : public Entity

	//class Item : public Entity
}