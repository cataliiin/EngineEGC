#include "Skybox.h"
#include "../../include/stb_image.h"
#ifndef GL_TEXTURE_CUBE_MAP
#define GL_TEXTURE_CUBE_MAP 0x8513
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x851A
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_TEXTURE_WRAP_R 0x8072
#endif

Skybox::Skybox() : textureID(0), isLoaded(false) {}

Skybox::~Skybox()
{
    if (isLoaded)
        glDeleteTextures(1, &textureID);
}

void Skybox::Load(const std::vector<std::string> &faces)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(false);

    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format,
                         width, height, 0, format, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cerr << "Skybox error: Could not load " << faces[i] << std::endl;
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    isLoaded = true;
}
void Skybox::Draw(Vec3 cameraRotation)
{
    if (!isLoaded) return;

    glDisable(GL_LIGHTING);
    glDepthMask(GL_FALSE);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    float matrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);

    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    glLoadMatrixf(matrix);

    glEnable(GL_TEXTURE_CUBE_MAP);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    float s = 1.0f;
    glBegin(GL_QUADS);

    glTexCoord3f(-s, -s,  s); glVertex3f(-s, -s,  s);
    glTexCoord3f( s, -s,  s); glVertex3f( s, -s,  s);
    glTexCoord3f( s,  s,  s); glVertex3f( s,  s,  s);
    glTexCoord3f(-s,  s,  s); glVertex3f(-s,  s,  s);

    glTexCoord3f( s, -s, -s); glVertex3f( s, -s, -s);
    glTexCoord3f(-s, -s, -s); glVertex3f(-s, -s, -s);
    glTexCoord3f(-s,  s, -s); glVertex3f(-s,  s, -s);
    glTexCoord3f( s,  s, -s); glVertex3f( s,  s, -s);

    glTexCoord3f( s, -s,  s); glVertex3f( s, -s,  s);
    glTexCoord3f( s, -s, -s); glVertex3f( s, -s, -s);
    glTexCoord3f( s,  s, -s); glVertex3f( s,  s, -s);
    glTexCoord3f( s,  s,  s); glVertex3f( s,  s,  s);

    glTexCoord3f(-s, -s, -s); glVertex3f(-s, -s, -s);
    glTexCoord3f(-s, -s,  s); glVertex3f(-s, -s,  s);
    glTexCoord3f(-s,  s,  s); glVertex3f(-s,  s,  s);
    glTexCoord3f(-s,  s, -s); glVertex3f(-s,  s, -s);

    glTexCoord3f(-s,  s,  s); glVertex3f(-s,  s,  s);
    glTexCoord3f( s,  s,  s); glVertex3f( s,  s,  s);
    glTexCoord3f( s,  s, -s); glVertex3f( s,  s, -s);
    glTexCoord3f(-s,  s, -s); glVertex3f(-s,  s, -s);

    glTexCoord3f(-s, -s, -s); glVertex3f(-s, -s, -s);
    glTexCoord3f( s, -s, -s); glVertex3f( s, -s, -s);
    glTexCoord3f( s, -s,  s); glVertex3f( s, -s,  s);
    glTexCoord3f(-s, -s,  s); glVertex3f(-s, -s,  s);

    glEnd();

    glDisable(GL_TEXTURE_CUBE_MAP);

    glPopMatrix();
    
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    
    glMatrixMode(GL_MODELVIEW);

    glDepthMask(GL_TRUE);
    glEnable(GL_LIGHTING);
}