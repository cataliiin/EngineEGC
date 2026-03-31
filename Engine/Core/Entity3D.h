#pragma once
#include "Types.h"

class Entity3D
{
public:
    Transform3D transform;
    Color4 color;

    Entity3D() : color(1, 1, 1, 1) {}
    virtual ~Entity3D() {}

    virtual void Update(float dt) = 0;
    virtual void Draw() = 0;
};