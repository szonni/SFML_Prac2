#include "Game.hpp"
#include "Components.hpp"
#include "Vec2.hpp"
#include <iostream>
#include <ctime>
#include <memory>
#include <string>
#define _USE_MATH_DEFINES // before cmath (for window)
#include <cmath>
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
    win.draw(text);
    win.display();
}

void Game::s_Input(sf::Event &event)
{   
    static sf::Clock timer;
    static bool canUseSpecial = true;
    const float cooldown = 10.f;

    while (win.pollEvent(event)) {
        //Fullscreen or Windowed
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11) {
            if (win.getSize() == sf::Vector2u(1280, 720)) {
                win.create(sf::VideoMode::getDesktopMode(), "Real Game", sf::Style::Fullscreen);
                win.setFramerateLimit(60);

            } else {
                win.create(sf::VideoMode(1280, 720), "Real Game", sf::Style::Default);
                win.setFramerateLimit(60);
            }
        }
        
        //close game
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            win.close();
            is_running = false;
        }
        
        //pause and unpause
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

        //shoot
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                spawnBullet();
            }
        }
        // Special attack
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Right && canUseSpecial) {
                Special();
                canUseSpecial = false;
                timer.restart();
            }
        }
    }
    if (canUseSpecial == false && timer.getElapsedTime().asSeconds() >= cooldown) {
        canUseSpecial = true;
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

    //Small enemy movement
    for (auto &small_enemy : em.getEntities("SmallEnemy")) {
        small_enemy->transform->position.x += small_enemy->transform->velocity.x;
        small_enemy->transform->position.y += small_enemy->transform->velocity.y;
    }
    
    // Nuke expansion
    for (auto &nuke : em.getEntities("Nuke")) {
        float rad = nuke->shape->circ.getRadius();
        rad += 1.5f;
        nuke->shape->circ.setOrigin(rad, rad);
        nuke->shape->circ.setRadius(rad);
        nuke->collision->radius = rad;
    }
    
    //Entity rotation
    for (auto &e : em.getEntities()) {
        e->transform->angle += 1.f;
    }
}

void Game::s_EnemySpawner()
{
    if (currentFrame % E_config.Interval == 0 && currentFrame > 0) {
        lastEnemySpawnTime = currentFrame - lastEnemySpawnTime;
        spawnEnemy();
    }
}

