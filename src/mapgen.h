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
		// --------------------------------------------------------------------------
		//                               WORLD GENERATION
		// --------------------------------------------------------------------------
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

		World* MapGenerator::generateWorld(Params* params, Entity* player)
		{
			static TCODRandom* defaultGenerator = TCODRandom::getInstance();
			// Generate Terrain
			TCODHeightMap* islandGradient = generateGradient(true, true, true, true, true);
			TCODHeightMap* polarGradient = generatePolarGradient();

			TCODHeightMap* heightMap = generateNoiseMap(islandGradient, 0.15f, 4.0f, false, true);
			TCODHeightMap* roughnessMap = generateNoiseMap(nullptr, 0.2f, 0.2f, false, false);
			TCODHeightMap* temperatureMap = generateNoiseMap(polarGradient, 0.07f, 2.0f, false, true);
			TCODHeightMap* moistureMap = generateNoiseMap(temperatureMap, 0.1f, 1.0f, true, false);

			// Generate Features
			TCODHeightMap* hubMap = generateNoiseMap(nullptr, 0.5f, 1.0f, false, true);
			TCODHeightMap* riverMap = generateNoiseMap(islandGradient, 0.5f, 1.0f, false, true);

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
						if (heightValue < waterLevel)			// Flooded
						{
							if (heightValue < shoreLevel)
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
								if (moistValue < 0.5f)
									worldTiles[i][j] = desert;
								else
								{
									if ((i + j) % 2 == 0)
										worldTiles[i][j] = grassland;
									else
										worldTiles[i][j] = scrubland;
								}
							}
							else
							{
								if (moistValue > 0.5f)
									worldTiles[i][j] = forest;
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
							if (hubValue > hubLevel)
							{
								worldTiles[i][j] = hub;
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
							if (worldTiles[i][j].tileName != "Hub")
								pathMask[i][j] = true;
						}

						// Mark Points as Connected
						connectedNodes.push(TilePosition(currentPoint.id, closestPoint.id, 0));
					}
				}
			}

			// Calculate Rivers
			TCODDijkstra riverfinder = TCODDijkstra(&riverCollisionMap, 0.0f);
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
						if (worldTiles[i][j].flooded)
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
						if (riverMask[i][j])
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
						if (pathMask[i][j])
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

			return new World(worldTiles, player);
		}

		// --------------------------------------------------------------------------
		//                               MAP GENERATION
		// --------------------------------------------------------------------------

		Map* MapGenerator::generateMap(Region* region)
		{
			return nullptr;
		}


	};

}