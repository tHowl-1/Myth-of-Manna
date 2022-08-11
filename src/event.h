#pragma once

#include <string>

namespace mom
{
	enum EventType
	{
		NullEvent,
		PositionEvent,
		CollideEvent,
		MovementEvent,
		RenderEvent,
		DirectionEvent
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

		Event(EventType name) : type(name){}
		Event(EventType name, int x, int y) : type(name), x(x), y(y) {}
		Event(EventType name, int x, int y, int dx, int dy) :type(name), x(x), y(y), dx(dx), dy(dy) {}
	};
}
