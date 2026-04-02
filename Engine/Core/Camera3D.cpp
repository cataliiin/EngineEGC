#include "Camera3D.h"
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <cmath>

void Camera3D::Apply(int width, int height)
{
    if (height == 0)
        height = 1;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (float)width / (float)height;
    gluPerspective(fov, aspect, nearClip, farClip);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    updateDirectionVectors();

    Vec3 target = transform.position + forward;

    gluLookAt(transform.position.x, transform.position.y, transform.position.z,
              target.x, target.y, target.z,
              up.x, up.y, up.z);
}

void Camera3D::Update(float dt)
{
    Camera::Update(dt);

    updateDirectionVectors();

    if (updateBehavior)
    {
        updateBehavior(this, dt);
    }
}

void Camera3D::updateDirectionVectors()
{
    float radYaw = transform.rotation.y * 3.14159f / 180.0f;
    float radPitch = transform.rotation.x * 3.14159f / 180.0f;

    forward.x = sin(radYaw) * cos(radPitch);
    forward.y = -sin(radPitch);
    forward.z = -cos(radYaw) * cos(radPitch);
    forward.normalize();

    right.x = cos(radYaw);
    right.y = 0;
    right.z = sin(radYaw);
    right.normalize();

    up = right.cross(forward).normalize();
}