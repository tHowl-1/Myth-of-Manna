#pragma once

// Forward Declarations
class Entity;

// Dependancies
#include <vector>
#include "tile_types.h"


namespace crp
{
	/*
		Basic container class to store entities and adjacent data
		
		* Subclassing is used here because they will act similarly in management entity storage
	*/
	class Scene
	{
	public:
		std::vector<Entity*> entities;
		Scene(Entity* player)
		{
			entities.push_back(player);
		}
	};

	//Entity and tile container
	class GameMap : public Scene
	{
	public:
		const static int width = 40, height = 25;
		int cameraX = 0, cameraY = 0;
		bool cameraLock = true;

		Tile tiles[width][height] = {};
		GameMap(Entity* player) : Scene(player)
		{
			player->x = width / 2;
			player->y = height / 2;
			cameraX = player->x;
			cameraY = player->y;
			// TODO - Replace with procedural generator
			for (int i = 0; i < width ; i++)
			{
				for (int j = 0; j < height; j++)
				{
					if (i == 0 || j == 0 || i == width - 1 || j == height - 1)
					{
						tiles[i][j] = wall;
					}
					else
					{
						tiles[i][j] = floor;
					}
				}
			}
		}

		// Checks if an x, y coordinate is within the bounds of the map
		bool inBounds(int x, int y)
		{
			return (x >= 0 && x < width&& y >= 0 && y < height);
		}
	};
	
	//Entity and GameMap container
	//class GameWorld

	//Entity container (maybe stored in map / unordered_map instead of vector)
	//class Inventory
	
}