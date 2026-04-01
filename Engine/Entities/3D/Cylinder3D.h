#pragma once
#include "../Entity3D.h"
#include <functional>

class Cylinder3D : public Entity3D
{
private:
    std::function<void(Cylinder3D *, float)> updateBehavior;

public:
    Cylinder3D();
    virtual ~Cylinder3D() {}

    float radius = 0.4f;
    float height = 1.0f;
    int resolution = 24;

    virtual void Update(float dt) override;
    virtual void Draw() override;

    void setUpdateBehavior(std::function<void(Cylinder3D *, float)> behavior)
    {
        updateBehavior = behavior;
    }
};