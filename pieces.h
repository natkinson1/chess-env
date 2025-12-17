#ifndef PIECES_H
#define PIECES_H

#include <vector>
#include <memory>
#include <tuple>
#include <iostream>

class Board;
class Piece;

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
    int newEncoding; // when a pawn promotes
    int pieceTakenId = -1;
    bool castleQS = false;
    bool castleKS = false;
    bool hasMoved; // store if piece has previously moved.
};

struct moveList : public std::vector<Move> {
    using std::vector<Move>::vector;
};

struct pieceList {
    std::vector<std::unique_ptr<Piece>> pieces;
    auto begin() {return pieces.begin();}
    auto end() {return pieces.end();}

    auto begin() const {return pieces.begin();}
    auto end() const {return pieces.end();}
};

class Piece {
protected:
public:
    int id;
    Position position;
    int encoding = -1000;
    int colour;
    bool taken = false;
    bool hasMoved = false;
    virtual moveList getMoves(Board& board) = 0;
    virtual ~Piece() = default;
};

class Pawn : public Piece {
private:
    bool hasMoved;
    int direction;
public:
    Pawn(Position pos, int colour, bool hasMoved, int id):
    direction(colour * -1) {
        this->position = pos;
        this->colour = colour;
        this->hasMoved = hasMoved;
        this->encoding = 1 * colour;
        this->id = id;
    };
    moveList getMoves(Board& board) override;
};

class Rook : public Piece {
private:
    bool hasMoved;
public:
    Rook(Position pos, int colour, bool hasMoved, int id) {
        this->position = pos;
        this->colour = colour;
        this->hasMoved = hasMoved;
        this->encoding = 4 * colour;
        this->id = id;
    };
    moveList getMoves(Board& board) override;
};

class Bishop : public Piece {
private:
public:
    Bishop(Position pos, int colour, int id) {
        this->position = pos;
        this->colour = colour;
        this->encoding = 2 * colour;
        this->id = id;
    };
    moveList getMoves(Board& board) override;
};

class Queen : public Piece {
private:
public:
    Queen(Position pos, int colour, int id) {
        this->position = pos;
        this->colour = colour;
        this->encoding = 5 * colour;
        this->id = id;
    };
    moveList getMoves(Board& board) override;
};

class Knight : public Piece {
private:
public:
    Knight(Position pos, int colour, int id) {
        this->position = pos;
        this->colour = colour;
        this->encoding = 3 * colour;
        this->id = id;
    };
    moveList getMoves(Board& board) override;
};

class King : public Piece {
private:
    bool hasMoved;
public:
    King(Position pos, int colour, bool hasMoved, int id) {
        this->position = pos;
        this->colour = colour;
        this->hasMoved = hasMoved;
        this->encoding = 6 * colour;
        this->id = id;
    };
    moveList getMoves(Board& board) override;

};

#endif