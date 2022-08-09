#pragma once

#include "../action.h"

class Ai
{
public:
	Action* perform()
	{
		return new MovementAction;
	}


}
