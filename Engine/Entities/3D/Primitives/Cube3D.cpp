#include "Cube3D.h"
#include <GL/freeglut.h>
#include "../Core/Types.h"

Cube3D::Cube3D() : Entity3D() {
    transform.position = Vec3(0.0f, 0.0f, 0.0f);
    transform.rotation = Vec3(0.0f, 0.0f, 0.0f);
    transform.scale = Vec3(1.0f, 1.0f, 1.0f);
}

void Cube3D::Draw()
{
    float s = 0.5f;

    glBegin(GL_QUADS);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-s, -s, s);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(s, -s, s);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(s, s, s);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-s, s, s);

    // Fața DIN SPATE (Z-)
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-s, -s, -s);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-s, s, -s);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(s, s, -s);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(s, -s, -s);

    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-s, s, -s);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-s, s, s);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(s, s, s);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(s, s, -s);

    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-s, -s, -s);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(s, -s, -s);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(s, -s, s);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-s, -s, s);

    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(s, -s, -s);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(s, s, -s);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(s, s, s);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(s, -s, s);

    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-s, -s, -s);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-s, -s, s);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-s, s, s);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-s, s, -s);

    glEnd();
}