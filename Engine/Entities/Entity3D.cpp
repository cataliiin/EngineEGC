#include "Entity3D.h"
#include <GL/freeglut.h>
#include "../Core/Types.h"
#include <functional>

void Entity3D::setUpdateBehavior(std::function<void(Entity3D *, float)> behavior)
{
    this->updateBehavior = behavior;
}

void Entity3D::Update(float dt)
{
    if (updateBehavior)
    {
        updateBehavior(this, dt);
    }
}

void Entity3D::addChild(Entity3D *child)
{
    if (!child || child == this)
        return;
    
    if (child->parent)
    {
        auto &pChildren = child->parent->children;
        pChildren.erase(std::remove(pChildren.begin(), pChildren.end(), child), pChildren.end());
    }

    child->parent = this;
    this->children.push_back(child);
}

void Entity3D::Render()
{
    glPushMatrix();

    glTranslatef(transform.position.x, transform.position.y, transform.position.z);
    glRotatef(transform.rotation.x, 1, 0, 0);
    glRotatef(transform.rotation.y, 0, 1, 0);
    glRotatef(transform.rotation.z, 0, 0, 1);
    glScalef(transform.scale.x, transform.scale.y, transform.scale.z);

    if (drawMode == DrawMode3D::XRAY)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glColor4f(color.r, color.g, color.b, 0.3f);
        Draw();

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(2.0f);
        glColor4f(color.r, color.g, color.b, 1.0f);
        Draw();

        glDisable(GL_BLEND);
    }
    else
    {
        switch (drawMode)
        {
        case DrawMode3D::WIREFRAME:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        case DrawMode3D::POINTS:
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            glPointSize(5.0f);
            break;
        default:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
        }
        glColor4f(color.r, color.g, color.b, color.a);
        Draw();
    }

    for (Entity3D *child : children)
    {
        if (child)
            child->Render();
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPopMatrix();
}