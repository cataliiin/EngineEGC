#pragma once
#include "../Entity3D.h"
#include <functional>

class Plane3D : public Entity3D
{
private:
    std::function<void(Plane3D *, float)> updateBehavior;

public:
    Plane3D();
    virtual ~Plane3D() {}
    float size = 1.0f;

    virtual void Update(float dt) override;
    virtual void Draw() override;

    void setUpdateBehavior(std::function<void(Plane3D *, float)> behavior)
    {
        updateBehavior = behavior;
    }
};