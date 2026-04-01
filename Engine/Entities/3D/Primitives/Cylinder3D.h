#pragma once
#include "../Entity3D.h"

class Cylinder3D : public Entity3D
{
public:
    Cylinder3D();
    virtual ~Cylinder3D() {}

    float radius = 0.4f;
    float height = 1.0f;
    int resolution = 24;

    virtual void Draw() override;

};