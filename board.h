#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include <tuple>

class Piece;

class Board {
protected:
    std::vector<std::vector<int>> board;
    std::vector<std::vector<int>> startingBoard = {
        {-4, -3, -2, -5, -6, -2, -3, -4},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {4, 3, 2, 5, 6, 2, 3, 4},
    };
public:
    std::vector<std::unique_ptr<Piece>> reset();
    std::tuple<int, int> getPiece(const std::vector<int>& position) const;
};

#endif