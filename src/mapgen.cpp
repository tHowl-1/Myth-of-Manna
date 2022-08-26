#include "mapgen.h"

#include "tile_types.h"
#include "scene_comp.h"
#include "scene.h"

// TODO - This file is hideous and needs a lot of work. For now it works reliably despite its issues.

TCODHeightMap* MapGenerator::generateGradient(bool north, bool east, bool south, bool west, bool invert)
{
	int xM = 2;
	int xA = 1;
	int yM = 2;
	int yA = 1;

	TCODHeightMap* islandGradient = new TCODHeightMap(TILED_SIZE, TILED_SIZE);
	for (int i = 0; i < TILED_SIZE; i++)
	{
		for (int j = 0; j < TILED_SIZE; j++)
		{


			float nx = ((xM * i) / float(TILED_SIZE)) - xA;
			float ny = ((yM * j) / float(TILED_SIZE)) - yA;

			float heightVal = 1 - ((1 - nx * nx) * (1 - ny * ny));
			islandGradient->setValue(i, j, heightVal);
		}
	}
	if (invert)
		islandGradient->scale(-1.0f);
	islandGradient->normalize(0.0f, 1.0f);
	return islandGradient;
}

TCODHeightMap* MapGenerator::generateIslandGradient()
{
	TCODHeightMap* islandGradient = new TCODHeightMap(TILED_SIZE, TILED_SIZE);
	for (int i = 0; i < TILED_SIZE; i++)
	{
		for (int j = 0; j < TILED_SIZE; j++)
		{
			float nx = ((2 * i) / float(TILED_SIZE)) - 1;
			float ny = ((2 * j) / float(TILED_SIZE)) - 1;
			float heightVal = 1 - ((1 - nx * nx) * (1 - ny * ny));
			islandGradient->setValue(i, j, heightVal);
		}
	}
	islandGradient->scale(-1.0f);
	islandGradient->normalize(0.0f, 1.0f);
	return islandGradient;
}

TCODHeightMap* MapGenerator::generatePolarGradient()
{
	TCODHeightMap* polarGradient = new TCODHeightMap(TILED_SIZE, TILED_SIZE);
	for (int i = 0; i < TILED_SIZE; i++)
	{
		for (int j = 0; j < TILED_SIZE; j++)
		{
			// TODO - Modify to create gradients of all sides (try nx/ny and heighval square values)
			float nx = ((2 * i) / float(TILED_SIZE)) - 1;
			float ny = ((2 * j) / float(TILED_SIZE)) - 1;
			float heightVal = 1 - ((1 - ny * ny) * (1 - ny * ny));
			polarGradient->setValue(i, j, heightVal);
		}
	}
	polarGradient->scale(-1.0f);
	polarGradient->normalize(0.0f, 1.0f);
	return polarGradient;
}

TCODHeightMap* MapGenerator::generateNoiseMap(TCODHeightMap* gradient, float frequency, float octaves, bool multiply, bool lerp)
{
	TCODNoise* noise2d = new TCODNoise(2);
	noise2d->setType(TCOD_NOISE_SIMPLEX);
	TCODHeightMap* noiseMap = new TCODHeightMap(TILED_SIZE, TILED_SIZE);
	for (int i = 0; i < TILED_SIZE; i++)
	{
		for (int j = 0; j < TILED_SIZE; j++)
		{
			float p[2] = { (float(i) + 0.1f) * frequency, (float(j) + 0.1f) * frequency };
			float noiseVal = noise2d->getFbm(p, octaves);
			noiseMap->setValue(i, j, noiseVal);
		}
	}
	delete noise2d;

	if (lerp && gradient != nullptr)
		noiseMap->lerp(noiseMap, gradient, 0.82);
	if (multiply && gradient != nullptr)
		noiseMap->multiply(noiseMap, gradient);
	noiseMap->normalize(0.0f, 1.0f);
	return noiseMap;
}

