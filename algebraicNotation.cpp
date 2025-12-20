#include <vector>
#include "algebraicNotation.h"
#include "pieces.h"

std::vector<std::vector<std::string>> boardCoordinates = {
    {"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"},
    {"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7"},
    {"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6"},
    {"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5"},
    {"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4"},
    {"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3"},
    {"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2"},
    {"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"},
};

std::string getPieceLetter(int type) {
    std::string pieceLetter;
    switch(type) {
        case pieceType::PAWN:
            pieceLetter = "";
            break;
        case pieceType::BISHOP:
            pieceLetter = "B";
            break;
        case pieceType::KNIGHT:
            pieceLetter = "N";
            break;
        case pieceType::ROOK:
            pieceLetter = "R";
            break;
        case pieceType::QUEEN:
            pieceLetter = "Q";
            break;
        case pieceType::KING:
            pieceLetter = "K";
            break;
        default:
            throw std::invalid_argument("Invalid pieceType: " + std::to_string(type));
    }
    return pieceLetter;
}

std::string square(const Position& pos) {
    return boardCoordinates[pos.row][pos.col];
}

std::string getAlgebraicNotation(Move move) {
    std::string moveString;
    if (move.newEncoding != -1000) {
        // promoting piece
        moveString += square(move.from);
        moveString += square(move.to);
        moveString += getPieceLetter(move.newEncoding);
    } else {
        // normal move
        moveString += square(move.from);
        moveString += square(move.to);
    }
    
    return moveString;
}