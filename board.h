#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include <tuple>
#include "pieces.h"
#include <array>

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
    int pieceIdCounter = 32;
    boardEncoding board;
    pieceList takenPieces;
public:
    pieceList pieces;
    Move lastMove;
    std::array<int, 6> pieceCountWhite = {0};
    std::array<int, 6> pieceCountBlack = {0};
    int move50rule = 0;
    void reset();
    moveList getMoves(int player);
    moveList getAllActions(int player);
    moveList getLegalActions(moveList moves, int player);
    bool isLegalMove(Move& move, int player);
    Piece* getPiece(const Position& position) const;
    void move(Move& move, int player);
    void undoMove(Move& move, int player);
    moveList castlingMoves(int player);
    Piece* getKing(int player);
    void clearBoard();
    void arrangeBoard(pieceList& pieces);
    bool inCheck(int player);
    bool isCheckMate(int player);
    bool isStaleMate(int player);
    bool drawByInsufficientMaterial();
    bool drawBy50MoveRule();
    void takePiece(Piece* piece);
    void undoTakePiece(Piece* piece);
    void incrementPieceCount(int pieceColour, int pieceType);
    void decrementPieceCount(int pieceColour, int pieceType);
};

#endif