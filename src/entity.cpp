#include "entity.h"

using namespace mom;

void Entity::eventPass(Event* actionEvent)
{
	if (!physics.null)
		physics.receiveEvent(actionEvent);
	if (!render.null)
		render.receiveEvent(actionEvent);
	if (!description.null)
		description.receiveEvent(actionEvent);
	if (!world.null)
		world.receiveEvent(actionEvent);
	if (!open.null)
		open.receiveEvent(actionEvent);
	if (!heal.null)
		heal.receiveEvent(actionEvent);
	if (!inventory.null)
		inventory.receiveEvent(actionEvent);
	if (!stats.null)
		stats.receiveEvent(actionEvent);
}
