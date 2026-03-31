#include "Engine.h"
#include <GL/freeglut.h>

Engine::Engine() : window(nullptr), running(false) {}

static Engine *engineInstance = nullptr;

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

void Engine::init(int width, int height, const std::string &title, bool resizable, Color4 bgColor, RenderMode mode)
{
    engineInstance = this;

    window = new Window(width, height, title, resizable);
    window->setBackgroundColor(bgColor);
    window->setEngine(this);
    renderMode = mode;
    running = true;

    glutTimerFunc(16, timerCallback, 0);
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

    return elapsed.count();
}

void Engine::run()
{
    if (window)
    {
        glutTimerFunc(getMsPerFrame(), timerCallback, 0);
        window->run();
    }
}

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

void Engine::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (this->renderMode == RenderMode::MODE_3D)
    {
        setupProjection(RenderMode::MODE_3D);
        for (auto e : entities3D)
            e->Draw();
    }

    setupProjection(RenderMode::MODE_2D);
    for (auto e : entities2D)
        e->Draw();

    glutSwapBuffers();
}

void Engine::update(float deltaTime) {
    if (renderMode == RenderMode::MODE_3D)
    {
        for (auto e : entities3D)
        {
            if (e)
                e->Update(deltaTime);
        }
    }

    for (auto e : entities2D)
    {
        if (e)
            e->Update(deltaTime);
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
}