#pragma once

// Forward dependencies
class Entity;

class BaseComponent
{
    public:
    Entity* parent;
    
    BaseComponent(Entity* parent) : parent(parent) {}
    
};
