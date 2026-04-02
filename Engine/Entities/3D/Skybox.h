#pragma once
#include <GL/freeglut.h>
#include <vector>
#include <string>
#include <iostream>
#include "../Core/Types.h"

class Skybox
{
private:
    unsigned int textureID;
    bool isLoaded = false;

public:
    Skybox();
    ~Skybox();

    void Load(const std::vector<std::string> &faces);
    void Draw(Vec3 cameraPos);
};