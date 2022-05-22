#pragma once

// Dependancies
#include "validate.h"
#include "entity.h"
#include "scene.h"

namespace crp
{
	// Base action
	class Action
	{
	public:
		virtual Validate perform();
	};

	// Action that was performed by an entity in a scene
	class EntityAction : public Action
	{
	public:
		Entity* entity;
		GameMap* map;

		EntityAction(Entity* performer, GameMap* activeScene) : entity(performer), map(activeScene) {}
	};

	// EntityAction with a relative direction (dx, dy)
	class ActionWithDirection : public EntityAction
	{
	public:
		int dx;
		int dy;

		ActionWithDirection(Entity* performer, GameMap* activeScene, int dx, int dy) : EntityAction(performer, activeScene), dx(dx), dy(dy) {}
	};

	// Moves camera by (dx, dy)
	class CameraMovementAction : public ActionWithDirection
	{
	public:
		CameraMovementAction(Entity* performer, GameMap* activeScene, int dx, int dy) : ActionWithDirection(performer, activeScene, dx, dy) {}
		Validate perform();
	};

	// Entity movement action in a given direction
	class MovementAction : public ActionWithDirection
	{
	public:
		MovementAction(Entity* performer, GameMap* activeScene, int dx, int dy) : ActionWithDirection(performer, activeScene, dx, dy) {}
		Validate perform();
	};

	// Toggle Camera lock on and off
	class CameraLockAction : public EntityAction
	{
	public:
		CameraLockAction(Entity* performer, GameMap* activeScene) : EntityAction(performer, activeScene) {}
		Validate perform();
	};

	// Quits the game
	class QuitAction : public Action
	{
	public:
		Validate perform();
	};

}