World* MapGenerator::generateWorld(Params* params)
{
	static TCODRandom* defaultGenerator = TCODRandom::getInstance();
	// Generate Terrain
	TCODHeightMap* islandGradient = nullptr;
	TCODHeightMap* polarGradient = nullptr;

	if (params->island)
		islandGradient = generateGradient(true, true, true, true, true);
	if (params->polar)
		polarGradient = generatePolarGradient();

	TCODHeightMap* heightMap = generateNoiseMap(islandGradient, 0.15f, 4.0f, false, true);
	TCODHeightMap* roughnessMap = generateNoiseMap(nullptr, 0.2f, 0.2f, false, false);
	TCODHeightMap* temperatureMap = generateNoiseMap(polarGradient, 0.07f, 2.0f, false, true);
	TCODHeightMap* moistureMap = generateNoiseMap(temperatureMap, 0.1f, 1.0f, true, false);

	// Generate Features
	TCODHeightMap* hubMap = generateNoiseMap(nullptr, 0.5f, 1.0f, false, true);
	TCODHeightMap* riverMap = generateNoiseMap(islandGradient, 0.5f, 1.0f, false, true);

	// Scale by parameters
	heightMap->add(params->height - 1.0f);
	roughnessMap->add(params->roughness - 1.0f);
	temperatureMap->normalize(params->temperature - 1.0f, params->temperature);
	moistureMap->normalize(params->moisture - 1.0f, params->moisture);


	// Populate Tilemap
	WorldTile worldTiles[TILED_SIZE][TILED_SIZE];
	{
		for (int i = 0; i < TILED_SIZE; i++)
		{
			for (int j = 0; j < TILED_SIZE; j++)
			{
				float heightValue = heightMap->getValue(i, j);
				float roughValue = roughnessMap->getValue(i, j);
				float tempValue = temperatureMap->getValue(i, j);
				float moistValue = moistureMap->getValue(i, j);

				// Define World Tile
				if (heightValue < waterLevel + 0.1f * (((params->sealevel - 0.6f) / 0.2f) - 2))			// Flooded
				{
					if (heightValue < shoreLevel + 0.1f * (((params->sealevel - 0.6f) / 0.2f) - 2))
						worldTiles[i][j] = deepOcean;
					else
						worldTiles[i][j] = shallowOcean;
				}
				else if (roughValue > peakLevel)	// Mountains
					worldTiles[i][j] = mountains;
				else if (roughValue > rockyLevel)		// Rocky
					worldTiles[i][j] = rocky;
				else							// Smooth
				{
					if (tempValue > 0.7f)
					{
						if (moistValue > 0.6f)
							worldTiles[i][j] = rainforest;
						else if (moistValue < 0.2f)
							worldTiles[i][j] = desert;
						else
						{
							if ((i + j) % 2 == 0)
								worldTiles[i][j] = grassland;
							else
								worldTiles[i][j] = scrubland;
						}
					}
					else if (tempValue < 0.2f)
					{
						if (moistValue > 0.5f)
							worldTiles[i][j] = taiga;
						else if (moistValue < 0.2f)
							worldTiles[i][j] = desert;
						else
						{
							worldTiles[i][j] = tundra;
						}
					}
					else
					{
						if (moistValue > 0.5f)
							worldTiles[i][j] = forest;
						else if (moistValue < 0.2f)
							worldTiles[i][j] = desert;
						else
						{
							if ((i + j) % 2 == 0)
								worldTiles[i][j] = grassland;
							else
								worldTiles[i][j] = scrubland;
						}
					}
				}
			}
		}
	}

	// Pathing
	// Setup Collision Map and Pathing Points
	TCODMap pathCollisionMap = TCODMap(TILED_SIZE, TILED_SIZE);
	TCODMap riverCollisionMap = TCODMap(TILED_SIZE, TILED_SIZE);
	TCODList<TilePosition> riverPoints;
	int riverId = 0;
	TCODList<TilePosition> hubPoints;
	int hubId = 0;
	TCODList<TilePosition> connectedNodes;
	bool pathMask[TILED_SIZE][TILED_SIZE];
	bool riverMask[TILED_SIZE][TILED_SIZE];
	{
		for (int i = 0; i < TILED_SIZE; i++)
		{
			for (int j = 0; j < TILED_SIZE; j++)
			{
				pathMask[i][j] = false;
				riverMask[i][j] = false;
				float heightValue = heightMap->getValue(i, j);
				float roughValue = roughnessMap->getValue(i, j);
				float hubValue = hubMap->getValue(i, j);
				float riverValue = riverMap->getValue(i, j);
				pathCollisionMap.setProperties(i, j, true, true);
				riverCollisionMap.setProperties(i, j, true, true);
				if (heightValue < waterLevel)
				{
					pathCollisionMap.setProperties(i, j, true, false);
				}
				if (roughValue > rockyLevel)
				{
					pathCollisionMap.setProperties(i, j, true, false);
					riverCollisionMap.setProperties(i, j, true, false);
				}

				if (pathCollisionMap.isWalkable(i, j))
				{
					float scaledLevel;
					if (params->population >= 1.0f)
					{
						scaledLevel = -0.05f * (((params->population - 0.6f) / 0.2f) - 2);
					}
					else
					{
						scaledLevel = -0.01f * (((params->population - 0.6f) / 0.2f) - 2);
					}

					if (hubValue > hubLevel + scaledLevel)
					{
						pathMask[i][j] = true;

						hubPoints.push(TilePosition(i, j, hubId));
						hubId++;
					}
					else if (riverValue > riverLevel - 0.005f && riverValue < riverLevel)
					{
						riverPoints.push(TilePosition(i, j, riverId));
						riverId++;
					}
				}
			}
		}
	}

	// Calculate Paths
	TCODDijkstra pathfinder = TCODDijkstra(&pathCollisionMap, 0.0f);
	if (params->roads)
	{
		for (TilePosition* iterator = hubPoints.begin(); iterator != hubPoints.end(); iterator++)
		{
			TilePosition currentPoint = *iterator;
			TilePosition closestPoint;
			float shortestDistance = 10000.0f;

			pathfinder.compute(currentPoint.x, currentPoint.y);

			// Find Closest Point
			for (TilePosition* subIterator = hubPoints.begin(); subIterator != hubPoints.end(); subIterator++)
			{
				TilePosition currentSubPoint = *subIterator;
				float currentDistance;

				if (currentSubPoint.x != currentPoint.x && currentSubPoint.y != currentPoint.y)
				{
					// Check points aren't already connected:
					bool connected = false;
					for (TilePosition* connectedIterator = connectedNodes.begin(); connectedIterator != connectedNodes.end(); connectedIterator++)
					{
						if (connectedIterator->x == currentPoint.id)
						{
							if (connectedIterator->y == currentSubPoint.id)
							{
								connected = true;
							}
						}
						if (connectedIterator->y == currentPoint.id)
						{
							if (connectedIterator->x == currentSubPoint.id)
							{
								connected = true;
							}
						}
					}
					if (!connected)
					{
						currentDistance = pathfinder.getDistance(currentSubPoint.x, currentSubPoint.y);
						if (currentDistance < shortestDistance && currentDistance > 0.0f)
						{
							shortestDistance = currentDistance;
							closestPoint = currentSubPoint;
						}
					}
				}
			}

			// Walk Path

			if (shortestDistance < 10000.0f)
			{

				pathfinder.setPath(closestPoint.x, closestPoint.y);
				while (!pathfinder.isEmpty())
				{
					int i, j;
					pathfinder.walk(&i, &j);
					pathMask[i][j] = true;
				}

				// Mark Points as Connected
				connectedNodes.push(TilePosition(currentPoint.id, closestPoint.id, 0));
			}
		}
	}

	// Calculate Rivers
	TCODDijkstra riverfinder = TCODDijkstra(&riverCollisionMap, 0.0f);
	if (params->rivers)
	{
		for (TilePosition* iterator = riverPoints.begin(); iterator != riverPoints.end(); iterator++)
		{
			TilePosition currentPoint = *iterator;
			bool north = false;
			bool south = false;
			bool east = false;
			bool west = false;

			int northDist = currentPoint.y;
			int southDist = TILED_SIZE - currentPoint.y;
			int eastDist = TILED_SIZE - currentPoint.x;
			int westDist = currentPoint.x;

			if (westDist < eastDist) // Closer West
			{
				if (northDist < southDist) // Closer North
				{
					if (northDist < westDist)
					{
						north = true;
					}
					else
					{
						west = true;
					}
				}
				else // Closer South
				{
					if (southDist < westDist)
					{
						south = true;
					}
					else
					{
						west = true;
					}
				}
			}
			else // Closer East
			{

				if (northDist < southDist) // Closer North
				{
					if (northDist < eastDist)
					{
						north = true;
					}
					else
					{
						east = true;
					}
				}
				else // Closer South
				{
					if (southDist < eastDist)
					{
						south = true;
					}
					else
					{
						east = true;
					}
				}
			}

			TilePosition closestPoint = TilePosition(0, 0, 0);
			if (north)
				closestPoint = TilePosition(currentPoint.x, 0, 0);
			if (south)
				closestPoint = TilePosition(currentPoint.x, TILED_SIZE - 1, 0);
			if (east)
				closestPoint = TilePosition(TILED_SIZE - 1, currentPoint.y, 0);
			if (west)
				closestPoint = TilePosition(0, currentPoint.y, 0);

			riverfinder.compute(currentPoint.x, currentPoint.y);
			riverfinder.setPath(closestPoint.x, closestPoint.y);
			while (!riverfinder.isEmpty())
			{
				int i, j;
				riverfinder.walk(&i, &j);
				if (worldTiles[i][j].tileName == shallowOcean.tileName || worldTiles[i][j].tileName == deepOcean.tileName)
					break;
				riverMask[i][j] = true;
			}

		}
	}
	// Blit Paths onto map
	{
		for (int i = 0; i < TILED_SIZE; i++)
		{
			for (int j = 0; j < TILED_SIZE; j++)
			{
				if (params->rivers && riverMask[i][j])
				{
					// Check edge neighbors
					worldTiles[i][j] = river;
					bool N = false;
					bool E = false;
					bool S = false;
					bool W = false;

					int num = 0;

					if (i - 1 > 0)
					{
						if (riverMask[i - 1][j])
						{
							W = true;
							num++;
						}
					}

					if (i + 1 < TILED_SIZE)
					{
						if (riverMask[i + 1][j])
						{
							E = true;
							num++;
						}
					}

					if (j - 1 > 0)
					{
						if (riverMask[i][j - 1])
						{
							N = true;
							num++;
						}
					}

					if (j + 1 < TILED_SIZE)
					{
						if (riverMask[i][j + 1])
						{
							S = true;
							num++;
						}
					}

					if (num == 1)
					{
						if (N || S)
							worldTiles[i][j].character = ord("│");
						if (E || W)
							worldTiles[i][j].character = ord("─");
					}
					else if (num == 2)
					{
						if (N && S)
							worldTiles[i][j].character = ord("│");
						if (W && E)
							worldTiles[i][j].character = ord("─");
						if (W && S)
							worldTiles[i][j].character = ord("┐");
						if (S && E)
							worldTiles[i][j].character = ord("┌");
						if (E && N)
							worldTiles[i][j].character = ord("└");
						if (N && W)
							worldTiles[i][j].character = ord("┘");
					}
					else if (num == 3)
					{
						if (W && N && E)
							worldTiles[i][j].character = ord("┴");
						if (N && W && S)
							worldTiles[i][j].character = ord("┤");
						if (W && S && E)
							worldTiles[i][j].character = ord("┬");
						if (N && E && S)
							worldTiles[i][j].character = ord("├");
					}
					else if (num == 4)
					{
						worldTiles[i][j].character = ord("┼");
					}
				}
				if (params->roads && pathMask[i][j])
				{
					// Check edge neighbors
					worldTiles[i][j] = path;
					bool N = false;
					bool E = false;
					bool S = false;
					bool W = false;

					int num = 0;

					if (i - 1 > 0)
					{
						if (pathMask[i - 1][j])
						{
							W = true;
							num++;
						}
					}

					if (i + 1 < TILED_SIZE)
					{
						if (pathMask[i + 1][j])
						{
							E = true;
							num++;
						}
					}

					if (j - 1 > 0)
					{
						if (pathMask[i][j - 1])
						{
							N = true;
							num++;
						}
					}

					if (j + 1 < TILED_SIZE)
					{
						if (pathMask[i][j + 1])
						{
							S = true;
							num++;
						}
					}

					if (num == 1)
					{
						if (N || S)
							worldTiles[i][j].character = ord("│");
						if (E || W)
							worldTiles[i][j].character = ord("─");
					}
					else if (num == 2)
					{
						if (N && S)
							worldTiles[i][j].character = ord("│");
						if (W && E)
							worldTiles[i][j].character = ord("─");
						if (W && S)
							worldTiles[i][j].character = ord("┐");
						if (S && E)
							worldTiles[i][j].character = ord("┌");
						if (E && N)
							worldTiles[i][j].character = ord("└");
						if (N && W)
							worldTiles[i][j].character = ord("┘");
					}
					else if (num == 3)
					{
						if (W && N && E)
							worldTiles[i][j].character = ord("┴");
						if (N && W && S)
							worldTiles[i][j].character = ord("┤");
						if (W && S && E)
							worldTiles[i][j].character = ord("┬");
						if (N && E && S)
							worldTiles[i][j].character = ord("├");
					}
					else if (num == 4)
					{
						worldTiles[i][j].character = ord("┼");
					}
				}

			}
		}
	}

	// TODO - Path Rivers

	// TODO - Set Hub Population and Allegiance

	// TODO - Add Features

	// TODO - Generate Lore / Villains / Main Characters

	// Cleanup
	delete islandGradient;
	delete polarGradient;

	delete heightMap;
	delete roughnessMap;
	delete temperatureMap;
	delete moistureMap;

	delete hubMap;
	delete riverMap;

	return new World(worldTiles);
}

