#include <iostream>
#include "Game.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);
    Game game("resources/config.txt");
    game.run();

    return 0;
}
