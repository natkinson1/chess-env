#include "pieces.h"
#include "board.h"

void Board::reset() {
    
    this->pieces.pieces.clear();
    this->pieces.pieces.reserve(32);
    

    // // white pieces
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,0}, 1, false, 0));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,1}, 1, false, 1));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,2}, 1, false, 2));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,3}, 1, false, 3));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,4}, 1, false, 4));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,5}, 1, false, 5));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,6}, 1, false, 6));
    this->pieces.pieces.push_back(std::make_unique<Pawn>(Position{6,7}, 1, false, 7));
    this->pieces.pieces.push_back(std::make_unique<Rook>(Position{7,0}, 1, false, 8));
    this->pieces.pieces.push_back(std::make_unique<Knight>(Position{7,1}, 1, 9));
    this->pieces.pieces.push_back(std::make_unique<Bishop>(Position{7,2}, 1, 10));
    this->pieces.pieces.push_back(std::make_unique<Queen>(Position{7,3}, 1, 11));
    this->pieces.pieces.push_back(std::make_unique<King>(Position{7,4}, 1, false, 12));
    this->pieces.pieces.push_back(std::make_unique<Bishop>(Position{7,5}, 1, 13));
    this->pieces.pieces.push_back(std::make_unique<Knight>(Position{7,6}, 1, 14));
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
    this->lastMove = Move{.from=Position{.row=0, .col=0}, .to=Position{.row=0, .col=0}, .pieceType=pieceType::PAWN};

    // pawn, bishop, knight, rook, queen
    this->pieceCountWhite = {0, 8, 2, 2, 2, 1};
    this->pieceCountBlack = {0, 8, 2, 2, 2, 1};
};

moveList Board::getMoves(int player) {
    moveList allMoves = this->getAllActions(player);

    moveList allLegalMoves = this->getLegalActions(allMoves, player);
    moveList castleMoves = this->castlingMoves(player);

    allLegalMoves.insert(
        allLegalMoves.end(),
        castleMoves.begin(),
        castleMoves.end()
    );

    return allLegalMoves;
}

