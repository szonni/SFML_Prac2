#include "Game.hpp"
#include <iostream>
#include <ctime>
#include <fstream>

Game::Game(const std::string &config)
{
    init(config);
}

void Game::s_Render()
{
    win.clear();
    for (auto &e : em.getEntities()) {
        e->shape->circ.setPosition(e->transform->position.x, e->transform->position.y);
        
        e->transform->angle += 1.f;
        e->shape->circ.setRotation(e->transform->angle);
        
        win.draw(e->shape->circ);
    }
    win.display();
}

void Game::s_Input(sf::Event event)
{   
    while (win.pollEvent(event)) {

        if (is_paused) {
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
                is_paused = false;
            }
        } else {
            player->input->up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
            player->input->down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
            player->input->right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
            player->input->left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
                is_paused = true;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left){
                spawnBullet();
            }
        }
    }
}

void Game::s_Movement()
{   
    //Player Movement
    if (player->input->up) {
        player->transform->position.y -= player->transform->velocity.y;
    }
    if (player->input->down) {
        player->transform->position.y += player->transform->velocity.y;
    }
    if (player->input->left) {
        player->transform->position.x -= player->transform->velocity.x;
    }
    if (player->input->right) {
        player->transform->position.x += player->transform->velocity.x;
    }

    //Bullet Movement
    for (auto &bullet : em.getEntities("Bullet")) {
        bullet->transform->position.x += bullet->transform->velocity.x;
        bullet->transform->position.y += bullet->transform->velocity.y; 
    }

    //Enemy Movement
    for (auto &enemy : em.getEntities("Enemy")) {
        enemy->transform->position.x += enemy->transform->velocity.x;
        enemy->transform->position.y += enemy->transform->velocity.y;
    }
}

void Game::s_EnemySpawner(const int &timer)
{
    std::srand(std::time(nullptr));
    float ex = std::rand() % win.getSize().x;
    float ey = std::rand() % win.getSize().y;
    
    float rando1 = 2 + std::rand() % 3;
    float rando2 = 2 + std::rand() % 3;
    
    if (currentFrame % timer == 0 && currentFrame > 0) {
        lastEnemySpawnTime = currentFrame - lastEnemySpawnTime;
        spawnEnemy(ex, ey, 30, rando1, rando2, 0.f, sf::Color::Cyan, sf::Color::Yellow, 3, 4);
    }
}

void Game::s_Collision()
{
    for (auto &b : em.getEntities("Bullet")) {
        float b_Radius = b->collision->radius;
        for (auto &e : em.getEntities("Enemy")) {
            float e_Radius = e->collision->radius;
            sf::Vector2f bullet_middle =  b->shape->circ.getPosition();
            Vec2 b_pos(static_cast <float> (bullet_middle.x),static_cast <float> (bullet_middle.y));
            sf::Vector2f enemy_middle = e->shape->circ.getPosition();
            Vec2 e_pos(static_cast <float> (enemy_middle.x), static_cast <float> (enemy_middle.y));

            float Dist = b_pos.dist_power2(e_pos);
            float Rad2 = (b_Radius + e_Radius) * (b_Radius + e_Radius);
            if (Dist < Rad2) {
                e->destroy();
                b->destroy();
            }
        }
    }
    
    for (auto &b : em.getEntities("Enemy")) {
        if (b->shape->circ.getPosition().x - b->collision->radius < 0.f) {
            b->transform->velocity.x *= -1;
        }
        if (b->shape->circ.getPosition().x + b->collision->radius > static_cast <float> (win.getSize().x)) {
            b->transform->velocity.x *= -1;
        }
        if (b->shape->circ.getPosition().y - b->collision->radius < 0.f) {
            b->transform->velocity.y *= -1;
        }
        if (b->shape->circ.getPosition().y + b->collision->radius > static_cast <float> (win.getSize().y)) {
            b->transform->velocity.y *= -1;
        }
    }
}

void Game::run()
{
    spawnPlayer();
    while (is_running) {
        sf::Event event;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            win.close();
            break;
        }
        em.update();
        s_Input(event);
        
        if (!is_paused) {
            s_EnemySpawner(60);
            s_Collision();
            s_Movement();
        }
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
    
    //create player
    player = entity;
}

void Game::spawnEnemy(const float &x, const float &y, const float &radius, const float &speedX, const float &speedY, const float &angle, const sf::Color &fill, const sf::Color &outline, const int &verts, const float &thickness)
{
    auto entity = em.addEntity("Enemy");

    entity->transform = std::make_shared <c_Transform>(Vec2(x, y), Vec2(speedX, speedY), angle);

    entity->shape = std::make_shared <c_Shape>(radius, verts, sf::Color (fill), sf::Color (outline), thickness);

    entity->collision = std::make_shared <c_Collision>(radius);

    //record the frame that the enemy spawn
    lastEnemySpawnTime = currentFrame;
}

void Game::spawnBullet()
{
    auto bullet = em.addEntity("Bullet");

    bullet->transform = std::make_shared <c_Transform> (Vec2(player->transform->position.x, player->transform->position.y), Vec2(0,0), 0);

    bullet->shape = std::make_shared <c_Shape> (10, 8, sf::Color::White, sf::Color::White, 0);

    bullet->collision = std::make_shared <c_Collision> (10);

    Vec2 target(static_cast <float> (sf::Mouse::getPosition(win).x), static_cast <float> (sf::Mouse::getPosition(win).y));
    Vec2 player_pos(player->transform->position.x, player->transform->position.y);

    Vec2 Dist = target - player_pos;
    Dist.normalize();

    //bullet speed
    Dist *= 15.f;

    bullet->transform->velocity = Dist;
}

void Game::init(const std::string &path)
{
    win.create(sf::VideoMode(1280, 720), "Real Game");
    win.setFramerateLimit(60);
}
