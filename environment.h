#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include <memory>
#include "board.h"
#include "pieces.h"

class Environment {
private:
public:
    Board board;
    pieceList pieces;
    std::tuple<std::vector<std::vector<int>>, int> reset();
    void loadState(pieceList& pieces);
};

#endif