#include "Window.h"
#include <GL/freeglut.h>
#include <iostream>
#include "../Engine.h"

Window *Window::instance = nullptr;

Window::Window(int w, int h, const std::string &t, bool resizable)
    : width(w), height(h), title(t), windowId(-1), resizable(resizable), clearColor(0.1f, 0.1f, 0.1f, 1.0f)
{

    instance = this;

    int dummy_argc = 1;
    char *dummy_argv[] = {(char *)"executable", NULL};
    glutInit(&dummy_argc, dummy_argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);

    windowId = glutCreateWindow(title.c_str());

    glutDisplayFunc(Window::display);
    glutReshapeFunc(Window::reshape);
    glutIdleFunc(Window::idle);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);

}

Window::~Window()
{
    if (windowId != -1)
    {
        glutDestroyWindow(windowId);
    }
}

void Window::run()
{
    if (windowId != -1)
    {
        glutMainLoop();
    }
}

void Window::setBackgroundColor(Color4 color)
{
    clearColor = color;
}

void Window::setTitle(const std::string &newTitle)
{
    title = newTitle;
    if (windowId != -1)
    {
        glutSetWindow(windowId);
        glutSetWindowTitle(title.c_str());
    }
}

void Window::setSize(int w, int h)
{
    width = w;
    height = h;
    if (windowId != -1)
    {
        glutSetWindow(windowId);
        glutReshapeWindow(w, h);
    }
}


// CALLBACKS

void Window::display()
{
    if (!instance || !instance->engine)
        return;

    glClearColor(
        instance->clearColor.r,
        instance->clearColor.g,
        instance->clearColor.b,
        instance->clearColor.a);

    instance->engine->render();

}

void Window::reshape(int w, int h)
{
    if (!instance)
        return;

    if (!instance->resizable)
    {
        if (w != instance->width || h != instance->height)
        {
            glutReshapeWindow(instance->width, instance->height);
            return;
        }
    }

    instance->width = w;
    instance->height = h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
}

void Window::idle()
{
    if (!instance)
        return;

    glutPostRedisplay();
}