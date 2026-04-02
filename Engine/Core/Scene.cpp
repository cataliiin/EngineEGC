#include "Scene.h"
#include "../Engine.h"
#include "../Entities/Entity2D.h"
#include "../Entities/Entity3D.h"
#include <GL/freeglut.h>

Scene::~Scene() {
    for (auto e : entities2D) delete e;
    for (auto e : entities3D) delete e;
    for (auto c : cameras) delete c;
    if (activeSkybox) delete activeSkybox;
    entities2D.clear();
    entities3D.clear();
    cameras.clear();
}

void Scene::Update(float dt)
{
    if (activeCamera) {
        activeCamera->Update(dt);
    }
    for (auto e : updatableEntities3D) {
        e->Update(dt);
    }
    for (auto e : updatableEntities2D) {
        e->Update(dt);
    }
}

void Scene::Render()
{
    if (!activeCamera)
        return;

    Window *win = Engine::getInstance().getWindow();
    int w = win->getWidth();
    int h = win->getHeight();

    activeCamera->Apply(w, h); 

    if (activeCamera->is3D())
    {
        Camera3D *cam3d = static_cast<Camera3D *>(activeCamera);

        if (activeSkybox)
        {
            activeSkybox->Draw(cam3d->transform.rotation);
        }

        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
        lightManager.UpdateLights(cam3d->transform.position);

        for (auto e : entities3D)
        {
            if (e && e->parent == nullptr)
            {
                e->Render();
            }
        }
    }

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, 0);

    for (auto e : entities2D)
    {
        if (e)
            e->Draw();
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
}

void Scene::addEntity2D(Entity2D *e)
{
    if (e) {
        entities2D.push_back(e);
        sortEntities2DByZIndex();
        if (e->updateBehavior != nullptr) {
            registerUpdateableEntity2D(e);
        }
    }
}

void Scene::addEntity3D(Entity3D *e)
{
    if (e) {
        entities3D.push_back(e);
        if (e->updateBehavior != nullptr) {
            registerUpdateableEntity3D(e);
        }
    }
}

void Scene::registerUpdateableEntity2D(Entity2D *e)
{
    if (e) {
        auto it = std::find(updatableEntities2D.begin(), updatableEntities2D.end(), e);
        if (it == updatableEntities2D.end()) {
            updatableEntities2D.push_back(e);
        }
    }
}

void Scene::registerUpdateableEntity3D(Entity3D* e)
{
    if (e) {
        auto it = std::find(updatableEntities3D.begin(), updatableEntities3D.end(), e);
        if (it == updatableEntities3D.end()) {
            updatableEntities3D.push_back(e);
        }
    }
}

void Scene::sortEntities2DByZIndex()
{
    std::stable_sort(entities2D.begin(), entities2D.end(), [](Entity2D *a, Entity2D *b) { 
        return a->zIndex < b->zIndex; 
    });
}
