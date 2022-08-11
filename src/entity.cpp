#include "entity.h"

#include "components/physics.h"
#include "components/render.h"
#include "components/group.h"

using namespace mom;

Entity::~Entity()
{
	delete physics;
	delete render;
}

void Entity::eventPass(Event* actionEvent)
{
	if (physics != nullptr)
		physics->receiveEvent(actionEvent);
	if (render != nullptr)
		render->receiveEvent(actionEvent);
}

Party::~Party()
{
	delete physics;
	//delete group;
	delete render;
}

void Party::eventPass(Event* actionEvent)
{
	if (physics != nullptr)
		physics->receiveEvent(actionEvent);
	//if (group != nullptr)
	//	group->receiveEvent(actionEvent);
	if (render != nullptr)
		render->receiveEvent(actionEvent);
}
