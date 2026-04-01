#include "Camera2D.h"
#include <GL/freeglut.h>

void Camera2D::Apply(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, width, 0, height);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(-position.x, -position.y, 0);
    glScalef(zoom, zoom, 1.0f);

    glDisable(GL_DEPTH_TEST);
}

void Camera2D::Update(float dt)
{
}