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
		tcod::ColorRGB color;

		Entity(int x, int y, std::string ch, tcod::ColorRGB col) : x(x), y(y), ch(ch), color(col){}
	};

	//class Actor : public Entity

	//class Item : public Entity
}