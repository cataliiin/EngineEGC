#pragma once
#include <vector>
#include "Scene.h"

class SceneManager
{
private:
    std::vector<Scene*> sceneStack;

public:
    ~SceneManager();

    void PushScene(Scene* scene);
    void PopScene();
    void ChangeScene(Scene* scene);

    void Update(float dt);
    void Render();

    Scene* getActiveScene() {
        return sceneStack.empty() ? nullptr : sceneStack.back();
    }
};
