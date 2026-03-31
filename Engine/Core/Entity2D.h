#pragma once
#include "Types.h"

class Entity2D
{
public:
    Transform2D transform;
    Color4 color;

    Entity2D() : color(1, 1, 1, 1) {}
    virtual ~Entity2D() {}

    virtual void Update(float dt) = 0;
    virtual void Draw() = 0;
};