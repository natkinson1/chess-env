#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "pieces.h"
#include "board.h"

// std::vector<std::vector<std::vector<int>>> boardPieces = {
//     // -1 represents no pieces on that square
//     // [pieceEncoding, player]
//     {{4,-1},{3,-1},{2,-1},{5,-1},{6,-1},{2,-1},{3,-1},{1,-1}},
//     {{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1}},
//     {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
//     {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
//     {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
//     {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
//     {{1,1},{1,1},{1,1},{1,1},{1,1},{1,1},{1,1},{1,1}},
//     {{4,1},{3,1},{2,1},{5,1},{6,1},{2,1},{3,1},{1,1}},
// };

// std::vector<std::vector<std::string>> boardCoordiantes = {
//     {"A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8"},
//     {"A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7"},
//     {"A6", "B6", "C6", "D6", "E6", "F6", "G6", "H6"},
//     {"A5", "B5", "C5", "D5", "E5", "F5", "G5", "H5"},
//     {"A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4"},
//     {"A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3"},
//     {"A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2"},
//     {"A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1"},
// };

// std::vector<std::vector<std::vector<int>>> board = {
//     {{0,0}, {0,1}, {0,2}, {0,3}, {0,4}, {0,5}, {0,6}, {0,7}},
//     {{1,0}, {1,1}, {1,2}, {1,3}, {1,4}, {1,5}, {1,6}, {1,7}},
//     {{2,0}, {2,1}, {2,2}, {2,3}, {2,4}, {2,5}, {2,6}, {2,7}},
//     {{3,0}, {3,1}, {3,2}, {3,3}, {3,4}, {3,5}, {3,6}, {3,7}},
//     {{4,0}, {4,1}, {4,2}, {4,3}, {4,4}, {4,5}, {4,6}, {4,7}},
//     {{5,0}, {5,1}, {5,2}, {5,3}, {5,4}, {5,5}, {5,6}, {5,7}},
//     {{6,0}, {6,1}, {6,2}, {6,3}, {6,4}, {6,5}, {6,6}, {6,7}},
//     {{7,0}, {7,1}, {7,2}, {7,3}, {7,4}, {7,5}, {7,6}, {7,7}},
// };

boardEncoding Board::reset() {
    this->board = this->startingBoard;

    // white pieces
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,0}, 1, false));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,1}, 1, false));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,2}, 1, false));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,3}, 1, false));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,4}, 1, false));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,5}, 1, false));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,6}, 1, false));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,7}, 1, false));
    this->pieces.pieces.push_back(std::make_unique<Rook>(Position{7,0}, 1, false));
    this->pieces.pieces.push_back(std::make_unique<Knight>(Position{7,1}, 1));
    this->pieces.pieces.push_back(std::make_unique<Bishop>(Position{7,2}, 1));
    this->pieces.pieces.push_back(std::make_unique<Queen>(Position{7,3}, 1));
    this->pieces.pieces.push_back(std::make_unique<King>(Position{7,4}, 1, false));
    this->pieces.pieces.push_back(std::make_unique<Bishop>(Position{7,5}, 1));
    this->pieces.pieces.push_back(std::make_unique<Knight>(Position{7,6}, 1));
    this->pieces.pieces.push_back(std::make_unique<Rook>(Position{7,7}, 1, false));
    // black pieces
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{1,0}, -1, false));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{1,1}, -1, false));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{1,2}, -1, false));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{1,3}, -1, false));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{1,4}, -1, false));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{1,5}, -1, false));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{1,6}, -1, false));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{1,7}, -1, false));
    this->pieces.pieces.push_back(std::make_unique<Rook>(Position{0,0}, -1, false));
    this->pieces.pieces.push_back(std::make_unique<Knight>(Position{0,1}, -1));
    this->pieces.pieces.push_back(std::make_unique<Bishop>(Position{0,2}, -1));
    this->pieces.pieces.push_back(std::make_unique<Queen>(Position{0,3}, -1));
    this->pieces.pieces.push_back(std::make_unique<King>(Position{0,4}, -1, false));
    this->pieces.pieces.push_back(std::make_unique<Bishop>(Position{0,5}, -1));
    this->pieces.pieces.push_back(std::make_unique<Knight>(Position{0,6}, -1));
    this->pieces.pieces.push_back(std::make_unique<Rook>(Position{0,7}, -1, false));

    return this->board;
};

moveList Board::getActions(int player) {
    // check for en passen
    // check for castling
    moveList allMoves;
    for (const auto& piece : this->pieces){
        if (piece->colour == player) {
            moveList pieceMoves = piece->getMoves(*this);
            allMoves.insert(
                allMoves.end(),
                pieceMoves.begin(),
                pieceMoves.end()
            );
        } else {
            continue;
        }
    }
    return allMoves;
};

void Board::move(Move move) {

    for (auto& piece : pieces) {
        //piece is taken
        if (piece->position == move.to) {
            piece->taken = true;
        }
        if (piece->position == move.from) {
            piece->position = move.to;
        };
    };
};

void Board::undoMove(Move move) {
    for (auto& piece : this->pieces) {
        //undo piece taken
        if (piece->position == move.to) { // what if multiple pieces are taken on same square?
            piece->taken = false;
        }
        if (piece->position == move.to) {
            piece->position = move.from;
        };
    };
}

bool Board::isLegalMove(Move move, int player) {
    // check if move causes piece to be in check.
    // check to see if other player can take king.

    int target = 6 * player;
    Position kingPosition;
    for (const auto& piece : this->pieces) {
        if (piece->encoding == target) {
            kingPosition = piece->position;
        } else {
            continue;
        }
    }
    this->move(move);
    bool inCheck = this->inCheck(player);
    this->undoMove(move);
    
    return !inCheck;
}

bool Board::inCheck(int player) {
    int kingEncoding = 6 * player;
    Position kingPosition;
    for (const auto& piece : this->pieces) {
        if (piece->encoding == kingEncoding) {
            kingPosition = piece->position;
        } else {
            continue;
        }
    }
    moveList allMoves = this->getActions(player * -1);
    for (auto& move : allMoves) {
        if (move.to == kingPosition) {
            return true;
        }
    }
    return false;
}

std::tuple<int, int> Board::getPiece(const Position& position) const {
    int piece = this->board.at(position.row).at(position.col);
    int pieceColour = (piece > 0) ? 1 : ((piece < 0) ? -1 : 0);
    return {piece, pieceColour};
};

void Board::clearBoard() {
    this->board = this->emptyBoard;
}

void Board::arrangeBoard(pieceList& pieces) {
    this->clearBoard();
    for (auto& piece : pieces) {
        int row = piece->position.row;
        int col = piece->position.col;
        int idx = piece->encoding;
        this->board.at(row).at(col) = idx;
    }
}