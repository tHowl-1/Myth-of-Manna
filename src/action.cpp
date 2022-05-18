#include "action.h"

using namespace crp;

void Action::perform()
{
	return;
}

void MovementAction::perform()
{
	performer->x += dx;
	performer->y += dy;
	return;
}