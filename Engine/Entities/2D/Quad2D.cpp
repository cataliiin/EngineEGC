#include "Quad2D.h"
#include <GL/freeglut.h>

Quad2D::Quad2D() : Entity2D()
{
    transform.position = Vec2(0.0f, 0.0f);
    transform.scale = Vec2(1.0f, 1.0f);
    transform.rotation = 0.0f;
    color = Color4(1.0f, 1.0f, 1.0f, 1.0f);
}

Quad2D::Quad2D(Vec2 position, Vec2 scale, Color4 color) : Entity2D()
{
    transform.position = position;
    transform.scale = scale;
    transform.rotation = 0.0f;
    this->color = color;
}

Quad2D::~Quad2D()
{
}

void Quad2D::Draw()
{
    glPushMatrix();

    glTranslatef(transform.position.x, transform.position.y, 0.0f);

    glRotatef(transform.rotation, 0.0f, 0.0f, 1.0f);

    glScalef(transform.scale.x, transform.scale.y, 1.0f);

    glColor4f(color.r, color.g, color.b, color.a);

    glBegin(GL_QUADS);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
    glEnd();

    glPopMatrix();
}