#include <vector>
#include <unordered_map>
#include <iostream>
#include "pieces.cpp"

std::unordered_map<std::string, int> player = {
    {"black", -1},
    {"white", 1}
};

std::unordered_map<std::string, int> pieceEncoding = {
    {"pawn", 1},
    {"bishop", 2},
    {"knight", 3},
    {"rook", 4},
    {"queen", 5},
    {"king", 6}
};

// state must be boardEncoding + list of pieceClasses
std::vector<Piece>

class Environment {
private:
    std::vector<std::vector<std::vector<int>>> boardEncoding;

public:
    void movePiece() {}

    void loadState(std::vector<std::vector<std::vector<int>>> state) {
        boardEncoding = state;
    }

    std::vector<std::vector<std::vector<int>>> getActions() {

    }
};