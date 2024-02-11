#pragma once

#include "EntityMananger.hpp"
#include <SFML/Graphics.hpp>

struct Player {int S_rad, C_rad, Outline_T, Verts; float S; unsigned int Fill_R, Fill_G, Fill_B, Outline_R, Outline_G, Outline_B;};
struct Enemy {int S_rad, C_rad, Outline_T, VertMin, VertMax, L_Span, Interval; float SpeedMin, SpeedMax; unsigned int Outline_R, Outline_G, Outline_B;};
struct Bullet {int S_rad, C_rad, Outline_T, Verts, L_Span; float S; unsigned int Fill_R, Fill_G, Fill_B, Outline_R, Outline_G, Outline_B;};


class Game {
    sf::RenderWindow win;
    EntityManager em;
    sf::Font font;
    sf::Text text;
    
    Player P_config;
    Enemy E_config;
    Bullet B_config;
    
    int score = 0;
    int currentFrame = 0;
    int lastEnemySpawnTime = 0;
    bool is_paused = false;
    bool is_running = true;

    std::shared_ptr <Entity> player;

    void init(const std::string &path);

public:
    Game(const std::string &config);

    void s_Render();
    void s_Input(sf::Event event);
    void s_Movement();
    void s_EnemySpawner(const int &timer);
    void s_Collision();
    void s_LifeSpanInit();

    void run();
    void spawnPlayer();
    void spawnEnemy();
    void spawnBullet();
};