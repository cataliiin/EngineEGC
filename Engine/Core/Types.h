#pragma once

struct Vec2
{
    float x, y;

    Vec2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    Vec2 operator+(const Vec2 &v) const { return Vec2(x + v.x, y + v.y); }
    Vec2 operator-(const Vec2 &v) const { return Vec2(x - v.x, y - v.y); }
    Vec2 operator*(float s) const { return Vec2(x * s, y * s); }
};

struct Vec3
{
    float x, y, z;

    Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3 &v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    Vec3 operator*(float s) const { return Vec3(x * s, y * s, z * s); }
};

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

    Color4(Color3 c, float a = 1.0f)
        : Color3(c.r, c.g, c.b), a(a) {}
};