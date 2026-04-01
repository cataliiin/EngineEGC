#pragma once
#include "../Light3D.h"

class PointLight3D : public Light3D
{
public:
    float radius = 10.0f;

    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    void Bind(int index) override
    {
        if (!isOn)
            return;
        GLenum id = GL_LIGHT0 + index;
        glEnable(id);

        float posVec[] = {transform.position.x, transform.position.y, transform.position.z, 1.0f};
        glLightfv(id, GL_POSITION, posVec);

        linear = 4.5f / radius;
        quadratic = 75.0f / (radius * radius);

        glLightf(id, GL_CONSTANT_ATTENUATION, constant);
        glLightf(id, GL_LINEAR_ATTENUATION, linear);
        glLightf(id, GL_QUADRATIC_ATTENUATION, quadratic);

        SendColorsToGPU(id);
        glLightf(id, GL_SPOT_CUTOFF, 180.0f);
    }
};