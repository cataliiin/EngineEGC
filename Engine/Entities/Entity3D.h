#pragma once
#include <Types.h>
#include "GL/freeglut.h"
#include <functional>
#include "Material.h"

class Entity3D
{
public:
    Transform3D transform;
    Entity3D *parent = nullptr;
    std::vector<Entity3D *> children;

    Material material;
    
    DrawMode3D drawMode;

    std::function<void(Entity3D*, float)> updateBehavior = nullptr;

    Entity3D() : drawMode(DrawMode3D::SOLID) {}
    virtual ~Entity3D() {}

    virtual void Update(float dt);
    void setUpdateBehavior(std::function<void(Entity3D *, float)> behavior);
    void addChild(Entity3D *child);

        void Render();
        virtual void Draw() = 0;
    };