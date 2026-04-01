#pragma once
#include "../Entity3D.h"

class Capsule3D : public Entity3D
{

public:
    Capsule3D();
    virtual ~Capsule3D() {}

    float radius = 0.5f;
    float height = 1.0f;
    int resolution = 12;

    virtual void Draw() override;

    void drawHalfSphere(float radius, int res, bool top);
};