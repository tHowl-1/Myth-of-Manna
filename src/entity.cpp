#include "entity.h"

using namespace mom;

void Entity::eventPass(Event* actionEvent)
{
	if (!world.null)
		world.receiveEvent(actionEvent);
	if (!physics.null)
		physics.receiveEvent(actionEvent);
	if (!render.null)
		render.receiveEvent(actionEvent);
}
