#pragma once

// Dependancies
#include "palette.h"
#include "tile.h"
#include "cp_437.h"

namespace mom
{
	// WORLD TILES
	static WorldTile deepOcean("Deep Ocean", ord("~"), BLUE, true, 0.0f);
	static WorldTile shallowOcean("Shallow Ocean", ord("≈"), LT_BLUE, true, 0.0f);

	static WorldTile forest("Forest", ord("♠"), GREEN, true,  0.5f);
	static WorldTile grassland("Grassland", ord("\""), LT_GREEN,  true,  0.75f);
	static WorldTile scrubland("Grassland", ord("ⁿ"), LT_GREEN, true, 0.75f);
	
	static WorldTile tundra("Tundra", ord("="), CYAN, true, 0.65f);
	static WorldTile taiga("Taiga", ord("↑"), GREEN,  true,  0.4f);
	static WorldTile rainforest("Rainforest", ord("Γ"), GREEN, true, 0.4f);
	static WorldTile desert("Desert", ord("~"), TAN, true, 0.5f);

	static WorldTile mountains("Mountains", ord("▲"), WHITE, true,  0.1f);
	static WorldTile rocky("Rocky", ord("▲"), DK_GRAY,  true,  0.35f);

	static WorldTile river("River", ord("."), LT_BLUE,  true, 0.25f);
	static WorldTile path("Path", ord("."), BROWN,  true, 1.0f);


	// MAP TILES
	// WALLS
	static Tile stone("Stone", false, false, false, false, ord("#"), DK_GRAY);

	static Tile castleBrick("Castle Brick", false, false, false, false, ord("#"), LT_GRAY);
	static Tile redBrick("Red Brick", false, false, false, false, ord("#"), RED);
	
	static Tile woodWall("Wood", false, false, false, true, ord("#"), BROWN);

	static Tile glass("Glass", false, false, true, false, ord("-"), CYAN);

	// FLOORS
	static Tile grass("Grass", true, false, true, true, ord("."), LT_GREEN);
	static Tile dirt("Dirt", true, false, true, false, ord("."), BROWN);
	static Tile snow("Snow", true, false, true, false, ord("."), WHITE);
	static Tile rock("Rock", true, false, true, false, ord(","), DK_GRAY);
	static Tile sand("Sand", true, false, true, false, ord("≈"), TAN);

	static Tile flower("Flowers", true, false, true, true, ord("♣"), RED);
	static Tile broadleafTree("Broadleaf Tree", false, false, true, true, ord("♠"), GREEN);
	static Tile pineTree("Pine Tree", false, false, true, true, ord("↑"), GREEN);
	static Tile palmTree("Palm Tree", false, false, true, true, ord("Γ"), GREEN);
	static Tile cactus("Cactus", false, false, true, true, ord("¥"), GREEN);
	static Tile tallGrass("Tall Grass", true, false, false, true, ord("\""), LT_GREEN);

	static Tile deepWater("Deep Water", false, true, true, false, ord("~"), BLUE);
	static Tile shallowWater("Shallow Water", true, true, true, false, ord("~"), LT_BLUE);

	static Tile woodFloor("Wood", true, false, true, true, ord("_"), BROWN);
	static Tile stoneTile("Tile", true, false, true, false, ord("_"), LT_GRAY);

	//DEBUG
	static Tile red("RED", true, false, true, false, ord("█"), RED);
	static Tile green("GREEN", true, false, true, false, ord("█"), GREEN);
	static Tile blue("BLUE", true, false, true, false, ord("█"), BLUE);
	static Tile yellow("YELLOW", true, false, true,  false, ord("█"), YELLOW);

	
}