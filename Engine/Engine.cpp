#include "Engine.h"

Engine::Engine() : window(nullptr), running(false) {}

void Engine::init(int width, int height, const std::string &title, bool resizable, Color4 bgColor)
{
    window = new Window(width, height, title, resizable);

    window->setBackgroundColor(bgColor);

    running = true;
}

void Engine::run()
{
    if (window)
    {
        window->run();
    }
}

Engine::~Engine()
{
    if (window != nullptr)
    {
        delete window;
    }
}