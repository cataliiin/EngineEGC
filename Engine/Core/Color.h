#pragma once

struct Color3
{
    float r, g, b;

    Color3(float r = 0.0f, float g = 0.0f, float b = 0.0f)
        : r(r), g(g), b(b) {}
};

struct Color4 : public Color3
{
    float a;

    Color4(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f)
        : Color3(r, g, b), a(a) {}

    // conversie de la color3
    Color4(Color3 c, float a = 1.0f)
        : Color3(c.r, c.g, c.b), a(a) {}
};