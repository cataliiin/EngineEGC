#pragma once
#include "../Entity3D.h"
#include <functional>

class Plane3D : public Entity3D
{
public:
    Plane3D();
    virtual ~Plane3D() {}
    float size = 1.0f;

    virtual void Draw() override;
};