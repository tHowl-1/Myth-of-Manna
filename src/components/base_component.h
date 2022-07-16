#pragma once

// Dependencies
#include "../entity.h"

class BaseComponent
{
public:
    Entity* parent;
    
    BaseComponent(Entity* parent) : parent(parent) {}
    
};
