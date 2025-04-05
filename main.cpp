#include "game.h"
#include <iostream>

int main() {
    try {
        // Create and start the game
        Game game;
        game.initialize();
        game.run();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}