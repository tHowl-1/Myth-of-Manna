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
			static TCODRandom* defaultGenerator = TCODRandom::getInstance();
			const int heightMapDimension = TILED_SIZE;
			TCODHeightMap worldHeightMap(heightMapDimension, heightMapDimension);

			TCODNoise* noise2d = new TCODNoise(2);
			noise2d->setType(TCOD_NOISE_SIMPLEX);

			for (int i = 0; i < heightMapDimension; i++)
			{
				for (int j = 0; j < heightMapDimension; j++)
				{
					float p[2] = { (float(i) + 0.1f) / 15, (float(j) + 0.1f) / 15 };
					float heightVal = noise2d->getFbm(p, 32.0f);
					worldHeightMap.setValue(i, j, heightVal);
				}
			}
			delete noise2d;

			worldHeightMap.normalize(0.0f, 1.0f);

			return new World(&worldHeightMap, player);
		}
		

		Map* generateMap(Region* region)
		{
			return nullptr;
		}
	};

}