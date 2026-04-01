#pragma once
#include <GL/freeglut.h>
#include <string>
#include <iostream>
#include "Types.h"
#include "../include/stb_image.h"

class Material
{
public:
    Color4 ambient;
    Color4 diffuse;
    Color4 specular;
    float shininess;

    unsigned int textureID;
    bool hasTexture;

    Vec2 tiling = {1.0f, 1.0f};

    Material() : ambient(0.2f, 0.2f, 0.2f, 1.0f),
                 diffuse(1.0f, 1.0f, 1.0f, 1.0f),
                 specular(0.5f, 0.5f, 0.5f, 1.0f),
                 shininess(32.0f),
                 textureID(0),
                 hasTexture(false) {}

    void loadTexture(const std::string &path)
    {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

        if (data)
        {
            GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            gluBuild2DMipmaps(GL_TEXTURE_2D, format, width, height, format, GL_UNSIGNED_BYTE, data);
            hasTexture = true;
        }
        else
        {
            std::cerr << "Failed to load texture: " << path << std::endl;
        }
        stbi_image_free(data);
    }

    void Apply()
    {
        glMaterialfv(GL_FRONT, GL_AMBIENT, &ambient.r);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, &diffuse.r);
        glMaterialfv(GL_FRONT, GL_SPECULAR, &specular.r);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);

        glColor4f(diffuse.r, diffuse.g, diffuse.b, diffuse.a);

        if (hasTexture)
        {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textureID);

            glMatrixMode(GL_TEXTURE);
            glLoadIdentity();
            glScalef(tiling.x, tiling.y, 1.0f);
            glMatrixMode(GL_MODELVIEW);
        }
        else
        {
            glDisable(GL_TEXTURE_2D);

            glMatrixMode(GL_TEXTURE);
            glLoadIdentity();
            glMatrixMode(GL_MODELVIEW);
        }
    }
};