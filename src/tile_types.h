#pragma once

// Dependancies
#include "palette.h"
#include "tile.h"
#include "cp_437.h"

namespace mom
{
	static MapTile wall(false, ord("#"), BROWN);
	static MapTile floor(true, ord("."), DK_GRAY);

	static MapTile red(true, ord("█"), RED);
	static MapTile green(true, ord("█"), GREEN);
	static MapTile blue(true, ord("█"), BLUE);
	static MapTile yellow(true, ord("█"), YELLOW);

	static WorldTile plains(true, ord("█"), GREEN, true, false);
	static WorldTile rock(true, ord("^"), BROWN, false, true);
	static WorldTile water(false, ord("~"), BLUE, false, false);
}