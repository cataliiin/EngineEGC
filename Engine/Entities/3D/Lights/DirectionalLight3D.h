#pragma once
#include "../Light3D.h"

class DirectionalLight3D : public Light3D
{
public:
    Vec3 target = {0.0f, 0.0f, 0.0f};

    void Bind(int index) override
    {
        if (!isOn)
            return;
        GLenum id = GL_LIGHT0 + index;
        glEnable(id);

        Vec3 dir = (transform.position - target).normalize();
        float posVec[] = {dir.x, dir.y, dir.z, 0.0f};
        
        glLightfv(id, GL_POSITION, posVec);
        SendColorsToGPU(id);

        glLightf(id, GL_SPOT_CUTOFF, 180.0f);
    }
};