#pragma once
#include "../Entity3D.h"

class Cube3D : public Entity3D
{

public:
    Cube3D();
    virtual ~Cube3D() {}

    virtual void Draw() override;
};