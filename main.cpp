#include <iostream>
#include <vector>
#include "environment.h"

int main() {
    Environment env;
    auto [terminal, reward] = env.reset();

    int i = 0;
    while (i < 100 && !terminal) {
        moveList moves = env.getActions();
        Move move = moves[rand() % moves.size()];
        auto [terminal, reward] = env.step(move);
        i++;
    }

    std::cout << "Game finished";

}