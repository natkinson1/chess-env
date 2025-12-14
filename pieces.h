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
};

struct moveList : public std::vector<Move> {
    using std::vector<Move>::vector;
};

// struct pieceList : public std::vector<std::unique_ptr<Piece>> {
//     using std::vector<std::unique_ptr<Piece>>::vector;
// };

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
    Position position;
    int encoding;
    int colour;
    bool taken = false;
    virtual moveList getMoves(const Board& board) const = 0;
    virtual ~Piece() = default;
};



class Pawn : public Piece {
private:
    bool hasMoved;
    int direction;
public:
    Pawn(Position pos, int colour, bool hasMoved):
    direction(colour * -1) {
        this->position = pos;
        this->colour = colour;
        this->hasMoved = hasMoved;
        this->encoding = 1 * colour;
    };
    moveList getMoves(const Board& board) const override;
};

class Rook : public Piece {
private:
    int encoding = 4;
    bool hasMoved;
public:
    Rook(Position pos, int colour, bool hasMoved) {
        this->position = pos;
        this->colour = colour;
        this->hasMoved = hasMoved;
        this->encoding = 4 * colour;
    };
    moveList getMoves(const Board& board) const override;
};

class Bishop : public Piece {
private:
public:
    Bishop(Position pos, int colour) {
        this->position = pos;
        this->colour = colour;
        this->encoding = 2 * colour;

        std::cout << "Bishop created - encoding: " << this->encoding << std::endl;
    };
    moveList getMoves(const Board& board) const override;
};

class Queen : public Piece {
private:
public:
    Queen(Position pos, int colour) {
        this->position = pos;
        this->colour = colour;
        this->encoding = 5 * colour;
    };
    moveList getMoves(const Board& board) const override;
};

class Knight : public Piece {
private:
public:
    Knight(Position pos, int colour) {
        this->position = pos;
        this->colour = colour;
        this->encoding = 3 * colour;
    };
    moveList getMoves(const Board& board) const override;
};

class King : public Piece {
private:
    bool hasMoved;
public:
    King(Position pos, int colour, bool hasMoved) {
        this->position = pos;
        this->colour = colour;
        this->hasMoved = hasMoved;
        this->encoding = 6 * colour;
    };
    moveList getMoves(const Board& board) const override;

};

#endif