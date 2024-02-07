#pragma once

#include "EntityMananger.hpp"
#include <SFML/Graphics.hpp>



class Game {
    sf::RenderWindow win;
    EntityManager em;
    sf::Font font;
    sf::Text text;
    int score = 0;
    int currentFrame = 0;
    int lastEnemySpawnTime = 0;
    bool is_paused = false;
    bool is_running = true;

    std::shared_ptr <Entity> player;

    void init(const std::string &path);

public:
    Game();
    Game(const std::string &config);

    void s_Render();
    void s_Input();
    void s_Movement();
    void s_EnemySpawner(const int &timer);

    void run();
    void spawnPlayer();
    void spawnEnemy(const float &x, const float &y, const float &radius, const float &speedX, const float &speedY, const float &angle, const sf::Color &fill, const sf::Color &outline, const int &verts, const float &thickness);
    void spawnBullet(std::shared_ptr <Entity> e, const Vec2 &target);
};