#pragma once
#include "../Core/Entity3D.h"
#include <functional>

class Sphere3D : public Entity3D
{
private:
    std::function<void(Sphere3D *, float)> updateBehavior;

public:
    Sphere3D();
    virtual ~Sphere3D() {}

    virtual void Update(float dt) override;
    virtual void Draw() override;

    void setUpdateBehavior(std::function<void(Sphere3D *, float)> behavior)
    {
        updateBehavior = behavior;
    }
};