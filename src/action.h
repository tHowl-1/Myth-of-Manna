#pragma once

// Dependancies
#include "entity.h"

namespace crp
{
	// Base action
	class Action
	{
	public:
		virtual int perform();
	};

	// Action that was performed by an entity
	class EntityAction : public Action
	{
	public:
		Entity* performer;
		EntityAction(Entity* entity) : performer(entity) {}
	};

	// EntityAction with a relative direction (dx, dy)
	class ActionWithDirection : public EntityAction
	{
	public:
		int dx;
		int dy;

		ActionWithDirection(Entity* entity, int dx, int dy) : EntityAction(entity), dx(dx), dy(dy) {}
	};

	// Entity movement action in a given direction
	class MovementAction : public ActionWithDirection
	{
	public:
		MovementAction(Entity* entity, int dx, int dy) : ActionWithDirection(entity, dx, dy) {}
		int perform();
	};

	// Quits the game
	class QuitAction : public Action
	{
	public:
		int perform();
	};

}