#pragma once

#include <string>

#include "../event.h"

using namespace mom;
/// <summary>
/// The description component holds information about the entities name/description.
/// </summary>

namespace mom
{
	class DescriptionC
	{
	public:
		bool null = false;

		std::string name;
		std::string description;

		DescriptionC() : null(true) {}
		DescriptionC(std::string name, std::string description) :name(name), description(description) {}

		void receiveEvent(Event* actionEvent)
		{
			switch (actionEvent->type)
			{
			case NameEvent:
				actionEvent->string += name;
				break;
			case DescribeEvent:
				actionEvent->string += description;
				break;
			default:
				break;
			}
		}
	};
}
