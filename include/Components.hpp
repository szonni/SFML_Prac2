#pragma once

#include "Vec2.hpp"
#include <SFML/Graphics.hpp>

class c_Transform {

public:
    Vec2 position = {0.f, 0.f};
    Vec2 velocity = {0.f, 0.f};
    float angle = 0.f;

    c_Transform(Vec2 p, Vec2 v, float a)
        : position(p), velocity(v), angle(a) {}
};

class c_Name {
    std::string name = "non";
};

class c_Shape {

public:
    sf::CircleShape circ;

    c_Shape(float r, int points, const sf::Color &fill, const sf::Color &outline, float thick)
        : circ(r, points)
        {
            circ.setFillColor(fill);
            circ.setOutlineColor(outline);
            circ.setOutlineThickness(thick);
            circ.setOrigin(r, r);
        }
};

class c_Collision {

public:
    float radius = 0.f;

    c_Collision(float r)
        : radius(r) {}
};

class c_Score {

public:
    int score = 0;

    c_Score(int s)
        : score(s) {}
};

class c_LifeSpan {

public:
    int remain = 0;
    int total = 0;

    c_LifeSpan(int total)
        : remain(total), total(total) {}
};

class c_Input {

public:
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;

    c_Input() {}
};