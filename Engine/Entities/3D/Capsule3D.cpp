#include "Capsule3D.h"
#include <GL/freeglut.h>
#include "../Core/Types.h"
#include <cmath>

Capsule3D::Capsule3D() : Entity3D()
{
    transform.position = Vec3(0.0f, 0.0f, 0.0f);
    transform.rotation = Vec3(0.0f, 0.0f, 0.0f);
    transform.scale = Vec3(1.0f, 1.0f, 1.0f);
}

void Capsule3D::Update(float dt)
{
    if (updateBehavior)
    {
        updateBehavior(this, dt);
    }
}

void Capsule3D::Draw()
{

    GLUquadric *quad = gluNewQuadric();

    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, -height / 2.0f);
    gluCylinder(quad, radius, radius, height, resolution, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, height / 2.0f, 0.0f);
    drawHalfSphere(radius, resolution, true);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -height / 2.0f, 0.0f);
    drawHalfSphere(radius, resolution, false);
    glPopMatrix();

    gluDeleteQuadric(quad);
}

void Capsule3D::drawHalfSphere(float radius, int res, bool top)
{
    float angleStep = (M_PI / 2.0f) / res;
    float startAngle = top ? 0 : M_PI / 2.0f;

    for (int i = 0; i < res; i++)
    {
        float lat0 = startAngle + i * angleStep;
        float lat1 = startAngle + (i + 1) * angleStep;

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= res * 2; j++)
        {
            float lng = 2.0f * M_PI * (float)j / (res * 2);
            float x = cos(lng);
            float z = sin(lng);

            glVertex3f(x * radius * sin(lat0), radius * cos(lat0), z * radius * sin(lat0));
            glVertex3f(x * radius * sin(lat1), radius * cos(lat1), z * radius * sin(lat1));
        }
        glEnd();
    }
}