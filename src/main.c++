#include <iostream>
#include "Entity.hpp"
#include "EntityMananger.hpp"
#include "Game.hpp"

int main() {
    Game game("resources/config.txt");
    game.run();

    return 0;
}