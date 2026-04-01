#pragma once
#include "../Core/Entity3D.h"
#include <functional>

class Cube3D : public Entity3D
{
private:
    std::function<void(Cube3D*, float)> updateBehavior;

public:
    Cube3D();
    virtual ~Cube3D() {}

    virtual void Update(float dt) override;
    virtual void Draw() override;

    void setUpdateBehavior(std::function<void(Cube3D*, float)> behavior) {
        updateBehavior = behavior;
    }
};