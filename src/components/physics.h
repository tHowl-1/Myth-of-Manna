#pragma once

#include "../event.h"

using namespace mom;

namespace mom
{
	class Physics
	{
	public:
		int x;
		int y;

		int dx = 1;
		int dy = 0;

		bool solid;

		Physics(int x, int y, bool solid) : x(x), y(y), solid(solid) {}

		void receiveEvent(Event* actionEvent)
		{
			switch (actionEvent->type)
			{
				case PositionEvent:
					actionEvent->x = x;
					actionEvent->y = y;
					actionEvent->dx = dx;
					actionEvent->dy = dy;
					break;
				case CollideEvent:
					if (actionEvent->x == x && actionEvent->y == y)
						actionEvent->check = false;
					break;
				case MovementEvent:
					x = actionEvent->x;
					y = actionEvent->y;
					dx = actionEvent->dx;
					dy = actionEvent->dy;
					break;
				case RenderEvent:
					actionEvent->x = x;
					actionEvent->y = y;
					break;
				default:
					break;
			}
		}

	};
}