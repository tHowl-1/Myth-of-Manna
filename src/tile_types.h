#pragma once

// Dependancies
#include "palette.h"
#include "tile.h"
#include "cp_437.h"

namespace crp
{
	// TODO - Create codepoint dictionary
	static Tile wall(false, ord("#"), BROWN);
	static Tile floor(true, ord("."), DK_GRAY);
}