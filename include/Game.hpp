#pragma once

#include "EntityMananger.hpp"
#include <SFML/Graphics.hpp>

struct Player {
  int S_rad, C_rad, Outline_T, Verts = 0;
  float S = 0;
  unsigned int Fill_R, Fill_G, Fill_B, Outline_R, Outline_G, Outline_B = 0;
};
struct Enemy {
  int S_rad, C_rad, Outline_T, VertMin, VertMax, L_Span, Interval = 0;
  float SpeedMin, SpeedMax = 0;
  unsigned int Outline_R, Outline_G, Outline_B = 0;
};
struct Bullet {
  int S_rad, C_rad, Outline_T, Verts, L_Span = 0;
  float S = 0;
  unsigned int Fill_R, Fill_G, Fill_B, Outline_R, Outline_G, Outline_B = 0;
};

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

  std::shared_ptr<Entity> player;

  void init(const std::string &path);

public:
  Game(const std::string &config);

  void s_Render();
  void s_Input(sf::Event &event);
  void s_Movement();
  void s_EnemySpawner();
  void s_Collision();
  void s_LifeSpanInit();

  void run();
  void spawnPlayer();
  void spawnEnemy();
  void spawnSmallEnemy();
  void spawnBullet();
  void upScore();
};
