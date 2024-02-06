#include "Game.hpp"
#include <iostream>
#include <fstream>

Game::Game() {}

Game::Game(const std::string &config)
{
    init(config);
}

void Game::s_Render()
{
    win.clear();
    for (auto e : em.getEntities()) {
        e->shape->circ.setPosition(e->transform->position.x, e->transform->position.y);
        
        e->transform->angle += 1.f;
        e->shape->circ.setRotation(e->transform->angle);
        
        win.draw(e->shape->circ);
    }
    win.display();
}

void Game::s_EnemySpawner(const int &timer)
{
    float ex = std::rand() % win.getSize().x;
    float ey = std::rand() % win.getSize().y;
    if (currentFrame % timer == 0 && currentFrame > 0) {
        lastEnemySpawnTime = currentFrame - lastEnemySpawnTime;
        std::cout << "Enemy spawns after: " << lastEnemySpawnTime;
        spawnEnemy(ex, ey, 30, 3.2, 2.5, 0.f, sf::Color::Cyan, sf::Color::Yellow, 3, 4);
    }
}

void Game::run()
{
    spawnPlayer();
    
    while (is_running) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            win.close();
            break;
        }
        s_EnemySpawner(120);
        em.update();
        s_Render();
        currentFrame++;
    }

}

void Game::spawnPlayer()
{
    //add entity to wait rooom
    auto entity = em.addEntity("Player");
    
    //create entity respectively at x,y; give them speed; at angle a
    entity->transform = std::make_shared <c_Transform> (Vec2(150.f, 200.f), Vec2(3.f, 4.f), 0.f);
    //create shape for the entity (radius, number of vertices, fill color, outline color, thickness)
    entity->shape = std::make_shared <c_Shape> (20.f, 6, sf::Color::Black, sf::Color::Red, 4.f);
    //create shape collision radius
    entity->collision = std::make_shared <c_Collision> (20.f);
    //input
    entity->input = std::make_shared <c_Input> ();
    
    //create entity
    player = entity;
}

void Game::spawnEnemy(const float &x, const float &y, const float &radius, const float &speedX, const float &speedY, const float &angle, const sf::Color &fill, const sf::Color &outline, const int &verts, const float &thickness)
{
    auto entity = em.addEntity("Enemy");

    entity->transform = std::make_shared <c_Transform> (Vec2(x, y), Vec2(speedX, speedY), angle);

    entity->shape = std::make_shared <c_Shape> (radius, verts, sf::Color (fill), sf::Color (outline), thickness);

    entity->collision = std::make_shared <c_Collision> (radius);

    //record the frame that the enemy spawn
    lastEnemySpawnTime = currentFrame;
    std::cout << " | Enemy spawned on frame: " << lastEnemySpawnTime << '\n';
}

void Game::init(const std::string &path)
{
    win.create(sf::VideoMode(1280, 720), "Real Game");
    win.setFramerateLimit(60);

}
