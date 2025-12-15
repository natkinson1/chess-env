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



// struct moveList {
//     std::vector<Move> moves;

//     void push_back(const Move& move) {
//         moves.push_back(move);
//     }
    
//     // Optional: Add other useful methods
//     size_t size() const { return moves.size(); }
//     bool empty() const { return moves.empty(); }
// };

struct boardEncoding: public std::vector<std::vector<int>> {
    using std::vector<std::vector<int>>::vector;
};

class Board {
protected:
    boardEncoding board;
    pieceList pieces;
    pieceList takenPieces;
    boardEncoding startingBoard = {
        {-4, -3, -2, -5, -6, -2, -3, -4},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {4, 3, 2, 5, 6, 2, 3, 4},
    };
    boardEncoding emptyBoard = {
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
    moveList getMoves(int player);
    moveList getAllActions(int player);
    moveList getLegalActions(moveList moves, int player);
    bool isLegalMove(Move& move, int player);
    Piece* getPiece(const Position& position) const;
    void move(Move& move);
    void undoMove(Move& move);
    moveList castlingMoves(int player);
    Piece* getKing(int player);
    void clearBoard();
    void arrangeBoard(pieceList& pieces);
    bool inCheck(int player);
};

#endif