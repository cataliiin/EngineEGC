#pragma once
#include "Types.h"
#include <functional>

class Engine;

class Entity2D
{
public:
    Transform2D transform;
    Color4 color;
    int zIndex = 0;
    Engine *engine = nullptr;

    using UpdateCallback = std::function<void(Entity2D *, float)>;

    void setUpdate(UpdateCallback callback)
    {
        updateCallback = callback;
    }

    void setZIndex(int z);

    Entity2D() : color(1, 1, 1, 1) {}
    virtual ~Entity2D() {}

    virtual void Update(float dt) = 0;
    virtual void Draw() = 0;

protected:
    UpdateCallback updateCallback = nullptr;
};