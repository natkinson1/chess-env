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
    int currentPlayer;
    moveList gameMoves;
    int moveNum = 1;
    std::tuple<bool, int> reset();
    std::tuple<bool, int, std::string> step(Move move);
    moveList getActions();
    void loadState(pieceList& pieces);
};

#endif