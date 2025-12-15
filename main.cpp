#include <iostream>
#include <vector>
#include "environment.h"

int main() {
    Environment env;

    auto [state, player] = env.reset();

    moveList moves = env.board.getMoves(player);

    std::cout << "Number of moves for player 1: " << moves.size() << std::endl;

}