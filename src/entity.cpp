#include "entity.h"

#include "components/physics.h"
#include "components/render.h"

using namespace mom;

void Entity::eventPass(Event* actionEvent)
{
	if (physics != nullptr)
		physics->receiveEvent(actionEvent);
	if (render != nullptr)
		render->receiveEvent(actionEvent);
}

void Party::move(int dx, int dy)
{
	x += dx;
	y += dy;
}

Party::Party()
{
	x = 0;
	y = 0;
	character = 0x00;
	color = tcod::ColorRGB(255, 255, 255);
	solid = true;
	for (int i = 0; i < MAX_MEMBERS; i++)
		partyMembers[i] = nullptr;
}