void Game::s_Collision()
{
    float player_Rad = player->collision->radius;
    sf::Vector2f player_mid = player->shape->circ.getPosition();
    Vec2 player_pos(static_cast <float> (player_mid.x), static_cast <float> (player_mid.y));
    
    // Bullet and Enemy
    for (auto &b : em.getEntities("Bullet")) {
        float b_Radius = b->collision->radius;
        sf::Vector2f bullet_middle =  b->shape->circ.getPosition();
        Vec2 b_pos(static_cast <float> (bullet_middle.x), static_cast <float> (bullet_middle.y));
        for (auto &e : em.getEntities("Enemy")) {
            float e_Radius = e->collision->radius;
            sf::Vector2f enemy_middle = e->shape->circ.getPosition();
            Vec2 e_pos(static_cast <float> (enemy_middle.x), static_cast <float> (enemy_middle.y));

            float Dist = b_pos.dist_power2(e_pos);
            float Rad2 = (b_Radius + e_Radius) * (b_Radius + e_Radius);
            if (Dist < Rad2) {
                score += e->score->points;
                e->destroy();
                b->destroy();
                spawnSmallEnemy();
            }
        }
        
        //Bullet and SmallEnemy
        for (auto &se : em.getEntities("SmallEnemy")) {
            float se_Radius = se->collision->radius;
            sf::Vector2f se_middle = se->shape->circ.getPosition();
            Vec2 se_pos(static_cast <float> (se_middle.x), static_cast <float> (se_middle.y));

            float Dist = b_pos.dist_power2(se_pos);
            float Rad2 = (b_Radius + se_Radius) * (b_Radius + se_Radius);
            if (Dist < Rad2) {
                score += se->score->points;
                se->destroy();
                b->destroy();
            }
        }
    }
    
    // Player and Enemy and border
    for (auto &e : em.getEntities("Enemy")) {
        if (e->shape->circ.getPosition().x - e->collision->radius < 0.f) {
            e->transform->velocity.x *= -1;
        }
        if (e->shape->circ.getPosition().x + e->collision->radius > static_cast <float> (win.getSize().x)) {
            e->transform->velocity.x *= -1;
        }
        if (e->shape->circ.getPosition().y - e->collision->radius < 0.f) {
            e->transform->velocity.y *= -1;
        }
        if (e->shape->circ.getPosition().y + e->collision->radius > static_cast <float> (win.getSize().y)) {
            e->transform->velocity.y *= -1;
        }

        float e_Rad = e->collision->radius;
        sf::Vector2f e_mid = e->shape->circ.getPosition();
        Vec2 e_pos(static_cast <float> (e_mid.x), static_cast <float> (e_mid.y));
        
        float Dists = player_pos.dist_power2(e_pos);
        float Rad2s = (player_Rad + e_Rad) * (player_Rad + e_Rad);
        
        if (Dists < Rad2s) {
            player->transform->position = Vec2(static_cast <float> (win.getSize().x) / 2, static_cast <float> (win.getSize().y) / 2);
            score = 0;
        }
    }
    
    for (auto &n : em.getEntities("Nuke")) {
        float n_rad = n->collision->radius;
        sf::Vector2f n_mid = n->shape->circ.getPosition();
        Vec2 n_pos(static_cast <float> (n_mid.x), static_cast <float> (n_mid.y));

        for (auto &e : em.getEntities("Enemy")) {
            float e_rad = e->collision->radius;
            sf::Vector2f e_mid = e->shape->circ.getPosition();
            Vec2 e_pos(static_cast <float> (e_mid.x), static_cast <float> (e_mid.y));

            float Distn = n_pos.dist_power2(e_pos);
            float Rad2n = (n_rad + e_rad) * (n_rad + e_rad);

            if (Distn < Rad2n) {
                score += e->score->points;
                e->destroy();
                spawnSmallEnemy();
            }
        }
         for (auto &se : em.getEntities("SmallEnemy")) {
            float se_Radius = se->collision->radius;
            sf::Vector2f se_middle = se->shape->circ.getPosition();
            Vec2 se_pos(static_cast <float> (se_middle.x), static_cast <float> (se_middle.y));

            float Dist = n_pos.dist_power2(se_pos);
            float Rad2 = (n_rad + se_Radius) * (n_rad + se_Radius);
            if (Dist < Rad2) {
                score += se->score->points;
                se->destroy();
            }
        }   
    }
}

void Game::s_LifeSpanInit()
{   
    //static declaration will be initialized only once
    static unsigned int fade = 255 / B_config.L_Span;

    //Bullet life span
    for (auto &b : em.getEntities("Bullet")) {
        b->life_span->remain -= 1;
        sf::Color fill = b->shape->circ.getFillColor();
        sf::Color outlineColor = b->shape->circ.getOutlineColor();
        
        fill.a -= fade;
        b->shape->circ.setFillColor(fill);
        outlineColor.a -= fade;
        b->shape->circ.setOutlineColor(outlineColor);

        if (b->life_span->remain == 0) {
            b->destroy();
        }
    }
    //Small enemy life span
    for (auto &se : em.getEntities("SmallEnemy")) {
        se->life_span->remain -= 1;
        if (se->life_span->remain == 0) {
            se->destroy();
        }
    }
    
    // Nuke Life Span
    for (auto &n : em.getEntities("Nuke")) {
        n->life_span->remain -= 1;
        sf::Color outline = n->shape->circ.getOutlineColor();
        outline.a = static_cast<float>(outline.a);
        
        outline.a -= 1.f;
        n->shape->circ.setOutlineColor(outline);
        if (n->life_span->remain == 0) {
            n->destroy();
        }
    }
}


