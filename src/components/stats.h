#pragma once

#include "../event.h"

using namespace mom;

namespace mom
{
	class StatsC
	{
	public:
		bool null = false;

		//int level;
		//int experience;

		//int maxMana;
		//int mana;

		int maxHealth;
		int health;

		StatsC() : null(true) {}
		StatsC(int maxHealth) : maxHealth(maxHealth), health(maxHealth) {}

		void receiveEvent(Event* actionEvent)
		{
			switch (actionEvent->type)
			{
			case HealEvent:
				health += actionEvent->amount;
				if (health > maxHealth)
					health = maxHealth;
				break;
			case DamageEvent:
				health -= actionEvent->amount;
				if (health < 0)
					health = 0;
				break;
			default:
				break;
			}
		}
	};
}

