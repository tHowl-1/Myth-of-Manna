#pragma once

// Dependancies
#include "palette.h"
#include "tile.h"
#include "cp_437.h"

namespace mom
{
	static Tile wall(false, ord("#"), BROWN);
	static Tile floor(true, ord("."), DK_GRAY);

	static Tile red(true, ord("█"), RED);
	static Tile green(true, ord("█"), GREEN);
	static Tile blue(true, ord("█"), BLUE);
	static Tile yellow(true, ord("█"), YELLOW);
}