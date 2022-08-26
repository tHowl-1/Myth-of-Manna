#pragma once

#include "../event.h"

using namespace mom;

/// <summary>
/// The physics component contains the vital information surrounding entity position collision and existance.
/// </summary>

namespace mom
{
	class PhysicsC
	{
	public:
		bool null = false;

		int x;
		int y;

		int dx = 1;
		int dy = 0;

		bool solid;

		bool pocketable;

		bool existant = true;

		PhysicsC() : null(true) {}
		PhysicsC(int x, int y, bool solid, bool pocketable) : x(x), y(y), solid(solid), pocketable(pocketable) {}

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
					if (actionEvent->x + actionEvent->dx == x && actionEvent->y + actionEvent->dy == y && solid)
						actionEvent->check = false;
					break;
				case MovementEvent:
					x = actionEvent->x + actionEvent->dx;
					y = actionEvent->y + actionEvent->dy;
					dx = actionEvent->dx;
					dy = actionEvent->dy;
					break;
				case RenderEvent:
					actionEvent->x = x;
					actionEvent->y = y;
					actionEvent->check = existant;
					break;
				case DirectionEvent:
					dx = actionEvent->dx;
					dy = actionEvent->dy;
					break;
				case HideEvent:
					existant = false;
					break;
				case ShowEvent:
					existant = true;
					break;
				default:
					break;
			}
		}

	};
}