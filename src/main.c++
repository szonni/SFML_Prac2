#include <iostream>
#include "Game.hpp"

int main() {
    Game game("resources/config.txt");
    game.run();

    return 0;
}