#include <iostream>
#include <vector>
#include "environment.h"

int main() {
    Environment env;

    env.reset();

    std::vector<std::vector<std::vector<int>>> moves = env.getActions();

    std::cout << "Number of actions: " << moves.size() << std::endl;

}