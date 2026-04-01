#include "Cube3D.h"
#include <GL/freeglut.h>
#include "../Core/Types.h"

Cube3D::Cube3D() : Entity3D() {
    transform.position = Vec3(0.0f, 0.0f, 0.0f);
    transform.rotation = Vec3(0.0f, 0.0f, 0.0f);
    transform.scale = Vec3(1.0f, 1.0f, 1.0f);
}

void Cube3D::Draw() {
    glutSolidCube(1.0); 
}