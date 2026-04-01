#pragma once
#include "../Entity3D.h"

class Sphere3D : public Entity3D
{

public:
    Sphere3D();
    virtual ~Sphere3D() {}

    virtual void Draw() override;

};