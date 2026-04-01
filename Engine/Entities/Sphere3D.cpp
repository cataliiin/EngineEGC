#include "Sphere3D.h"
#include <GL/freeglut.h>
#include "../Core/Types.h"

Sphere3D::Sphere3D() : Entity3D()
{
    transform.position = Vec3(0.0f, 0.0f, 0.0f);
    transform.rotation = Vec3(0.0f, 0.0f, 0.0f);
    transform.scale = Vec3(1.0f, 1.0f, 1.0f);
}

void Sphere3D::Update(float dt)
{
    if (updateBehavior)
    {
        updateBehavior(this, dt);
    }
}

void Sphere3D::Draw()
{
    glutSolidSphere(1.0f, 20, 20);
}