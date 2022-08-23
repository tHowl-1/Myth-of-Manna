#pragma once

#include "../event.h"

using namespace mom;

namespace mom
{
	class HealC
	{
	public:
		bool null = false;

		int amountToHeal;

		HealC() : null(true) {}
		HealC(int amountToHeal) : amountToHeal(amountToHeal) {}

		void receiveEvent(Event* actionEvent)
		{
			switch (actionEvent->type)
			{
			case ConsumeEvent:
				actionEvent->amount = amountToHeal;
				break;
			default:
				break;
			}
		}
	};
}
