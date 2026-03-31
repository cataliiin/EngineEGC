#pragma once

#include <string>
#include "Types.h"

class Engine;

class Window
{
public:
    Window(int w = 800, int h = 600, const std::string &t = "EngineEGC", bool resizable = true);
    ~Window();

    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

    void run();

    void setBackgroundColor(Color4 color);
    void setTitle(const std::string &newTitle);
    void setSize(int w, int h);
    void setEngine(Engine *e) { engine = e; }

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    static void display();
    static void reshape(int w, int h);
    static void idle();

private:
    int width;
    int height;
    std::string title;
    int windowId;
    bool resizable;

    Color4 clearColor;

    static Window *instance;

    Engine *engine = nullptr;
    
};