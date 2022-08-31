#pragma once

#include "palette.h"
#include "cp_437.h"

#include "components/physics.h"
#include "components/render.h"
#include "components/description.h"
#include "components/world.h"
#include "components/open.h"
#include "components/heal.h"
#include "components/inventory.h"

#include "entity.h"

/// <summary>
/// Static entity representations of certain entity types because I have yet to implement json parsing.
/// </summary>

namespace mom
{
	static Entity nullEntity = Entity(
		Object,
		PhysicsC(),
		RenderC(),
		DescriptionC(),
		WorldC(),
		OpenC(),
		HealC(),
		InventoryC(),
		StatsC()
	);

	static Entity Player = Entity(
		Actor,
		PhysicsC(0, 0, true, false),
		RenderC(ord("@"), WHITE),
		DescriptionC("The Player", "A noble adventurer on a grandiose quest!"),
		WorldC(0, 0, false),
		OpenC(),
		HealC(),
		InventoryC(5),
		StatsC(10)
	);

	static Entity Goblin = Entity(
		Actor,
		PhysicsC(0, 0, true, false),
		RenderC(ord("g"), LT_GREEN),
		DescriptionC("Goblin", "A horrible cave creature and gold theif."),
		WorldC(),
		OpenC(),
		HealC(),
		InventoryC(),
		StatsC(5)
	);

	static Entity Door = Entity(
		Object,
		PhysicsC(0, 0, true, false),
		RenderC(ord("+"), BROWN),
		DescriptionC("Door", "A sturdy door."),
		WorldC(),
		OpenC(ord(","), BROWN),
		HealC(),
		InventoryC(),
		StatsC()
	);

	static Entity Potion = Entity(
		Item,
		PhysicsC(0, 0, false, true),
		RenderC(ord("!"), RED),
		DescriptionC("Potion", "A bottle of unasuming red liquid."),
		WorldC(),
		OpenC(),
		HealC(10),
		InventoryC(),
		StatsC()
	);

}