#pragma once

#include "../event.h"

using namespace mom;

namespace mom
{
	class OpenC
	{
	public:
		bool null = false;
		
		bool open = false;

		int openCharacter;
		tcod::ColorRGB openColor;

		OpenC() : null(true) {}
		OpenC(int openCharacter, tcod::ColorRGB openColor) : open(false), openCharacter(openCharacter), openColor(openColor) {}

		void receiveEvent(Event* actionEvent)
		{
			switch (actionEvent->type)
			{
			case InteractEvent:
				if (open)
					open = false;
				else if (!open)
					open = true;
				break;
			case RenderEvent:
				actionEvent->character = openCharacter;
				actionEvent->color = openColor;
				break;
			case CollideEvent:
				if (open)
					actionEvent->check = true;
				break;
			default:
				break;
			}
		}
	};
}
