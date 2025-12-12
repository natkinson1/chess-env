#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include <memory>
#include "board.h"
#include "pieces.h"

class Environment {
private:
    Board board;
    std::vector<std::unique_ptr<Piece>> pieces;
public:
    std::tuple<std::vector<std::vector<int>>, int> reset();
    std::vector<std::vector<std::vector<int>>> getActions(int player);
    void loadState(std::vector<std::unique_ptr<Piece>>& pieces);
};

#endif