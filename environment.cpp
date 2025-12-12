#include <vector>
#include <unordered_map>
#include <iostream>
#include <memory>
#include <tuple>
#include "environment.h"
#include "pieces.h"

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

// new encoding
std::vector<std::vector<int>> boardPieces = {
    // -1 represents no pieces on that square
    // [pieceEncoding, player]
    {-4, -3, -2, -5, -6, -2, -3, -4},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {4, 3, 2, 5, 6, 2, 3, 4},
};

// std::vector<std::vector<std::vector<int>>> boardPieces = {
//     // -1 represents no pieces on that square
//     // [pieceEncoding, player]
//     {{4,-1},{3,-1},{2,-1},{5,-1},{6,-1},{2,-1},{3,-1},{4,-1}},
//     {{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1}},
//     {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
//     {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
//     {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
//     {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
//     {{1,1},{1,1},{1,1},{1,1},{1,1},{1,1},{1,1},{1,1}},
//     {{4,1},{3,1},{2,1},{5,1},{6,1},{2,1},{3,1},{4,1}},
// };

std::vector<std::vector<std::vector<int>>> board = {
    {{0,0}, {0,1}, {0,2}, {0,3}, {0,4}, {0,5}, {0,6}, {0,7}},
    {{1,0}, {1,1}, {1,2}, {1,3}, {1,4}, {1,5}, {1,6}, {1,7}},
    {{2,0}, {2,1}, {2,2}, {2,3}, {2,4}, {2,5}, {2,6}, {2,7}},
    {{3,0}, {3,1}, {3,2}, {3,3}, {3,4}, {3,5}, {3,6}, {3,7}},
    {{4,0}, {4,1}, {4,2}, {4,3}, {4,4}, {4,5}, {4,6}, {4,7}},
    {{5,0}, {5,1}, {5,2}, {5,3}, {5,4}, {5,5}, {5,6}, {5,7}},
    {{6,0}, {6,1}, {6,2}, {6,3}, {6,4}, {6,5}, {6,6}, {6,7}},
    {{7,0}, {7,1}, {7,2}, {7,3}, {7,4}, {7,5}, {7,6}, {7,7}},
};

std::tuple<std::vector<std::vector<int>>, int> Environment::reset() {
    
    std::vector<std::vector<int>> state = this->board.reset();

    return {state, 1};
}

void Environment::loadState(std::vector<std::unique_ptr<Piece>>& pieces) {
    this->pieces.clear();
    this->pieces = std::move(pieces);
    this->board.arrangeBoard(this->pieces);
}