#pragma once

struct Vec2
{
    float x = 0;
    float y = 0;

    Vec2(float x_in, float y_in);

    bool operator == (const Vec2 &v) const;
    bool operator != (const Vec2 &v) const;

    Vec2 operator + (const Vec2 &v) const;
    Vec2 operator - (const Vec2 &v) const;
    Vec2 operator / (const float &v) const;
    Vec2 operator * (const float &v) const;

    void operator += (const Vec2 &v);
    void operator -= (const Vec2 &v);
    void operator *= (const float &v);
    void operator /= (const float &v);

    float dist_power2(const Vec2 &v) const;
    void normalize();
};
