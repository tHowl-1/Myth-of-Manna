#pragma once

#include <string>
#include "physics.h"
#include "../event.h"

using namespace mom;

namespace mom
{
	class Render
	{
	public:
		int character;
		tcod::ColorRGB color;

		Render(int ch, tcod::ColorRGB col) : character(ch), color(col) {}

		void receiveEvent(Event* actionEvent)
		{
			switch (actionEvent->type)
			{
			case RenderEvent:
				actionEvent->character = character;
				actionEvent->color = color;
				break;
			default:
				break;
			}
		}
	};
}