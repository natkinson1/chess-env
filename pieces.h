#include <vector>

class Piece {
protected:
    std::vector<int> position;
    int colour;
public:
    std::vector<std::vector<std::vector<int>>> getMoves(std::vector<std::vector<int>> board) {}
};

class Pawn : public Piece {
private:
    bool taken = false;
    bool hasMoved = false;
    int encoding = 1;
    int direction;

public:
    Pawn(std::vector<int> pos, int col);
};

