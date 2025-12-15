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
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,0}, 1, false, 0));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,1}, 1, false, 1));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,2}, 1, false, 2));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,3}, 1, false, 3));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,4}, 1, false, 4));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,5}, 1, false, 5));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,6}, 1, false, 6));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,7}, 1, false, 7));
    this->pieces.pieces.push_back(std::make_unique<Rook>(Position{7,0}, 1, false, 8));
    // this->pieces.pieces.push_back(std::make_unique<Knight>(Position{7,1}, 1, 9));
    // this->pieces.pieces.push_back(std::make_unique<Bishop>(Position{7,2}, 1, 10));
    // this->pieces.pieces.push_back(std::make_unique<Queen>(Position{7,3}, 1, 11));
    this->pieces.pieces.push_back(std::make_unique<King>(Position{7,4}, 1, false, 12));
    // this->pieces.pieces.push_back(std::make_unique<Bishop>(Position{7,5}, 1, 13));
    // this->pieces.pieces.push_back(std::make_unique<Knight>(Position{7,6}, 1, 14));
    this->pieces.pieces.push_back(std::make_unique<Rook>(Position{7,7}, 1, false, 15));
    // black pieces
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{1,0}, -1, false, 16));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{1,1}, -1, false, 17));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{1,2}, -1, false, 18));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{1,3}, -1, false, 19));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{1,4}, -1, false, 20));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{1,5}, -1, false, 21));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{1,6}, -1, false, 22));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{1,7}, -1, false, 23));
    this->pieces.pieces.push_back(std::make_unique<Rook>(Position{0,0}, -1, false, 24));
    this->pieces.pieces.push_back(std::make_unique<Knight>(Position{0,1}, -1, 25));
    this->pieces.pieces.push_back(std::make_unique<Bishop>(Position{0,2}, -1, 26));
    this->pieces.pieces.push_back(std::make_unique<Queen>(Position{0,3}, -1, 27));
    this->pieces.pieces.push_back(std::make_unique<King>(Position{0,4}, -1, false, 28));
    this->pieces.pieces.push_back(std::make_unique<Bishop>(Position{0,5}, -1, 29));
    this->pieces.pieces.push_back(std::make_unique<Knight>(Position{0,6}, -1, 30));
    this->pieces.pieces.push_back(std::make_unique<Rook>(Position{0,7}, -1, false, 31));

    return this->board;
};

moveList Board::getMoves(int player) {
    moveList allMoves = this->getAllActions(player);

    moveList allLegalMoves = this->getLegalActions(allMoves, player);
    moveList castleMoves = this->castlingMoves(player);

    return allLegalMoves;
}

moveList Board::getAllActions(int player) {
    // check for en passen
    // check for castling
    moveList allMoves;
    for (const auto& piece : this->pieces){
        if (piece->colour == player && !piece->taken) {
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

moveList Board::getLegalActions(moveList moves, int player) {
    moveList legalMoves;
    for (Move move : moves) {
        bool isLegal = this->isLegalMove(move, player);
        if (isLegal) {
            legalMoves.push_back(move);
        } else {
            continue;
        }
    }
    return legalMoves;
}

void Board::move(Move& move) {

    this->board[move.to.row][move.to.col] = this->board[move.from.row][move.from.col];
    this->board[move.from.row][move.from.col] = 0;

    for (auto& piece : pieces) {
        //piece is taken
        if (piece->position == move.to && !piece->taken) {
            piece->taken = true;
            move.pieceTakenId = piece->id;
        }
        if (piece->position == move.from && !piece->taken) {
            piece->position = move.to;
        };
    };
};

void Board::undoMove(Move& move) {
    
    this->board[move.from.row][move.from.col] = this->board[move.to.row][move.to.col];
    if (move.pieceTakenId != -1) {
        this->board[move.to.row][move.to.col] = move.pieceTakenId;
    } else {
        this->board[move.to.row][move.to.col] = 0;
    }
    

    for (auto& piece : this->pieces) {
        //undo piece taken
        if (piece->id == move.pieceTakenId) {
            piece->taken = false;
            move.pieceTakenId = -1;
        }
        if (piece->position == move.to && !piece->taken) {
            piece->position = move.from;
        };
    };
};

bool Board::isLegalMove(Move& move, int player) {
    // check if move causes piece to be in check.
    // check to see if other player can take king.

    this->move(move);
    bool inCheck = this->inCheck(player);
    this->undoMove(move);
    
    return !inCheck;
}

bool Board::inCheck(int player) {
    Piece* king = this->getKing(player);
    moveList allMoves = this->getAllActions(player * -1);
    for (auto& move : allMoves) {
        if (move.to == king->position) {
            return true;
        }
    }
    return false;
}

Piece* Board::getPiece(const Position& position) const {
    for (auto& piece : this->pieces) {
        if (piece->position == position && !piece->taken) {
            return piece.get();
        }
    }
    return nullptr;
};

moveList Board::castlingMoves(int player) {
    moveList allMoves;
    int rank = (player == 1) ? 7 : 0;
    int rookEncoding = 4 * player;
    Piece* king = this->getKing(player);
    if (king->hasMoved) {
        return allMoves;
    }
    //check kingside
    Position pos1 = {.row=rank, .col=7};
    Piece* kingRook = this->getPiece(pos1);
    moveList kingRookMoves = kingRook->getMoves(*this);
    bool isClearRight = false;
    for (Move move : kingRookMoves) {
        if (move.to == Position{king->position.row, king->position.col + 1}) {
            isClearRight = true;
        }
    }

    if (kingRook != nullptr && kingRook->encoding == rookEncoding && !kingRook->hasMoved && isClearRight) {
        Move move = {.castleKS=true};
        allMoves.push_back(move);
    }

    //check queenside
    Position pos2 = {.row=rank, .col=0};
    Piece* queenRook = this->getPiece(pos2);
    moveList queenRookMoves = queenRook->getMoves(*this);
    bool isClearLeft = false;
    for (Move move : queenRookMoves) {
        if (move.to == Position{king->position.row, king->position.col - 1}) {
            isClearLeft = true;
        }
    }

    if (queenRook != nullptr && queenRook->encoding == rookEncoding && !queenRook->hasMoved && isClearLeft) {
        Move move = {.castleQS=true};
        allMoves.push_back(move);
    }
    return allMoves;
}

Piece* Board::getKing(int player) {
    int kingEncoding = 6 * player;
    Position kingPosition;
    for (const auto& piece : this->pieces) {
        if (piece->encoding == kingEncoding) {
            return piece.get();
        } else {
            continue;
        }
    }
    return nullptr;
}

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