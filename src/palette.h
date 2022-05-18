#pragma once
// Header to store colors by name

#include <libtcod.hpp>

namespace crp
{
	// Wad's optimum 16 color palette:
	const static tcod::ColorRGB BLACK{0, 0, 0};
	const static tcod::ColorRGB DK_GRAY{ 87, 87, 87 };
	const static tcod::ColorRGB RED{ 173, 35, 35 };
	const static tcod::ColorRGB BLUE{ 42, 75, 215 };
	const static tcod::ColorRGB GREEN{ 29, 105, 20 };
	const static tcod::ColorRGB BROWN{ 129, 74, 25 };
	const static tcod::ColorRGB PURPLE{ 129, 38, 192 };
	const static tcod::ColorRGB LT_GRAY{ 160, 160, 160 };
	const static tcod::ColorRGB LT_GREEN{ 129, 197, 122 };
	const static tcod::ColorRGB LT_BLUE{ 157, 175, 255 };
	const static tcod::ColorRGB CYAN{ 41, 208, 208 };
	const static tcod::ColorRGB ORANGE{ 255, 146, 51 };
	const static tcod::ColorRGB YELLOW{ 255, 238, 51 };
	const static tcod::ColorRGB TAN{ 233, 22, 187 };
	const static tcod::ColorRGB PINK{ 255, 205, 243 };
	const static tcod::ColorRGB WHITE{ 255, 255, 255 };
}