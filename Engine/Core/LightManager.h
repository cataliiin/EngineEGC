#pragma once
#include <vector>
#include <algorithm>
#include <GL/freeglut.h>
#include "../Entities/Light3D.h"
#include "../Entities/3D/Lights/DirectionalLight3D.h"

class LightManager
{
private:
    std::vector<Light3D *> allLights;
    Color4 globalAmbient = {0.2f, 0.2f, 0.2f, 1.0f};

public:
    void addLight(Light3D *light) { allLights.push_back(light); }

    void removeLight(Light3D *light)
    {
        allLights.erase(std::remove(allLights.begin(), allLights.end(), light), allLights.end());
    }

    void setGlobalAmbient(Color4 color) { globalAmbient = color; }

    void UpdateLights(Vec3 cameraPos)
    {
        glEnable(GL_LIGHTING);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, &globalAmbient.r);

        std::sort(allLights.begin(), allLights.end(), [&](Light3D *a, Light3D *b)
                  {
            bool aDir = (dynamic_cast<DirectionalLight3D*>(a) != nullptr);
            bool bDir = (dynamic_cast<DirectionalLight3D*>(b) != nullptr);
            
            if (aDir != bDir) return aDir; // Directional are prioritate

            float distSqA = (a->transform.position - cameraPos).lengthSquared();
            float distSqB = (b->transform.position - cameraPos).lengthSquared();
            return distSqA < distSqB; });

        for (int i = 0; i < 8; i++)
        {
            if (i < (int)allLights.size() && allLights[i]->isOn)
            {
                allLights[i]->Bind(i);
            }
            else
            {
                glDisable(GL_LIGHT0 + i);
            }
        }
    }
};