#include "Engine.h"
#include "Entities/Entity2D.h"
#include "Entities/Entity3D.h"
#include <GL/freeglut.h>
#include <algorithm>
#include <cstdint>
#include <iostream>

Engine::Engine() : window(nullptr), running(false) {}

void timerCallback(int value)
{
    float dt = Engine::getInstance().calculateDeltaTime();
    Engine::getInstance().update(dt);
    glutPostRedisplay();
    glutTimerFunc(Engine::getInstance().getMsPerFrame(), timerCallback, 0);
}

void onKeyDown(unsigned char key, int x, int y)
{
    Engine::getInstance().getInput()->setKeyState(key, true);
}

void onKeyUp(unsigned char key, int x, int y)
{
    Engine::getInstance().getInput()->setKeyState(key, false);
}

void onSpecialKeyDown(int key, int x, int y)
{
    if (Engine::getInstance().getInput())
    {
        Engine::getInstance().getInput()->setSpecialKeyState(key, true);
        Engine::getInstance().getInput()->updateModifiers(glutGetModifiers());
    }
}

void onSpecialKeyUp(int key, int x, int y)
{
    if (Engine::getInstance().getInput())
    {
        Engine::getInstance().getInput()->setSpecialKeyState(key, false);
        Engine::getInstance().getInput()->updateModifiers(glutGetModifiers());
    }
}

void Engine::init(int width, int height, const std::string &title, bool resizable, Color4 bgColor, RenderMode mode)
{

    window = new Window(width, height, title, resizable);
    window->setBackgroundColor(bgColor);
    window->setEngine(this);
    renderMode = mode;
    input = new Input();
    glutKeyboardFunc(onKeyDown);
    glutKeyboardUpFunc(onKeyUp);
    glutSpecialFunc(onSpecialKeyDown);
    glutSpecialUpFunc(onSpecialKeyUp);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_COLOR_MATERIAL);

    running = true;

}

float Engine::calculateDeltaTime()
{
    if (firstFrame)
    {
        lastFrameTime = std::chrono::steady_clock::now();
        firstFrame = false;
        return 0.0f;
    }

    auto currentFrameTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;

    return (elapsed.count() > 0.1f) ? 0.1f : elapsed.count();
}

void Engine::run()
{
    if (window)
    {
        glutTimerFunc(getMsPerFrame(), timerCallback, 0);
        window->run();
    }
}

void Engine::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sceneManager.Render();

    glutSwapBuffers();
}

void Engine::update(float deltaTime)
{
    sceneManager.Update(deltaTime);

    if (this->input)
    {
        this->input->update();
    }
}

Engine::~Engine()
{
    delete input;
    delete window;
}