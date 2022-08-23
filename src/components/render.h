#pragma once

#include "../event.h"

using namespace mom;

namespace mom
{
	class RenderC
	{
	public:
		bool null = false;

		int character;
		tcod::ColorRGB color;

		RenderC() : null(true) {}
		RenderC(int ch, tcod::ColorRGB col) : character(ch), color(col) {}

		void receiveEvent(Event* actionEvent)
		{	
			switch (actionEvent->type)
			{
			case WorldRenderEvent:
				actionEvent->character = character;
				actionEvent->color = color;
				break;
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