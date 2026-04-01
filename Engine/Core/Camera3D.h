#pragma once
#include "Camera.h"
#include "Types.h"
#include <functional>

class Camera3D : public Camera
{
public:
    Transform3D transform;

    float fov = 45.0f;
    float nearClip = 0.1f;
    float farClip = 1000.0f;

    Vec3 forward;
    Vec3 up = {0, 1, 0};

    void Apply(int width, int height) override;
    void Update(float dt) override;

    void setUpdateBehavior(std::function<void(Camera *, float)> behavior)
    {
        this->updateBehavior = behavior;
    }

private:
    void updateDirectionVectors();
    std::function<void(Camera *, float)> updateBehavior;

};