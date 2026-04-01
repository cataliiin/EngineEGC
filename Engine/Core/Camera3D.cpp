#include "Camera3D.h"
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <cmath>

void Camera3D::Apply(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (float)width / (float)height;
    gluPerspective(fov, aspect, nearClip, farClip);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    updateDirectionVectors();

    Vec3 lookAtTarget = transform.position + forward;

    gluLookAt(transform.position.x, transform.position.y, transform.position.z,
              lookAtTarget.x, lookAtTarget.y, lookAtTarget.z,
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
    float yaw = transform.rotation.y;
    float pitch = transform.rotation.x;

    forward.x = cos(yaw) * cos(pitch);
    forward.y = sin(pitch);
    forward.z = sin(yaw) * cos(pitch);
    forward.normalize();
}