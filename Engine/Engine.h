#pragma once
#include "Core/Window.h"

class Engine
{
public:
    Engine();
    ~Engine();

    void init(int width = 800, int height = 600, const std::string &title = "EngineEGC", bool resizable = true, Color4 bgColor = Color4(0.0f, 0.0f, 0.0f, 1.0f));

    void run();

    Window *getWindow() { return window; }
private:
    Window *window;
    bool running;
};