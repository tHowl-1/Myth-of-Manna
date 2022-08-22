#pragma once

#include "entity.h"
#include "components/world.h"
#include "components/physics.h"
#include "components/render.h"

namespace mom
{
	static Entity nullEntity = Entity(
		PhysicsC(),
		RenderC(),
		DescriptionC(),
		WorldC(),
		OpenC(),
		HealC(),
		InventoryC()
	);

	static Entity Player = Entity(
		PhysicsC(0, 0, true),
		RenderC(ord("@"), WHITE),
		DescriptionC("The Player", "A noble adventurer on a grandiose quest!"),
		WorldC(0, 0, false),
		OpenC(),
		HealC(),
		InventoryC(5)
	);

	static Entity Goblin = Entity(
		PhysicsC(0, 0, true),
		RenderC(ord("g"), LT_GREEN),
		DescriptionC("Goblin", "A horrible cave creature and gold theif."),
		WorldC(),
		OpenC(),
		HealC(),
		InventoryC()
	);

	static Entity Door = Entity(
		PhysicsC(0, 0, true),
		RenderC(ord("+"), BROWN),
		DescriptionC("Door", "A sturdy door."),
		WorldC(),
		OpenC(ord("\,"), BROWN),
		HealC(),
		InventoryC()
	);

	static Entity Potion = Entity(
		PhysicsC(0, 0, true),
		RenderC(ord("!"), RED),
		DescriptionC("Potion", "A bottle of unasuming red liquid."),
		WorldC(),
		OpenC(),
		HealC(10),
		InventoryC()
	);

}