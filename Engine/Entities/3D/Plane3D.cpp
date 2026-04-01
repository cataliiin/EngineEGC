#include "Plane3D.h"
#include <GL/freeglut.h>
#include "../Core/Types.h"

Plane3D::Plane3D() : Entity3D()
{
    transform.position = Vec3(0.0f, 0.0f, 0.0f);
    transform.rotation = Vec3(0.0f, 0.0f, 0.0f);
    transform.scale = Vec3(1.0f, 1.0f, 1.0f);
}

void Plane3D::Update(float dt)
{
    if (updateBehavior)
    {
        updateBehavior(this, dt);
    }
}

void Plane3D::Draw()
{
    float halfSize = size / 2.0f;

    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);

    glVertex3f(-halfSize, 0.0f, halfSize);
    glVertex3f(halfSize, 0.0f, halfSize);
    glVertex3f(halfSize, 0.0f, -halfSize);
    glVertex3f(-halfSize, 0.0f, -halfSize);
    glEnd();
}