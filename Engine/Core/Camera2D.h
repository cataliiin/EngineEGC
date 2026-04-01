#pragma once
#include "Camera.h"
#include "Types.h"

class Camera2D : public Camera
{
public:
    Vec2 position = {0, 0};
    float zoom = 1.0f;

    void Apply(int width, int height) override;

    void Update(float dt);
};

