#pragma once
#include "Core/Window.h"
#include <vector>
#include <chrono>
#include "Core/Input.h"
#include "Core/SceneManager.h"

enum class RenderMode
{
    MODE_2D,
    MODE_3D
};

class Engine
{
public:
    static Engine& getInstance() {
        static Engine instance;
        return instance;
    }

    Engine(const Engine&) = delete;
    void operator=(const Engine&) = delete;
    ~Engine();

    void init(int width = 800, int height = 600, const std::string &title = "EngineEGC", bool resizable = true, Color4 bgColor = Color4(0.0f, 0.0f, 0.0f, 1.0f), RenderMode mode = RenderMode::MODE_2D);

    void run();

    Input *getInput() { return input; }

    SceneManager& getSceneManager() { return sceneManager; }

    void update(float deltaTime);
    void render();

    void setTargetFPS(int fps)
    {
        targetFPS = fps;
        msPerFrame = 1000 / targetFPS;
    }



    int getMsPerFrame() const { return msPerFrame; }
    float calculateDeltaTime();

    Window *getWindow() { return window; }
private:
    Engine();

    Window *window;
    bool running;
    RenderMode renderMode;
    int targetFPS = 60;
    int msPerFrame = 16;
    std::chrono::steady_clock::time_point lastFrameTime;
    bool firstFrame = true;
    Input *input;
    SceneManager sceneManager;

};