void Game::run()
{
    spawnPlayer();
    while (is_running) {
        sf::Event event;
        std::srand(std::time(nullptr));
        
        s_Input(event);
        em.update();
        upScore();
        if (!is_paused) {
            s_EnemySpawner();
            s_Collision();
            s_Movement();
            s_LifeSpanInit();
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
    entity->transform = std::make_shared <c_Transform> (Vec2(static_cast<float>(win.getSize().x) / 2, static_cast<float>(win.getSize().y) / 2), Vec2(P_config.S, P_config.S), 0.f);
    //create shape for the entity (radius, number of vertices, fill color, outline color, thickness)
    entity->shape = std::make_shared <c_Shape> (P_config.S_rad, P_config.Verts, sf::Color (P_config.Fill_R, P_config.Fill_G, P_config.Fill_B), 
    sf::Color (P_config.Outline_R, P_config.Outline_G, P_config.Outline_B), P_config.Outline_T);
    //create shape collision radius
    entity->collision = std::make_shared <c_Collision> (P_config.C_rad);
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
    
    //make enemy unable to spawn on player
    float ex, ey = 0;
    do {
        ex = entity->collision->radius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX) / (static_cast <float> (win.getSize().x) - 2.f * entity->collision->radius));
        ey = entity->collision->radius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX) / (static_cast <float> (win.getSize().y) - 2.f * entity->collision->radius));
    }
    while
    ((ex + entity->collision->radius > player->transform->position.x - player->collision->radius)
    && (ex - entity->collision->radius < player->transform->position.x + player->collision->radius)
    && (ey + entity->collision->radius > player->transform->position.y - player->collision->radius)
    && (ey - entity->collision->radius < player->transform->position.y + player->collision->radius));
    
    float rando1 = E_config.SpeedMin + static_cast <float> (std::rand()) / (static_cast <float> (RAND_MAX) / E_config.SpeedMax);
    float rando2 = E_config.SpeedMin + static_cast <float> (std::rand()) / (static_cast <float> (RAND_MAX) / E_config.SpeedMax);
        
    entity->transform = std::make_shared <c_Transform> (Vec2(ex, ey), Vec2(rando1, rando2), 0);

    entity->score = std::make_shared <c_Score> (100);

    //record the frame that the enemy spawn
    lastEnemySpawnTime = currentFrame;
}

void Game::spawnSmallEnemy()
{
    for (auto &e : em.getEntities("Enemy")) {
        if (e->isDead()) {
            for (size_t i = 1; i <= e->shape->circ.getPointCount(); i++) {
                auto small_e = em.addEntity("SmallEnemy");
                
                small_e->transform = std::make_shared <c_Transform> (Vec2(e->transform->position.x, e->transform->position.y), Vec2(0, 0), 
                360 / e->shape->circ.getPointCount() * i);

                small_e->shape = std::make_shared <c_Shape> (E_config.S_rad / 2, E_config.C_rad / 2, e->shape->circ.getFillColor(),
                e->shape->circ.getOutlineColor(), E_config.Outline_T);

                small_e->collision = std::make_shared<c_Collision>(E_config.C_rad / 2);

                small_e->life_span = std::make_shared <c_LifeSpan> (E_config.L_Span);

                float toRad = small_e->transform->angle * M_PI / 180;

                small_e->transform->velocity.x = 3 * std::cos(toRad);
                small_e->transform->velocity.y = 3 * std::sin(toRad);

                small_e->score = std::make_shared <c_Score> (200);
            }
        }
    }
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
    Dist *= B_config.S;

    bullet->transform->velocity = Dist;
    
}

void Game::upScore()
{
    text.setFont(font);
    std::string str_score = std::to_string(score);
    text.setString(str_score);
    text.setPosition(0, 0);
}

void Game::Special()
{
    auto nuke = em.addEntity("Nuke");
        
    nuke->transform = std::make_shared <c_Transform> (Vec2(player->transform->position.x, player->transform->position.y), Vec2(0,0), 0);

    nuke->shape = std::make_shared <c_Shape> (B_config.S_rad, 100, sf::Color (0, 0, 0, 0),
    sf::Color (B_config.Outline_R, B_config.Outline_G, B_config.Outline_B), B_config.Outline_T * 4);

    nuke->collision = std::make_shared <c_Collision> (B_config.C_rad);

    nuke->life_span = std::make_shared <c_LifeSpan> (255);
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

    win.create(sf::VideoMode::getDesktopMode(), "Real Game", sf::Style::Fullscreen);
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
