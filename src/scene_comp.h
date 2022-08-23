#pragma once;

namespace mom
{
	struct TilePosition
	{
		int x;
		int y;

		int id;

		TilePosition() : x(0), y(0), id(0) {}
		TilePosition(int x, int y, int id) : x(x), y(y), id(id) {}
	};

	struct PathTile
	{
		bool river;
		bool path;
		bool road;
	};

	struct Params
	{
		// World Generation Paramaters:
		bool island = true;
		bool polar = true;
		bool roads = true;
		bool rivers = true;

		float population = 1.0f;

		float height = 1.0f;
		float temperature = 1.0f;
		float roughness = 1.0f;
		float moisture = 1.0f;
		float sealevel = 1.0f;

		Params() {}
		Params(const Params& oldParams)
		{
			island = oldParams.island;
			polar = oldParams.polar;
			roads = oldParams.roads;
			population = oldParams.population;
			rivers = oldParams.rivers;
			height = oldParams.height;
			temperature = oldParams.temperature;
			roughness = oldParams.roughness;
			sealevel = oldParams.sealevel;

		}
	};
}