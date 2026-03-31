#pragma once
#include "Core/Window.h"
#include "Entity2D.h"
#include "Entity3D.h"
#include <vector>
#include <chrono>

enum class RenderMode
{
    MODE_2D,
    MODE_3D
};

class Engine
{
public:
    Engine();
    ~Engine();

    void init(int width = 800, int height = 600, const std::string &title = "EngineEGC", bool resizable = true, Color4 bgColor = Color4(0.0f, 0.0f, 0.0f, 1.0f), RenderMode mode = RenderMode::MODE_2D);

    void run();

    void addEntity2D(Entity2D* e) { if(e) entities2D.push_back(e); }
    void addEntity3D(Entity3D* e) { if(e) entities3D.push_back(e); }

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
    Window *window;
    bool running;
    RenderMode renderMode;
    int targetFPS = 60;
    int msPerFrame = 16;
    std::chrono::steady_clock::time_point lastFrameTime;
    bool firstFrame = true;

    std::vector<Entity2D *> entities2D;
    std::vector<Entity3D *> entities3D;

    void setupProjection(RenderMode mode);
};