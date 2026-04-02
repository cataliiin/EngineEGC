#include "SceneManager.h"

SceneManager::~SceneManager() {
    for (auto scene : sceneStack) {
        scene->Cleanup();
        delete scene;
    }
    sceneStack.clear();
}

void SceneManager::PushScene(Scene* scene) {
    if (!sceneStack.empty()) {
        sceneStack.back()->Pause();
    }
    sceneStack.push_back(scene);
    scene->Init();
}

void SceneManager::PopScene() {
    if (!sceneStack.empty()) {
        Scene* back = sceneStack.back();
        back->Cleanup();
        delete back;
        sceneStack.pop_back();

        if (!sceneStack.empty()) {
            sceneStack.back()->Resume();
        }
    }
}

void SceneManager::ChangeScene(Scene* scene) {
    for (auto s : sceneStack) {
        s->Cleanup();
        delete s;
    }
    sceneStack.clear();
    sceneStack.push_back(scene);
    scene->Init();
}

void SceneManager::Update(float dt) {
    if (!sceneStack.empty()) {
        sceneStack.back()->Update(dt);
    }
}

void SceneManager::Render() {
    for (auto scene : sceneStack) {
        scene->Render();
    }
}
