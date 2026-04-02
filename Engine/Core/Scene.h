#pragma once
#include <vector>
#include <algorithm>
#include "Camera.h"
#include "Camera2D.h"
#include "Camera3D.h"
#include "LightManager.h"
#include "../Entities/3D/Skybox.h"

class Entity2D;
class Entity3D;

class Scene
{
protected:
    std::vector<Entity2D *> entities2D;
    std::vector<Entity2D *> updatableEntities2D;
    std::vector<Entity3D *> entities3D;
    std::vector<Entity3D *> updatableEntities3D;
    std::vector<Camera *> cameras;
    Camera *activeCamera = nullptr;
    LightManager lightManager;
    Skybox *activeSkybox = nullptr;

public:
    virtual ~Scene();

    virtual void Init() = 0;
    virtual void Update(float dt);
    virtual void Render();
    virtual void Cleanup() {}

    virtual void Pause() {}
    virtual void Resume() {}

    void addEntity2D(Entity2D* e);
    void addEntity3D(Entity3D* e);
    void registerUpdateableEntity3D(Entity3D* e);
    void registerUpdateableEntity2D(Entity2D* e);
    void sortEntities2DByZIndex();

    void setSkybox(Skybox *s) { activeSkybox = s; }
    Skybox *getSkybox() { return activeSkybox; }

    void addCamera(Camera *cam, bool setAsActive = false) {
        cameras.push_back(cam);
        if (setAsActive || activeCamera == nullptr) {
            activeCamera = cam;
        }
    }
    void setActiveCamera(int index) {
        if (index >= 0 && index < cameras.size()) {
            activeCamera = cameras[index];
        }
    }
    Camera *getActiveCamera() { return activeCamera; }

    void addLight(Light3D *light) { lightManager.addLight(light); }
    LightManager &getLightManager() { return lightManager; }
};
