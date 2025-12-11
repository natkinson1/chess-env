#ifndef PIECES_H
#define PIECES_H

#include <vector>
#include <memory>
#include <tuple>

class Board;

class Piece {
protected:
    std::vector<int> position;
    int colour;
public:
    virtual std::vector<std::vector<std::vector<int>>> getMoves(const Board& board) const = 0;
    virtual ~Piece() = default;
};

class Pawn : public Piece {
private:
    bool taken = false;
    bool hasMoved = false;
    int encoding = 1;
    int direction;
public:
    Pawn(std::vector<int> pos, int colour):
    direction(colour * -1) {
        this->position = pos;
        this->colour = colour;
    }
    std::vector<std::vector<std::vector<int>>> getMoves(const Board& board) const override;
};

#endif