#include "Cylinder3D.h"
#include <GL/freeglut.h>
#include "../../Core/Types.h"
#include <cmath>

Cylinder3D::Cylinder3D() : Entity3D()
{
    transform.position = Vec3(0.0f, 0.0f, 0.0f);
    transform.rotation = Vec3(0.0f, 0.0f, 0.0f);
    transform.scale = Vec3(1.0f, 1.0f, 1.0f);
}

void Cylinder3D::Draw()
{
    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

    glTranslatef(0.0f, 0.0f, -height / 2.0f);

    glutSolidCylinder(radius, height, resolution, 1);
    glPopMatrix();
}