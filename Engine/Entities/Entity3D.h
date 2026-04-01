#pragma once
#include <Types.h>
#include "GL/freeglut.h"
#include <functional>
class Entity3D
{
public:
    Transform3D transform;
    Color4 color;
    DrawMode3D drawMode;

    std::function<void(Entity3D*, float)> updateBehavior = nullptr;

    Entity3D() : color(1, 1, 1, 1), drawMode(DrawMode3D::SOLID) {}
    virtual ~Entity3D() {}

    virtual void Update(float dt);
    void setUpdateBehavior(std::function<void(Entity3D *, float)> behavior);

    void Render();
    virtual void Draw() = 0;

};