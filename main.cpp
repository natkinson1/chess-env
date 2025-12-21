#include <iostream>
#include <vector>
#include "environment.h"
#include <chrono>

int main() {
    srand(time(0));
    Environment env;
    auto [terminal, reward] = env.reset();
    std::string reason;

    int i = 0;
    while (i < 500 && !terminal) {
        auto t1 = std::chrono::high_resolution_clock::now();
        moveList moves = env.getActions();
        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> ms_double = t2 - t1;
        std::cout << ms_double.count();
        Move move = moves[rand() % moves.size()];
        if (move.castleKS || move.castleQS) {
            std::cout << "Castled!" << std::endl;
        }
        auto [term, reward, res] = env.step(move);
        terminal = term;
        reason = res;
        i++;
        break;
    }

    std::cout << "Game finished: " << reason;

}