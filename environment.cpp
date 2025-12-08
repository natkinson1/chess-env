#include <vector>
#include <unordered_map>
#include <iostream>
#include <memory>
#include <tuple>
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

std::vector<std::vector<std::vector<int>>> boardPieces = {
    // -1 represents no pieces on that square
    // [pieceEncoding, player]
    {{4,-1},{3,-1},{2,-1},{5,-1},{6,-1},{2,-1},{3,-1},{4,-1}},
    {{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1}},
    {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
    {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
    {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
    {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
    {{1,1},{1,1},{1,1},{1,1},{1,1},{1,1},{1,1},{1,1}},
    {{4,1},{3,1},{2,1},{5,1},{6,1},{2,1},{3,1},{4,1}},
};

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

// state must be boardEncoding + list of piececlass

struct State {
    std::vector<std::vector<int>> board;
    std::vector<std::unique_ptr<Piece>> pieces;
};


class Environment {
private:
    State state;
    std::vector<std::vector<int>> board;
    std::vector<std::unique_ptr<Piece>> pieces;
public:
    void movePiece() {};

    void step() {};

    std::vector<std::unique_ptr<Piece>> reset() {
        std::vector<std::unique_ptr<Piece>> startingBoard;

        startingBoard.push_back(std::make_unique<Pawn>(std::vector<int>{6,0}, 1));

        return startingBoard;
    }

    std::vector<std::vector<std::vector<int>>> getActions() {
        std::vector<std::vector<std::vector<int>>> allMoves;
        for (const auto& piece : pieces){
            std::vector<std::vector<std::vector<int>>> pieceMoves = piece->getMoves(board);
            
        }
    }

    std::tuple<int, int> getPiece(const std::vector<int>& position) const {
        int piece = board[position[0]][position[1]];
        int pieceColour = (piece > 0) ? 1 : ((piece < 0) ? -1 : 0);
        return {piece, pieceColour};
    };
};