#include "Vec2.hpp"
#include <cmath>

Vec2::Vec2(float x_in, float y_in) 
    : x(x_in), y(y_in) 
    {}

    bool Vec2::operator == (const Vec2 &v) const
    {
        return (x == v.x && y && v.y);
    }

    bool Vec2::operator != (const Vec2 &v) const
    {
        return (x != v.x || y != v.y);
    }

    Vec2 Vec2::operator + (const Vec2 &v) const
    {
        return Vec2(x + v.x, y + v.y);
    }

    Vec2 Vec2::operator - (const Vec2 &v) const
    {
        return Vec2(x - v.x, y - v.y);
    }

    Vec2 Vec2::operator / (const float &v) const
    {
        return Vec2(x / v, y / v);
    }

    Vec2 Vec2::operator * (const float &v) const
    {
        return Vec2(x * v, y * v);
    }

    void Vec2::operator += (const Vec2 &v)
    {
        x += v.x;
        y += v.y;
    }

    void Vec2::operator -= (const Vec2 &v)
    {
        x -= v.x;
        y -= v.y;
    }

    void Vec2::operator *= (const float &v)
    {
        x *= v;
        y *= v;
    }

    void Vec2::operator /= (const float &v)
    {
        x /= v;
        y /= v;
    }

    float Vec2::dist_power2(const Vec2 &v) const
    {   
        float dx = v.x - x;
        float dy = v.y - y;
        return dx * dx + dy * dy;
    }

    void Vec2::normalize()
    {
        float length = std::sqrt(x * x + y * y);
        if (length != 0.f) {
            x /= length;
            y /= length;
        }
    }
