#pragma once

// Dependancies
#include "validate.h"
#include "entity.h"
#include "event.h"
#include "scene.h"

namespace mom
{
	// --------------------------------------------------------------------------
	//                               GENERIC ACTIONS
	// --------------------------------------------------------------------------

	// Base action
	class Action
	{
	public:
		virtual Validate perform();

		virtual ~Action() {}
	};

	// Quits the game
	class QuitAction : public Action
	{
	public:
		Validate perform();
	};


	// --------------------------------------------------------------------------
	//                               WORLD ACTIONS
	// --------------------------------------------------------------------------
	// Action performed by a party within a world
	class WorldAction : public Action
	{
	public:
		Party* party;
		World* world;

		WorldAction(Party* performer, World* activeWorld) : party(performer), world(activeWorld) {}
	};

	// Generates a world
	class WorldCreateAction : public Action
	{
	public:
		World** world;
		Params* params;

		WorldCreateAction(World** activeWorld, Params* newParams) : world(activeWorld), params(newParams) {}
		Validate perform();
	};

	// World action performed with a relative direction
	class WorldActionWithDirection : public WorldAction
	{
	public:
		int dx;
		int dy;

		WorldActionWithDirection(Party* performer, World* activeWorld, int dx, int dy) : WorldAction(performer, activeWorld), dx(dx), dy(dy) {}
	};

	// Party movement on world map
	class WorldMovementAction : public WorldActionWithDirection
	{
	public:
		WorldMovementAction(Party* performer, World* activeWorld, int dx, int dy) : WorldActionWithDirection(performer, activeWorld, dx, dy) {}
		Validate perform();
	};

	// Enters a map from world-view
	class EnterMapAction : public WorldAction
	{
	public:
		EnterMapAction(Party* performer, World* activeWorld) : WorldAction(performer, activeWorld) {}
		Validate perform();
	};

	// Exits a map from world-view
	class ExitMapAction : public WorldAction
	{
	public:
		ExitMapAction(Party* performer, World* activeWorld) : WorldAction(performer, activeWorld) {}
		Validate perform();
	};


	// --------------------------------------------------------------------------
	//                               MAP ACTIONS
	// --------------------------------------------------------------------------
	// Action performed by an entity within a map
	class MapAction : public Action
	{
	public:
		Entity* performer;
		Map* map;

		MapAction(Entity* performer, Map* activeMap) : performer(performer), map(activeMap) {}
	};

	// Map action performed with a relative direction
	class MapActionWithDirection : public MapAction
	{
	public:
		int dx;
		int dy;

		MapActionWithDirection(Entity* performer, Map* activeMap, int dx, int dy) : MapAction(performer, activeMap), dx(dx), dy(dy) {}
	};

	class PlaceTileAction : public MapAction
	{
	public:
		PlaceTileAction(Entity* performer, Map* activeMap) : MapAction(performer, activeMap) {}
		Validate perform();
	};

	// Entity movement action in a given direction
	class MapMovementAction : public MapActionWithDirection
	{
	public:
		MapMovementAction(Entity* performer, Map* activeMap, int dx, int dy) : MapActionWithDirection(performer, activeMap, dx, dy) {}
		Validate perform();
	};

	// Entity attack action in a given direction
	class MeleeAction : public MapActionWithDirection
	{
	public:
		MeleeAction(Entity* performer, Map* activeMap, int dx, int dy) : MapActionWithDirection(performer, activeMap, dx, dy) {}
		Validate perform();
	};

	// Entity bump action, either melee or movement depending on collision
	class BumpAction : public MapActionWithDirection
	{
	public:
		BumpAction(Entity* performer, Map* activeMap, int dx, int dy) : MapActionWithDirection(performer, activeMap, dx, dy) {}
		Validate perform();
	};
	
	
}
