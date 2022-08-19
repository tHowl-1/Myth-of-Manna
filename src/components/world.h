#pragma once

#include <string>

#include "../event.h"

using namespace mom;

namespace mom
{
	class WorldC
	{
	public:
		bool null = false;

		int x;
		int y;

		int dx = 1;
		int dy = 0;

		bool inMap;

		WorldC() : null(true) {}
		WorldC(int x, int y, bool inMap) : x(x), y(y), inMap(inMap) {}

		void receiveEvent(Event* actionEvent)
		{
			switch (actionEvent->type)
			{
			case WorldPositionEvent:
				actionEvent->x = x;
				actionEvent->y = y;
				actionEvent->dx = dx;
				actionEvent->dy = dy;
				break;
			case WorldMovementEvent:
				x = actionEvent->x + actionEvent->dx;
				y = actionEvent->y + actionEvent->dy;
				dx = actionEvent->dx;
				dy = actionEvent->dy;
				break;
			case WorldDirectionEvent:
				dx = actionEvent->dx;
				dy = actionEvent->dy;
				break;
			case WorldCollideEvent:
				if (actionEvent->x + actionEvent->dx == x && actionEvent->y + actionEvent->dy == y)
					actionEvent->check = false;
				break;
			case EnterWorldEvent:
				inMap = true;
				break;
			case ExitWorldEvent:
				inMap = false;
				break;
			case WorldRenderEvent:
				actionEvent->x = x;
				actionEvent->y = y;
				break;
			default:
				break;
			}
		}
	};
}