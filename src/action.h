#pragma once

// Dependancies
#include "entity.h"

namespace crp
{
	//Base action
	class Action
	{
	public:
		Entity* performer;
		Action(Entity* entity) : performer(entity) {}

		virtual void perform();
	};

	class ActionWithDirection : public Action
	{
	public:
		int dx;
		int dy;

		ActionWithDirection(Entity* entity, int dx, int dy) : Action(entity), dx(dx), dy(dy) {}
	};

	class MovementAction : public ActionWithDirection
	{
	public:
		MovementAction(Entity* entity, int dx, int dy) : ActionWithDirection(entity, dx, dy) {}
		void perform();
	};
}