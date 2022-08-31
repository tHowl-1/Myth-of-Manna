#pragma once

#include <string>
#include <libtcod.hpp>

/// <summary>
/// The main event class stores interim information passed between entities and actions.
/// </summary>

namespace mom
{
	enum EventType
	{
		NullEvent,
		PositionEvent,
		CollideEvent,
		MovementEvent,
		RenderEvent,
		DirectionEvent,
		WorldPositionEvent,
		WorldMovementEvent,
		WorldDirectionEvent,
		WorldCollideEvent,
		EnterWorldEvent,
		ExitWorldEvent,
		WorldRenderEvent,
		ConsumeEvent,
		InteractEvent,
		NameEvent,
		DescribeEvent,
		FillEvent,
		HideEvent,
		ShowEvent,
		IndexRetrieveEvent,
		HealEvent,
		DamageEvent
	};

	class Event
	{
	public:
		EventType type;

		//Data
		int character = 0;
		tcod::ColorRGB color = tcod::ColorRGB(0, 0, 0);
		std::string string = "";
		int x = -1, y = -1;
		int dx = 0, dy = 0;
		int amount = -1;
		bool check = true;
		void* thing = nullptr;

		Event(EventType name) : type(name){}
		Event(EventType name, int x, int y) : type(name), x(x), y(y) {}
		Event(EventType name, int x, int y, int dx, int dy) :type(name), x(x), y(y), dx(dx), dy(dy) {}
	};
}
