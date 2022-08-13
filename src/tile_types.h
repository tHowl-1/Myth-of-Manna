#pragma once

// Dependancies
#include "palette.h"
#include "tile.h"
#include "cp_437.h"

namespace mom
{
	// WORLD TILES
	static WorldTile forest("Forest", ord("♠"), GREEN, false, true, true);
	static WorldTile grassland("Grassland", ord("\""), LT_GREEN, false, true, false);
	static WorldTile scrubland("Grassland", ord("ⁿ"), LT_GREEN, false, true, false);

	static WorldTile deepOcean("Deep Ocean", ord("~"), BLUE, true, false, false);
	static WorldTile shallowOcean("Shallow Ocean", ord("≈"), LT_BLUE, true, false, false);
	
	//static WorldTile poison("Poison", ord("-"), PURPLE, false, true, false);
	static WorldTile desert("Desert", ord("~"), TAN, false, true, false);

	static WorldTile mountains("Mountains", ord("▲"), WHITE, false, false, false);
	static WorldTile rocky("Rocky", ord("▲"), DK_GRAY, false, false, false);

	static WorldTile river("River", ord("."), BLUE, true, false, false);
	static WorldTile path("Path", ord("."), BROWN, false, true, false);
	static WorldTile road("Road", ord("."), DK_GRAY, false, true, false);

	static WorldTile hub("Hub", ord("X"), RED, false, true, false);
	static WorldTile riverHead("River Head", ord("X"), PURPLE, false, true, false);



	// MAP TILES
	static Tile wall(false, ord("#"), BROWN);
	static Tile floor(true, ord("."), DK_GRAY);

	static Tile red(true, ord("█"), RED);
	static Tile green(true, ord("█"), GREEN);
	static Tile blue(true, ord("█"), BLUE);
	static Tile yellow(true, ord("█"), YELLOW);
}