Map* MapGenerator::generateMap(WorldTile worldTile)
{
	TCODHeightMap* gradient = nullptr;
	if (path.tileName == worldTile.tileName || river.tileName == worldTile.tileName)
	{
		gradient = generatePolarGradient();
		gradient->scale(-1.0f);
	}
	TCODHeightMap* heightMap = generateNoiseMap(gradient, 0.1f, 3.0f, false, true);
	TCODHeightMap* moistureMap = generateNoiseMap(nullptr, 0.2f, 2.0f, false, false);

	TCODHeightMap* hubMap = generateNoiseMap(nullptr, 0.5f, 1.0f, false, false);


	// Generate Map Tiles
	Tile mapTiles[TILED_SIZE][TILED_SIZE];
	{
		for (int i = 0; i < TILED_SIZE; i++)
		{
			for (int j = 0; j < TILED_SIZE; j++)
			{
				float heightValue;
				if (path.tileName == worldTile.tileName || river.tileName == worldTile.tileName)
				{
					if (worldTile.character == ord("─"))
						heightValue = heightMap->getValue(i, j);
					else
						heightValue = heightMap->getValue(j, i);
				}
				else
				{
					heightValue = heightMap->getValue(i, j);
				}

				float moistValue = moistureMap->getValue(i, j);
				float hubValue = hubMap->getValue(i, j);
				if (deepOcean.tileName == worldTile.tileName)  // DEEP OCEAN
				{
					mapTiles[i][j] = deepWater;
				}
				else if (shallowOcean.tileName == worldTile.tileName)  // SHALLOW OCEAN
				{
					if (heightValue < 0.7f)
					{
						mapTiles[i][j] = shallowWater;
						if (heightValue < 0.6f)
						{
							mapTiles[i][j] = deepWater;
						}
					}
					else if (heightValue < 0.8)
					{
						mapTiles[i][j] = sand;
					}
					else
					{
						mapTiles[i][j] = grass;
						if (moistValue > 0.5f)
						{
							mapTiles[i][j] = tallGrass;

						}
						if (hubValue > hubLevel)
							mapTiles[i][j] = palmTree;
						else if (hubValue > hubLevel - 0.02f)
							mapTiles[i][j] = flower;
					}
				}
				else if (forest.tileName == worldTile.tileName) // FOREST
				{
					if (heightValue > 0.2f)
					{
						mapTiles[i][j] = grass;
						if (moistValue > 0.8f)
							mapTiles[i][j] = tallGrass;
					}
					else
						mapTiles[i][j] = dirt;
					if (hubValue > hubLevel - 0.05)
						mapTiles[i][j] = broadleafTree;
				}
				else if (tundra.tileName == worldTile.tileName) // TUNDRA
				{
					if (heightValue > 0.3f)
						mapTiles[i][j] = snow;
					else
						mapTiles[i][j] = dirt;
					if (hubValue > hubLevel - 0.02)
						mapTiles[i][j] = grass;
				}
				else if (taiga.tileName == worldTile.tileName) // TAIGA
				{
					if (heightValue > 0.2f)
					{
						mapTiles[i][j] = grass;
						if (moistValue > 0.5f)
							mapTiles[i][j] = snow;
					}
					else
						mapTiles[i][j] = dirt;
					if (hubValue > hubLevel - 0.05)
						mapTiles[i][j] = pineTree;
				}
				else if (rainforest.tileName == worldTile.tileName) // RAINFOREST
				{
					if (heightValue < 0.15f)
					{
						mapTiles[i][j] = shallowWater;
						if (heightValue < 0.1f)
						{
							mapTiles[i][j] = deepWater;
						}
					}
					else if (heightValue < 0.2)
					{
						mapTiles[i][j] = dirt;
					}
					else
					{
						if (moistValue > 0.9f)
							mapTiles[i][j] = tallGrass;
						else if (moistValue > 0.2f)
						{
							mapTiles[i][j] = grass;
							if (hubValue > hubLevel - 0.1)
								mapTiles[i][j] = broadleafTree;
							else if (hubValue > hubLevel - 0.3)
								mapTiles[i][j] = palmTree;
						}
						else
						{
							mapTiles[i][j] = dirt;
						}
					}
				}
				else if (desert.tileName == worldTile.tileName) // DESERT
				{
					if (heightValue > 0.15f)
						mapTiles[i][j] = sand;
					else
						mapTiles[i][j] = dirt;
					if (hubValue > hubLevel)
						mapTiles[i][j] = cactus;
				}
				else if (mountains.tileName == worldTile.tileName) // MOUNTAINS
				{
					if (heightValue > 0.75f)
						mapTiles[i][j] = stone;
					else if (heightValue > 0.1f)
					{
						mapTiles[i][j] = rock;
						if (moistValue > 0.4f)
							mapTiles[i][j] = snow;
					}
					else
						mapTiles[i][j] = dirt;
				}
				else if (rocky.tileName == worldTile.tileName) // ROCKY
					if (heightValue > 0.85f)
						mapTiles[i][j] = stone;
					else
					{
						if (heightValue > 0.7f)
							mapTiles[i][j] = grass;
						else if (heightValue > 0.2f)
							mapTiles[i][j] = rock;
						else
							mapTiles[i][j] = dirt;

						if (hubValue > hubLevel)
							mapTiles[i][j] = pineTree;
					}
				else if (path.tileName == worldTile.tileName) // PATH
				{
					if (heightValue < 0.3f)
					{
						mapTiles[i][j] = dirt;
						if (heightValue < 0.2f)
						{
							mapTiles[i][j] = rock;
						}
					}
					else
					{
						mapTiles[i][j] = grass;
						if (moistValue > 0.5f)
						{
							mapTiles[i][j] = tallGrass;

						}
						if (hubValue > hubLevel)
							mapTiles[i][j] = flower;
					}
				}
				else if (river.tileName == worldTile.tileName) // RIVER
				{
					if (heightValue < 0.4f)
					{
						mapTiles[i][j] = shallowWater;
						if (heightValue < 0.3f)
						{
							mapTiles[i][j] = deepWater;
						}
					}
					else if (heightValue < 0.45)
					{
						mapTiles[i][j] = sand;
					}
					else
					{
						mapTiles[i][j] = grass;
						if (moistValue > 0.5f)
						{
							mapTiles[i][j] = tallGrass;

						}
						if (hubValue > hubLevel)
							mapTiles[i][j] = flower;
					}
				}
				else											// GRASSLAND
				{
					if (heightValue > 0.1f)
					{
						mapTiles[i][j] = grass;
						if (moistValue > 0.5f)
							mapTiles[i][j] = tallGrass;
					}
					else
						mapTiles[i][j] = dirt;
					if (hubValue > hubLevel)
						mapTiles[i][j] = flower;
				}
			}
		}
	}

	delete heightMap;
	delete moistureMap;
	if (gradient != nullptr)
		delete gradient;
	delete hubMap;
	return new Map(mapTiles);
}