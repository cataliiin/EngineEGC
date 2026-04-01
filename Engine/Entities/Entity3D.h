#pragma once
#include <Types.h>
#include "GL/freeglut.h"

class Entity3D
{
public:
    Transform3D transform;
    Color4 color;
    DrawMode3D drawMode;

    Entity3D() : color(1, 1, 1, 1), drawMode(DrawMode3D::SOLID) {}
    virtual ~Entity3D() {}

    virtual void Update(float dt) = 0;
    
    void Render() {
        glPushMatrix();

        glTranslatef(transform.position.x, transform.position.y, transform.position.z);
        glRotatef(transform.rotation.x, 1, 0, 0);
        glRotatef(transform.rotation.y, 0, 1, 0);
        glRotatef(transform.rotation.z, 0, 0, 1);
        glScalef(transform.scale.x, transform.scale.y, transform.scale.z);

        if (drawMode == DrawMode3D::XRAY) {
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
        } else {
            switch (drawMode) {
                case DrawMode3D::WIREFRAME: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
                case DrawMode3D::POINTS:    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); glPointSize(5.0f); break;
                default:                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
            }
            glColor4f(color.r, color.g, color.b, color.a);
            Draw();
        }

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glPopMatrix();
    }

protected:
    virtual void Draw() = 0;
};