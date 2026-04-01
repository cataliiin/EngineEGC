#pragma once
#include <GL/freeglut.h>

class Camera
{
public:
    virtual ~Camera() {}

    virtual void Apply(int screenWidth, int screenHeight) = 0;

    virtual void Update(float dt) {}
};