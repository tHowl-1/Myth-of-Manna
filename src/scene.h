#pragma once

// Forward Declarations
class Entity;

// Dependancies
#include <vector>


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
	//class GameMap
	
	//Entity and GameMap container
	//class GameWorld

	//Entity container
	//class Inventory
	
}