#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include <tuple>
#include "pieces.h"

class Piece;

struct State {
    std::vector<std::unique_ptr<Piece>> pieces;
    std::vector<std::vector<int>> board;
};

struct Position {
    int row;
    int col;

    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }
};

struct Move {
    Position from;
    Position to;
};

struct moveList {
    std::vector<Move> moves;
};

struct boardEncoding {
    std::vector<std::vector<int>> encoding; 
};

class Board {
protected:
    boardEncoding board;
    pieceList pieces;
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
    std::vector<std::vector<int>> emptyBoard = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };
public:
    boardEncoding reset();
    moveList getActions(int player);
    bool isLegalMove(Move move, int player);
    std::tuple<int, int> getPiece(const Position& position) const;
    std::tuple<pieceList, boardEncoding> moveTemp(Move move);
    void clearBoard();
    void arrangeBoard(pieceList& pieces);
};

#endif