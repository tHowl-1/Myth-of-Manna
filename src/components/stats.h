#pragma once

#include "base_component.h"

class Stats : public BaseComponent
{
public:
    int damage = 0;

    int max_hp = 10;
    int defense = 0;
    int strength = 1;

    Stats(Entity* parent) : BaseComponent(parent) {}
    
    
};