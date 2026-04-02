#pragma once
#include <GL/freeglut.h>
#include <functional>

class Camera
{
public:
    virtual ~Camera() {}

    std::function<void(Camera *, float)> updateBehavior;

    virtual bool is3D() const { return false; }

    virtual void Apply(int screenWidth, int screenHeight) = 0;
    virtual void Update(float dt){
        if (updateBehavior)
        {
            updateBehavior(this, dt);
        }
    }

    void setUpdateBehavior(std::function<void(Camera *, float)> behavior)
    {
        this->updateBehavior = behavior;
    }

};