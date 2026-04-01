#include "Sphere3D.h"
#include <GL/freeglut.h>
#include "../Core/Types.h"

Sphere3D::Sphere3D() : Entity3D()
{
    transform.position = Vec3(0.0f, 0.0f, 0.0f);
    transform.rotation = Vec3(0.0f, 0.0f, 0.0f);
    transform.scale = Vec3(1.0f, 1.0f, 1.0f);
}

void Sphere3D::Draw()
{
    float radius = 1.0f;
    int rings = 20;
    int sectors = 20;

    float const R = 1.0f / (float)(rings - 1);
    float const S = 1.0f / (float)(sectors - 1);

    glBegin(GL_TRIANGLE_STRIP);
    for (int r = 0; r < rings; r++)
    {
        for (int s = 0; s < sectors; s++)
        {
            float y = sin(-M_PI_2 + M_PI * r * R);
            float x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
            float z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

            glTexCoord2f(s * S, r * R);

            glNormal3f(x, y, z);

            glVertex3f(x * radius, y * radius, z * radius);

            float y2 = sin(-M_PI_2 + M_PI * (r + 1) * R);
            float x2 = cos(2 * M_PI * s * S) * sin(M_PI * (r + 1) * R);
            float z2 = sin(2 * M_PI * s * S) * sin(M_PI * (r + 1) * R);

            glNormal3f(x2, y2, z2);
            glVertex3f(x2 * radius, y2 * radius, z2 * radius);
        }
    }
    glEnd();
}