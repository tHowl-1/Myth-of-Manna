#pragma once

#include "entity.h"
#include "components/world.h"
#include "components/physics.h"
#include "components/render.h"

namespace mom
{
	static Entity nullEntity = Entity(
		WorldC(),
		PhysicsC(),
		RenderC()
	);

	static Entity Player = Entity(
		WorldC(0, 0, false),
		PhysicsC(0, 0, true),
		RenderC(ord("@"), WHITE)
	);

	static Entity Goblin = Entity(
		WorldC(),
		PhysicsC(0, 0, true),
		RenderC(ord("g"), LT_GREEN)
	);

}