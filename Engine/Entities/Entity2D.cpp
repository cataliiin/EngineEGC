#include "Entity2D.h"
#include "../Engine.h"

void Entity2D::setZIndex(int z)
{
    if (z == zIndex)
        return;
    zIndex = z;
    if (engine)
    {
        engine->sortEntities2DByZIndex();
    }
}

void Entity2D::setUpdateBehavior(std::function<void(Entity2D *, float)> behavior)
{
    this->updateBehavior = behavior;
}

void Entity2D::Update(float dt)
{
    if (updateBehavior)
    {
        updateBehavior(this, dt);
    }
}