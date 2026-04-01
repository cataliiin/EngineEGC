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