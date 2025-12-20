#include <vector>
#include <unordered_map>
#include <iostream>
#include <memory>
#include <tuple>
#include "environment.h"
#include "pieces.h"
#include "algebraicNotation.h"

// std::vector<std::vector<std::vector<int>>> board = {
//     {{0,0}, {0,1}, {0,2}, {0,3}, {0,4}, {0,5}, {0,6}, {0,7}},
//     {{1,0}, {1,1}, {1,2}, {1,3}, {1,4}, {1,5}, {1,6}, {1,7}},
//     {{2,0}, {2,1}, {2,2}, {2,3}, {2,4}, {2,5}, {2,6}, {2,7}},
//     {{3,0}, {3,1}, {3,2}, {3,3}, {3,4}, {3,5}, {3,6}, {3,7}},
//     {{4,0}, {4,1}, {4,2}, {4,3}, {4,4}, {4,5}, {4,6}, {4,7}},
//     {{5,0}, {5,1}, {5,2}, {5,3}, {5,4}, {5,5}, {5,6}, {5,7}},
//     {{6,0}, {6,1}, {6,2}, {6,3}, {6,4}, {6,5}, {6,6}, {6,7}},
//     {{7,0}, {7,1}, {7,2}, {7,3}, {7,4}, {7,5}, {7,6}, {7,7}},
// };

std::tuple<bool, int> Environment::reset() {
    
    this->board.reset();
    this->currentPlayer = pieceColour::WHITE;

    return {false, 0}; // terminal, reward
}

std::tuple<bool, int> Environment::step(Move move) {
    bool terminal;
    int reward;
    this->board.move(move, this->currentPlayer);
    bool isCheckMate = this->board.isCheckMate(this->currentPlayer * -1);
    bool isStaleMate = this->board.isStaleMate(this->currentPlayer * -1);
    bool is50MoveRule = this->board.drawBy50MoveRule();
    bool isinsufficientMaterial = this->board.drawByInsufficientMaterial();
    bool inCheck = this->board.inCheck(this->currentPlayer * -1);
    if (isCheckMate) {
        terminal = true;
        reward = (this->currentPlayer == pieceColour::WHITE) ? 1 : -1;
    } else if (isStaleMate) {
        terminal = true;
        reward = 0;
    } else if (is50MoveRule) {
        terminal = true;
        reward = 0;
    } else if (isinsufficientMaterial) {
        terminal = true;
        reward = 0;
    }
    this->gameMoves.push_back(
        move
    );
    this->currentPlayer *= -1;
    std::cout << moveNum << "." << " " << getAlgebraicNotation(move) << " ";
    this->moveNum++;
    return {terminal, reward};
}

moveList Environment::getActions() {
    return this->board.getMoves(this->currentPlayer);
}

void Environment::loadState(pieceList& pieces) {
    this->pieces.pieces.clear();
    this->board.pieces = std::move(pieces);
}

