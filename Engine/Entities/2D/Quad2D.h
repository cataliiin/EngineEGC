#pragma once

#include "../../Engine/Core/Entity2D.h"
#include "GL/freeglut.h"

class Quad2D : public Entity2D
{
public:
    Quad2D();

    Quad2D(Vec2 position, Vec2 scale = Vec2(1.0f, 1.0f), Color4 color = Color4(1.0f, 1.0f, 1.0f, 1.0f));

    virtual ~Quad2D();

    void Update(float deltaTime) override;
    void Draw() override;

private:
    float rotationSpeed;
};