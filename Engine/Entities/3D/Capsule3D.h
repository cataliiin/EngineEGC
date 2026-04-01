#pragma once
#include "../Core/Entity3D.h"
#include <functional>

class Capsule3D : public Entity3D
{
private:
    std::function<void(Capsule3D *, float)> updateBehavior;

public:
    Capsule3D();
    virtual ~Capsule3D() {}

    float radius = 0.5f;
    float height = 1.0f;
    int resolution = 12;

    virtual void Update(float dt) override;
    virtual void Draw() override;

    void drawHalfSphere(float radius, int res, bool top);

    void setUpdateBehavior(std::function<void(Capsule3D *, float)> behavior)
    {
        updateBehavior = behavior;
    }
};