#pragma once
#include "../Light3D.h"

class SpotLight3D : public Light3D
{
public:
    Vec3 target = {0.0f, 0.0f, 0.0f};
    float cutoffAngle = 15.0f;
    float exponent = 10.0f; // 0-128

    void Bind(int index) override
    {
        if (!isOn)
            return;
        GLenum id = GL_LIGHT0 + index;
        glEnable(id);

        float posVec[] = {transform.position.x, transform.position.y, transform.position.z, 1.0f};
        Vec3 dir = (target - transform.position).normalize();

        glLightfv(id, GL_POSITION, posVec);
        glLightfv(id, GL_SPOT_DIRECTION, &dir.x);

        glLightf(id, GL_SPOT_CUTOFF, cutoffAngle);
        glLightf(id, GL_SPOT_EXPONENT, exponent);

        SendColorsToGPU(id);
    }
};