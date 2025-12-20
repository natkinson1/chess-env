#ifndef ALGEBRAIC_NOTATION_H
#define ALGEBRAIC_NOTATION_H

#include <string>
#include "pieces.h"

// Function declarations
std::string square(const Position& pos);
std::string getPieceLetter(int pieceType);
std::string getAlgebraicNotation(Move move);

#endif