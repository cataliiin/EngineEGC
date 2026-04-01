#pragma once
#include "Entities/Entity3D.h"
#include <GL/freeglut.h>

class Light3D : public Entity3D
{
public:
    Color4 ambient = {0.1f, 0.1f, 0.1f, 1.0f};
    Color4 diffuse = {1.0f, 1.0f, 1.0f, 1.0f};
    Color4 specular = {1.0f, 1.0f, 1.0f, 1.0f};

    float intensity = 1.0f;
    bool isOn = true;

    virtual void Bind(int index) = 0;
    void Draw() override {}

protected:
    void SendColorsToGPU(GLenum id)
    {
        float d[] = {diffuse.r * intensity, diffuse.g * intensity, diffuse.b * intensity, diffuse.a};
        float a[] = {ambient.r * intensity, ambient.g * intensity, ambient.b * intensity, ambient.a};
        float s[] = {specular.r * intensity, specular.g * intensity, specular.b * intensity, specular.a};

        glLightfv(id, GL_DIFFUSE, d);
        glLightfv(id, GL_AMBIENT, a);
        glLightfv(id, GL_SPECULAR, s);
    }
};