moveList Board::getAllActions(int player) {
    // check for en passen
    // check for castling
    moveList allMoves;
    for (auto& piece : this->pieces){
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

void Board::move(Move& move, int player) {

    // if move is castle KS
    // if move is pawn promotion
    // if move in enpassen
    if (move.castleKS) {
        int rank = (player == 1) ? 7 : 0;
        Piece* king = this->getKing(player);
        Piece* kingRook = this->getPiece(Position{.row=rank, .col=7});

        king->position = Position{.row=rank, .col=6};
        kingRook->position = Position{.row=rank, .col=5};

    } else if (move.castleQS) {
        int rank = (player == 1) ? 7 : 0;
        Piece* king = this->getKing(player);
        Piece* kingRook = this->getPiece(Position{.row=rank, .col=0});

        king->position = Position{.row=rank, .col=2};
        kingRook->position = Position{.row=rank, .col=3};

    } else if (move.enPassent) {
        for (auto& piece: this->pieces) {
            if (piece->position == move.from && !piece->taken) {
                move.hasMoved = piece->hasMoved;
                piece->position = move.to;
                move.movedPieceId = piece->id;
                piece->hasMoved = true;
                Piece* takenPiece = this->getPiece(Position{.row=piece->position.row - piece->direction, .col=move.to.col});
                this->takePiece(takenPiece);
                move.pieceTakenId = takenPiece->id;
                break;
            }
        }
        this->move50rule = 0;
    } else if (move.newEncoding != -1000) {
        // pawn promotion
        Piece* promotingPawn = this->getPiece(move.from);
        move.movedPieceId = promotingPawn->id;
        this->takePiece(promotingPawn);
        Piece* takenPiece = this->getPiece(move.to);
        if (takenPiece) {
            move.pieceTakenId = takenPiece->id;
            this->takePiece(takenPiece);
        }
        switch(move.newEncoding) {
            case pieceType::BISHOP:
                this->pieces.pieces.push_back(
                    std::make_unique<Bishop>(move.to, player, this->pieceIdCounter)
                );
                this->pieceIdCounter+=1;
                this->incrementPieceCount(player, 2);
                break;
            case pieceType::KNIGHT:
                this->pieces.pieces.push_back(
                    std::make_unique<Knight>(move.to, player, this->pieceIdCounter)
                );
                this->pieceIdCounter+=1;
                this->incrementPieceCount(player, 3);
                break;
            case pieceType::ROOK:
                this->pieces.pieces.push_back(
                    std::make_unique<Rook>(move.to, player, true, this->pieceIdCounter)
                );
                this->pieceIdCounter+=1;
                this->incrementPieceCount(player, 4);
                break;
            case pieceType::QUEEN:
                this->pieces.pieces.push_back(
                    std::make_unique<Queen>(move.to, player, this->pieceIdCounter)
                );
                this->pieceIdCounter+=1;
                this->incrementPieceCount(player, 5);
                break;
        }
        this->move50rule = 0;
    } else {
        for (auto& piece : this->pieces) {
            //piece is taken
            if (piece->position == move.to && !piece->taken) {
                this->takePiece(piece.get());
                move.pieceTakenId = piece->id;
                this->move50rule = 0;
            }
            if (piece->position == move.from && !piece->taken) {
                move.hasMoved = piece->hasMoved;
                piece->position = move.to;
                piece->hasMoved = true;
                move.movedPieceId = piece->id;
                if (piece->type == pieceType::PAWN) {
                    this->move50rule = 0;
                }
            };
        };
    }
    this->lastMove = move;
    this->move50rule += 1;
};

void Board::undoMove(Move& move, int player) {
    //TODO: Undo promotion move.
    if (move.castleKS) {
        int rank = (player == 1) ? 7 : 0;
        Piece* king = this->getKing(player);
        Piece* kingRook = this->getPiece(Position{.row=rank, .col=5});

        king->position = Position{.row=rank, .col=4};
        kingRook->position = Position{.row=rank, .col=7};

    } else if (move.castleQS) {
        int rank = (player == 1) ? 7 : 0;
        Piece* king = this->getKing(player);
        Piece* queenRook = this->getPiece(Position{.row=rank, .col=3});

        king->position = Position{.row=rank, .col=4};
        queenRook->position = Position{.row=rank, .col=0};

    } else if (move.enPassent) {
        for (auto& piece: this->pieces) {
            if (move.movedPieceId == piece->id) {
                piece->hasMoved = move.hasMoved;
                piece->position = move.from;
            }
            if (piece->id == move.pieceTakenId) {
                this->undoTakePiece(piece.get());
            }
        }
    } else if (move.newEncoding != -1000) {
        for (auto& piece: this->pieces) {
            if (piece->id == move.pieceTakenId) {
                this->undoTakePiece(piece.get());
            } else if (piece->id == move.movedPieceId) {
                this->undoTakePiece(piece.get());
            }
        }
        
        Piece* promotedPiece = this->pieces.pieces.back().get();
        this->decrementPieceCount(promotedPiece->colour, promotedPiece->type);
        this->pieces.pieces.pop_back(); // remove newly made piece
        this->pieceIdCounter-=1;
    }
    
    else {
        for (auto& piece : this->pieces) {
            //undo piece taken
            if (piece->id == move.pieceTakenId) {
                this->undoTakePiece(piece.get());
                move.pieceTakenId = -1;
            }
            if (piece->id == move.movedPieceId) {
                piece->position = move.from;
                piece->hasMoved = move.hasMoved; // restore hasMoved state
            };
        };
    }
};

bool Board::isLegalMove(Move& move, int player) {
    // check if move causes piece to be in check.
    // check to see if other player can take king.
    int oldmove50rule = this->move50rule;
    Move oldMove = this->lastMove;

    this->move(move, player);
    bool inCheck = this->inCheck(player);
    this->undoMove(move, player);

    this->lastMove = oldMove;
    this->move50rule = oldmove50rule;

    return !inCheck;
}

bool Board::inCheck(int player) {
    Piece* king = this->getKing(player);
    moveList allMoves = this->getAllActions(player * -1);
    for (Move& move : allMoves) {
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
    // see if king moves through check
    bool movesThroughCheckKS = false;
    bool movesThroughCheckQS = false;
    moveList opponentMoves = this->getAllActions(player * -1);
    for (Move move : opponentMoves) {
        // king side
        if (move.to == Position{.row=rank, .col=4} || move.to == Position{.row=rank, .col=5} || move.to == Position{.row=rank, .col=6}) {
            movesThroughCheckKS = true;
        }
        // queen side
        if (move.to == Position{.row=rank, .col=4} || move.to == Position{.row=rank, .col=3} || move.to == Position{.row=rank, .col=2}) {
            movesThroughCheckQS = true;
        }
    }
    //check kingside
    Position pos1 = {.row=rank, .col=7};
    Piece* kingRook = this->getPiece(pos1);
    if (kingRook != nullptr) {
        // moveList kingRookMoves = kingRook->getMoves(*this);
        bool isClearRight = true;
        for (auto& piece : this->pieces) {
            if (piece->taken) {
                continue;
            } else {
                if (piece->position == Position{king->position.row, king->position.col + 1} || 
                    piece->position == Position{king->position.row, king->position.col + 2}) {
                    isClearRight = false;
                }
            }
            
        }

        if (kingRook->encoding == rookEncoding && !kingRook->hasMoved && isClearRight && !movesThroughCheckKS) {
            Move move = {.from=Position{.row=rank, .col=4}, .to=Position{.row=rank, .col=6}, .castleKS=true};
            allMoves.push_back(move);
        }
    };
    

    //check queenside
    Position pos2 = {.row=rank, .col=0};
    Piece* queenRook = this->getPiece(pos2);
    if (queenRook != nullptr) {
        // moveList queenRookMoves = queenRook->getMoves(*this);
        bool isClearLeft = true;
        for (auto& piece : this->pieces) {
            if (piece->taken) {
                continue;
            } else {
                if (piece->position == Position{king->position.row, king->position.col - 1} || 
                    piece->position == Position{king->position.row, king->position.col - 2} ||
                    piece->position == Position{king->position.row, king->position.col - 3}) {
                    isClearLeft = false;
                }
            }
        }

        if (queenRook->encoding == rookEncoding && !queenRook->hasMoved && isClearLeft && !movesThroughCheckQS) {
            Move move = {.from=Position{.row=rank, .col=4}, .to=Position{.row=rank, .col=2}, .castleQS=true};
            allMoves.push_back(move);
        }
    }
    
    return allMoves;
}

Piece* Board::getKing(int player) {
    int kingEncoding = 6 * player;
    Position kingPosition;
    for (auto& piece : this->pieces) {
        if (piece->encoding == kingEncoding) {
            return piece.get();
        } else {
            continue;
        }
    }
    return nullptr;
}

bool Board::isCheckMate(int player) {
    moveList moves = this->getMoves(player);
    bool inCheck = this->inCheck(player);

    if (moves.size() == 0 && inCheck) {
        return true;
    }
    return false;
}

bool Board::isStaleMate(int player) {
    moveList moves = this->getMoves(player);
    bool inCheck = this->inCheck(player);

    if (moves.size() == 0 && !inCheck) {
        return true;
    }
    return false;
}

bool Board::drawByInsufficientMaterial() {
    bool insufficientMaterialWhite = false;
    bool insufficientMaterialBlack = false;
    std::array<int, 6> oneBishopOnly = {0,0,1,0,0,0};
    std::array<int, 6> oneKnightOnly = {0,0,0,1,0,0};
    std::array<int, 6> twoKnightsOnly = {0,0,0,2,0,0};
    std::array<int, 6> noPieces = {0,0,0,0,0,0};

    if(this->pieceCountWhite == oneBishopOnly) {
        insufficientMaterialWhite = true;
    } else if (this->pieceCountWhite == oneKnightOnly) {
        insufficientMaterialWhite = true;
    } else if (this->pieceCountWhite == twoKnightsOnly && this->pieceCountBlack == noPieces) {
        insufficientMaterialWhite = true;
        insufficientMaterialBlack = true;
    } else if (this->pieceCountWhite == noPieces) {
        insufficientMaterialWhite = true;
    } 
    if(this->pieceCountBlack == oneBishopOnly) {
        insufficientMaterialBlack = true;
    } else if (this->pieceCountBlack == oneKnightOnly) {
        insufficientMaterialBlack = true;
    } else if (this->pieceCountBlack == twoKnightsOnly && this->pieceCountWhite == noPieces) {
        insufficientMaterialWhite = true;
        insufficientMaterialBlack = true;
    } else if (this->pieceCountBlack == noPieces) {
        insufficientMaterialBlack = true;
    }
    return insufficientMaterialWhite && insufficientMaterialBlack;
}

bool Board::drawBy50MoveRule() {
    if (this->move50rule >= 50) {
        return true;
    }
    return false;
}

void Board::takePiece(Piece* piece) {
    piece->taken = true;
    if (piece->colour == pieceColour::WHITE) {
        this->pieceCountWhite[piece->type] -= 1;
    } else {
        this->pieceCountBlack[piece->type] -= 1;
    }
};

void Board::undoTakePiece(Piece* piece) {
    piece->taken = false;
    if (piece->colour == pieceColour::WHITE) {
        this->pieceCountWhite[piece->type] += 1;
    } else {
        this->pieceCountBlack[piece->type] += 1;
    }
};

void Board::incrementPieceCount(int pieceColour, int pieceType) {
    if (pieceColour == pieceColour::WHITE) {
        this->pieceCountWhite[pieceType] += 1;
    } else {
        this->pieceCountBlack[pieceType] += 1;
    }
};

void Board::decrementPieceCount(int pieceColour, int pieceType) {
    if (pieceColour == pieceColour::WHITE) {
        this->pieceCountWhite[pieceType] -= 1;
    } else {
        this->pieceCountBlack[pieceType] -= 1;
    }
}