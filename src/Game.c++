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
        
        
        e->shape->circ.setRotation(e->transform->angle);
        
        win.draw(e->shape->circ);
    }
    win.display();
}

void Game::s_Input(sf::Event event)
{   
    while (win.pollEvent(event)) {

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            win.close();
            is_running = false;
        }
        
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
    if (player->input->up && (player->shape->circ.getPosition().y - player->collision->radius > 0.f)) {
        player->transform->position.y -= player->transform->velocity.y;
    }
    if (player->input->down && (player->shape->circ.getPosition().y + player->collision->radius < static_cast <float> (win.getSize().y))) {
        player->transform->position.y += player->transform->velocity.y;
    }
    if (player->input->left && (player->shape->circ.getPosition().x - player->collision->radius > 0.f)) {
        player->transform->position.x -= player->transform->velocity.x;
    }
    if (player->input->right && (player->shape->circ.getPosition().x + player->collision->radius < static_cast <float> (win.getSize().x))) {
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

    for (auto &e : em.getEntities()) {
        e->transform->angle += 1.f;
    }
}

void Game::s_EnemySpawner(const int &timer)
{
    if (currentFrame % timer == 0 && currentFrame > 0) {
        lastEnemySpawnTime = currentFrame - lastEnemySpawnTime;
        spawnEnemy();
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
        std::srand(std::time(nullptr));
        
        em.update();
        s_Input(event);
        
        if (!is_paused) {
            s_EnemySpawner(E_config.Interval);
            s_Collision();
            //s_Movement();
            currentFrame++;
        }
        s_Render();
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

void Game::spawnEnemy()
{
    auto entity = em.addEntity("Enemy");
    
    entity->collision = std::make_shared <c_Collision> (E_config.C_rad);

    //random vertex number
    int verts = E_config.VertMin + std::rand() % E_config.VertMax;
    
    //random fill color;
    unsigned int RF = std::rand() % 255;
    unsigned int GF = std::rand() % 255;
    unsigned int BF = std::rand() % 255;
    sf::Color color = sf::Color (RF, GF, BF);

    entity->shape = std::make_shared <c_Shape> (E_config.S_rad, verts, sf::Color (color), 
    sf::Color (E_config.Outline_R, E_config.Outline_G, E_config.Outline_B), E_config.Outline_T);
    
    float ex = entity->collision->radius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX) / (static_cast <float> (win.getSize().x) - 2.f * entity->collision->radius));
    float ey = entity->collision->radius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX) / (static_cast <float> (win.getSize().y) - 2.f * entity->collision->radius));
    
    float rando1 = 2 + std::rand() % 3;
    float rando2 = 2 + std::rand() % 3;
    

    entity->transform = std::make_shared <c_Transform> (Vec2(ex, ey), Vec2(rando1, rando2), 0);

    //record the frame that the enemy spawn
    lastEnemySpawnTime = currentFrame;
}

void Game::spawnBullet()
{
    auto bullet = em.addEntity("Bullet");

    bullet->transform = std::make_shared <c_Transform> (Vec2(player->transform->position.x, player->transform->position.y), Vec2(0,0), 0);

    bullet->shape = std::make_shared <c_Shape> (B_config.S_rad, B_config.C_rad, sf::Color (B_config.Fill_R, B_config.Fill_G, B_config.Fill_B),
    sf::Color (B_config.Outline_R, B_config.Outline_G, B_config.Outline_B), B_config.Outline_T);

    bullet->collision = std::make_shared <c_Collision> (B_config.C_rad);

    bullet->life_span = std::make_shared <c_LifeSpan> (B_config.L_Span);

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
    //initialized file reader
    std::ifstream file(path);
    
    //handle file opening
    if(!file.is_open()) {
        std::cerr << "Can't open file." << std::endl;
        return;
    }

    win.create(sf::VideoMode(1280, 720), "Real Game");
    win.setFramerateLimit(60);
    
    std::string type, font_path;
    int font_size, FR, FG, FB;
    
    //read config
    while (file >> type) {
        if (type == "Font") {
            file >> font_path >> font_size >> FR >> FG >> FB;
            if (!font.loadFromFile(font_path)) {
                std::cerr << "Failed to load font." << std::endl;
                return;
            } else {
                text.setFont(font);
                text.setCharacterSize(font_size);
                text.setFillColor(sf::Color (FR, FG, FB));
            }
        }
        if (type == "Player") {
            file >> P_config.S_rad >> P_config.C_rad >> P_config.S >> P_config.Fill_R >> P_config.Fill_G >> P_config.Fill_B >> 
            P_config.Outline_R >> P_config.Outline_G >> P_config.Outline_B >> P_config.Outline_T >> P_config.Verts;
        }
        if (type == "Enemy") {
            file >> E_config.S_rad >> E_config.C_rad >> E_config.SpeedMin >> E_config.SpeedMax >> E_config.Outline_R >> E_config.Outline_G >> 
            E_config.Outline_B >> E_config.Outline_T >> E_config.VertMin >> E_config.VertMax >> E_config.L_Span >> E_config.Interval;
        }
        if (type == "Bullet") {
            file >> B_config.S_rad >> B_config.C_rad >> B_config.S >> B_config.Fill_R >> B_config.Fill_G >> B_config.Fill_B >> 
            B_config.Outline_R >> B_config.Outline_G >> B_config.Outline_B >> B_config.Outline_T >> B_config.Verts >> B_config.L_Span;
        }
    }
}

