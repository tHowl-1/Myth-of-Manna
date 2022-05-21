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
		const static int width = 80, height = 45;


		Tile tiles[width][height] = {};
		GameMap(Entity* player) : Scene(player)
		{
			// TODO - Replace with procedural generator
			for (int i = 20; i < width - 20; i++)
			{
				for (int j = 10; j < height - 10; j++)
				{
					if (i == 20 || j == 10 || i == width - 21 || j == height - 11)
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
	};
	
	//Entity and GameMap container
	//class GameWorld

	//Entity container (maybe stored in map / unordered_map instead of vector)
	//class Inventory
	
}