#include "Game.hpp"
#include <iostream>
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

void Game::s_Input()
{
    player->input->up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    player->input->down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    player->input->right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    player->input->left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);

    sf::Vector2i mousePos = sf::Mouse::getPosition();
    Vec2 target(static_cast <int> (mousePos.x), static_cast <int> (mousePos.y));
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        spawnBullet(player, target);
    }
}

void Game::s_Movement()
{
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
}

void Game::s_EnemySpawner(const int &timer)
{
    float ex = std::rand() % win.getSize().x;
    float ey = std::rand() % win.getSize().y;
    if (currentFrame % timer == 0 && currentFrame > 0) {
        lastEnemySpawnTime = currentFrame - lastEnemySpawnTime;
        spawnEnemy(ex, ey, 30, 3.2, 2.5, 0.f, sf::Color::Cyan, sf::Color::Yellow, 3, 4);
    }
}

void Game::s_Collision()
{
    for (auto b : em.getEntities("Bullet")) {
        for (auto e : em.getEntities("Enemy")) {
            float b_Radius = b->collision->radius;
            float e_Radius = e->collision->radius;
            sf::Vector2f bullet_middle =  b->shape->circ.getPosition();
            sf::Vector2f enemy_middle = e->shape->circ.getPosition();
            Vec2 b_pos(static_cast <float> (bullet_middle.x),static_cast <float> (bullet_middle.y));
            Vec2 e_pos(static_cast <float> (enemy_middle.x), static_cast <float> (enemy_middle.y));
            std::cout << "b_pos: " << b_pos.x << " " << b_pos.y << '\n';
            std::cout << "e_pos: " << e_pos.x << " " << e_pos.y << '\n';
            float Dist = e_pos.dist_power2(b_pos);
            float Rad2 = (b_Radius + e_Radius) * (b_Radius + e_Radius);
            std::cout << "Dist: " << Dist << "\n";
            std::cout << "Rad2: " << Rad2 << '\n';
            bool collide = Dist < Rad2;
            switch (collide) {
            case true:
                b->destroy();
                e->destroy();
                break;
            default:
                break;
            }
        }
    }
}

void Game::run()
{
    spawnPlayer();
    
    while (is_running) {
        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                is_running = false;
                win.close();
            }
        }
        s_Input();
        s_EnemySpawner(120);
        s_Collision();
        s_Movement();
        s_Render();
        em.update();
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

void Game::spawnBullet(std::shared_ptr<Entity> e, const Vec2 &target)
{
    auto bullet = em.addEntity("Bullet");

    bullet->transform = std::make_shared <c_Transform> (Vec2(e->transform->position.x, e->transform->position.y), Vec2(0,0), 0);

    bullet->shape = std::make_shared <c_Shape> (10, 8, sf::Color::White, sf::Color::White, 0);

    bullet->collision = std::make_shared <c_Collision> (10);

}

void Game::init(const std::string &path)
{
    win.create(sf::VideoMode(1280, 720), "Real Game");
    win.setFramerateLimit(60);
}
