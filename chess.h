#include <vector>
#include <memory>
#include <tuple>

class Board;

class Piece {
protected:
    std::vector<int> position;
    int colour;

    Piece(std::vector<int> pos, int col) : position(std::move(pos)), colour(col) {}
    Piece() = default;
public:
    virtual std::vector<std::vector<std::vector<int>>> getMoves(const Board& board) const = 0;
    virtual ~Piece() = default;
};

class Board {
protected:
public:
    std::vector<std::unique_ptr<Piece>> reset();
    std::tuple<int, int> getPiece(const std::vector<int>& position) const;
};

class Pawn : public Piece {
private:
    // Removed duplicate position and colour
    bool taken = false;
    bool hasMoved = false;
    int encoding = 1;
    int direction;

public:
    Pawn(std::vector<int> pos, int col);
    
    std::vector<std::vector<std::vector<int>>> getMoves(const Board& board) const override;
};

class Environment {
private:
    Board board;
    std::vector<std::unique_ptr<Piece>> pieces;
public:

    std::vector<std::unique_ptr<Piece>> reset();

    std::vector<std::vector<std::vector<int>>> getActions();
};
