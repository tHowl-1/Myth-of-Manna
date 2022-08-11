#pragma once

namespace mom
{
	class World;
	class Map;
	class Params;
	class Entity;
	struct Region;

	class MapGenerator
	{
	public:
		World* generateWorld(Params* params, Entity* player)
		{
			TCODHeightMap worldHeightMap(TILED_SIZE, TILED_SIZE);

			TCODNoise* noise2d = new TCODNoise(2);
			noise2d->setType(TCOD_NOISE_SIMPLEX);

			for (int i = 0; i < 50; i++)
			{
				for (int j = 0; j < 50; j++)
				{
					float p[2] = { (float(i) + 0.1f) / 15, (float(j) + 0.1f) / 15 };
					float heightVal = noise2d->getFbm(p, 32.0f);
					worldHeightMap.setValue(i, j, heightVal);
				}
			}
			delete noise2d;
			return new World(&worldHeightMap, player);
		}
		

		Map* generateMap(Region* region)
		{
			return nullptr;
		}
	};

}