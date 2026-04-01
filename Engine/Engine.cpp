#include "Engine.h"
#include "Entities/Entity2D.h"
#include "Entities/Entity3D.h"
#include <GL/freeglut.h>
#include <algorithm>
#include <cstdint>
#include <iostream>

static Engine *engineInstance = nullptr;

Engine::Engine() : window(nullptr), running(false) {}

void timerCallback(int value)
{
    if (engineInstance)
    {
        float dt = engineInstance->calculateDeltaTime();

        engineInstance->update(dt);

        glutPostRedisplay();

        glutTimerFunc(engineInstance->getMsPerFrame(), timerCallback, 0);
    }
}

void onKeyDown(unsigned char key, int x, int y)
{
    if (engineInstance)
        engineInstance->getInput()->setKeyState(key, true);
}

void onKeyUp(unsigned char key, int x, int y)
{
    if (engineInstance)
        engineInstance->getInput()->setKeyState(key, false);
}

void onSpecialKeyDown(int key, int x, int y)
{
    if (engineInstance && engineInstance->getInput())
    {
        engineInstance->getInput()->setSpecialKeyState(key, true);
        engineInstance->getInput()->updateModifiers(glutGetModifiers());
    }
}

void onSpecialKeyUp(int key, int x, int y)
{
    if (engineInstance && engineInstance->getInput())
    {
        engineInstance->getInput()->setSpecialKeyState(key, false);
        engineInstance->getInput()->updateModifiers(glutGetModifiers());
    }
}

void Engine::init(int width, int height, const std::string &title, bool resizable, Color4 bgColor, RenderMode mode)
{
    engineInstance = this;

    window = new Window(width, height, title, resizable);
    window->setBackgroundColor(bgColor);
    window->setEngine(this);
    renderMode = mode;
    input = new Input();
    glutKeyboardFunc(onKeyDown);
    glutKeyboardUpFunc(onKeyUp);
    glutSpecialFunc(onSpecialKeyDown);
    glutSpecialUpFunc(onSpecialKeyUp);
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

/*
void Engine::setupProjection(RenderMode mode)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (mode == RenderMode::MODE_2D)
    {
        gluOrtho2D(0, window->getWidth(), 0, window->getHeight());
        glDisable(GL_DEPTH_TEST);
    }
    else
    {
        gluPerspective(45.0f, (float)window->getWidth() / window->getHeight(), 0.1f, 1000.0f);
        glEnable(GL_DEPTH_TEST);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
*/

void Engine::addEntity2D(Entity2D *e)
{
    if (e)
    {
        entities2D.push_back(e);
        sortEntities2DByZIndex();
        if (e->updateBehavior != nullptr)
        {
            updatableEntities2D.push_back(e);
        }
    }
}

void Engine::addEntity3D(Entity3D *e)
{
    if (e)
    {
        entities3D.push_back(e);
        if (e->updateBehavior != nullptr)
        {
            updatableEntities3D.push_back(e);
        }
    }
}

void Engine::registerUpdateableEntity2D(Entity2D *e)
{
    if (e)
    {
        auto it = std::find(updatableEntities2D.begin(), updatableEntities2D.end(), e);
        if (it == updatableEntities2D.end())
        {
            updatableEntities2D.push_back(e);
        }
    }
}

void Engine::registerUpdateableEntity3D(Entity3D* e)
{
    if (e)
    {
        auto it = std::find(updatableEntities3D.begin(), updatableEntities3D.end(), e);
        if (it == updatableEntities3D.end())
        {
            updatableEntities3D.push_back(e);
        }
    }
}

void Engine::sortEntities2DByZIndex()
{
    std::stable_sort(entities2D.begin(), entities2D.end(), [](Entity2D *a, Entity2D *b)
                     { return a->zIndex < b->zIndex; });
}


void Engine::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (activeCamera)
    {
        activeCamera->Apply(window->getWidth(), window->getHeight());

        for (auto e : entities3D)
            if (e)
                e->Render();
    }

    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, window->getWidth(), 0, window->getHeight());

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    for (auto e : entities2D)
        if (e)
            e->Draw();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);

    glutSwapBuffers();
}

void Engine::update(float deltaTime)
{

    if (activeCamera)
    {
        activeCamera->Update(deltaTime);
    }

    if (renderMode == RenderMode::MODE_3D)
    {
        for (auto e : updatableEntities3D)
        {
            e->Update(deltaTime);
        }
    }

    for (auto e : updatableEntities2D)
    {
        e->Update(deltaTime);
    }

    if (this->input)
    {
        this->input->update();
    }
}

Engine::~Engine()
{
    for (auto e : entities2D)
        delete e;
    for (auto e : entities3D)
        delete e;

    entities2D.clear();
    entities3D.clear();

    if (window != nullptr)
        delete window;

    engineInstance = nullptr;
}