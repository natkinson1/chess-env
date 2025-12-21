#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include "pieces.h"
#include "board.h"

moveList Pawn::getMoves(Board& board) {
    // returns [from, to] coordinates defining the new move.
    // check if move leads to king being in check.
    moveList legalMoves;

    if (!this->hasMoved) {
        Position coord1 = {this->position.row + this->direction, this->position.col};
        Position coord2 = {this->position.row + this->direction * 2, this->position.col};
        Piece* piece1 = board.getPiece(coord1);
        Piece* piece2 = board.getPiece(coord2);
        Move move = {.from=this->position, .to=coord2};
        if (piece1 == nullptr && piece2 == nullptr) {
            legalMoves.push_back(Move{.from=this->position, .to=coord2, .pieceType=pieceType::PAWN});
        };
    };
    // can move 1 forward
    Position coord = {this->position.row + this->direction, this->position.col};
    Piece* piece = board.getPiece(coord);
    if (piece == nullptr) {
        // add promoting moves
        if (coord.row == 0 || coord.row == 7) {
            for (int newPieceEncoding : {
                pieceType::BISHOP, 
                pieceType::KNIGHT,
                pieceType::ROOK, 
                pieceType::QUEEN}) {
                legalMoves.push_back(
                    Move{.from=this->position, .to=coord, .pieceType=pieceType::PAWN, .newEncoding=newPieceEncoding}
                );
            }
        } else {
            legalMoves.push_back(Move{.from=this->position, .to=coord});
        }
        
    }
    // can take diagRight
    Position rightDiag = {this->position.row + this->direction, this->position.col + 1};
    if (rightDiag.row >= 0 && rightDiag.row <= 7 && rightDiag.col <= 7) {
        Piece* piece = board.getPiece(rightDiag);
        if (piece == nullptr) {
        } else if (piece->colour != this->colour) {
            if (rightDiag.row == 0 || rightDiag.row == 7) {
                for (int newPieceEncoding : {
                    pieceType::BISHOP, 
                    pieceType::KNIGHT,
                    pieceType::ROOK, 
                    pieceType::QUEEN}) {
                    legalMoves.push_back(
                        Move{.from=this->position, .to=rightDiag, .pieceType=pieceType::PAWN, .newEncoding=newPieceEncoding}
                    );
                }
            } else {
                legalMoves.push_back(Move{.from=this->position, .to=rightDiag, .pieceType=pieceType::PAWN});
            }
        };
    };
    
    // can take diagLeft
    Position leftDiag = {this->position.row + this->direction, this->position.col - 1};
    if (leftDiag.row >= 0 && leftDiag.row <= 7 && leftDiag.col >= 0) {
        Piece* piece = board.getPiece(leftDiag);
        if (piece == nullptr) {
        } else if (piece->colour != this->colour) {
            if (leftDiag.row == 0 || leftDiag.row==7) {
                for (int newPieceEncoding : {
                    pieceType::BISHOP, 
                    pieceType::KNIGHT,
                    pieceType::ROOK, 
                    pieceType::QUEEN}) {
                    legalMoves.push_back(
                        Move{.from=this->position, .to=leftDiag, .pieceType=pieceType::PAWN, .newEncoding=newPieceEncoding}
                    );
                }
            } else {
                legalMoves.push_back(Move{.from=this->position, .to=leftDiag, .pieceType=pieceType::PAWN});
            }
            
        }
    }
    // en passent
    Move lastMove = board.lastMove;
    bool movedTwo = (lastMove.to.row - lastMove.from.row) * this->colour == 2;
    bool isPawn = lastMove.pieceType == pieceType::PAWN;
    if (isPawn && movedTwo) {
        // look left
        Position posLeft = {.row=this->position.row, .col=this->position.col - 1};
        if (lastMove.to == posLeft && this->position.col -1 >= 0) {
            Piece* piece = board.getPiece(Position{.row=this->position.row, .col=this->position.col - 1});
            legalMoves.push_back(
                Move{.from=this->position, .to=Position{.row=this->position.row + this->direction, .col=this->position.col - 1}, .enPassent=true}
            );
        }
        // look right
        Position posRight = {.row=this->position.row, .col=this->position.col + 1};
        if (lastMove.to == posRight && this->position.col + 1 <= 7) {
            Piece* piece = board.getPiece(Position{.row=this->position.row, .col=this->position.col + 1});
            legalMoves.push_back(
                Move{.from=this->position, .to=Position{.row=this->position.row + this->direction, .col=this->position.col + 1}, .enPassent=true}
            );
        }
    }

    return legalMoves;
};

moveList Rook::getMoves(Board& board) {
    moveList legalMoves;

    bool lookTop = true;
    bool lookLeft = true;
    bool lookRight = true;
    bool lookBottom = true;
    int i = 1;
    while (i <= 7) {
        // top
        if (lookTop && this->position.row - i >= 0) {
            Position coord = {this->position.row - i, this->position.col};
            Piece* piece = board.getPiece(coord);
            if (piece == nullptr) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::ROOK});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::ROOK});
                lookTop = false;
            } else {
                lookTop = false;
            }
        } else {
            lookTop = false;
        }
        // left
        if (lookLeft && this->position.col - i >= 0) {
            Position coord = {this->position.row, this->position.col - i};
            Piece* piece = board.getPiece(coord);
            if (piece == nullptr) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::ROOK});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::ROOK});
                lookLeft = false;
            } else {
                lookLeft = false;
            }
        } else {
            lookLeft = false;
        }
        // right
        if (lookRight && this->position.col + i <= 7) {
            Position coord = {this->position.row, this->position.col + i};
            Piece* piece = board.getPiece(coord);
            if (piece == nullptr) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::ROOK});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::ROOK});
                lookRight = false;
            } else {
                lookRight = false;
            }
        } else {
            lookRight = false;
        }
        // bottom
        if (lookBottom && this->position.row + i <= 7) {
            Position coord = {this->position.row + i, this->position.col};
            Piece* piece = board.getPiece(coord);
            if (piece == nullptr) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::ROOK});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::ROOK});
                lookBottom = false;
            } else {
                lookBottom = false;
            }
        } else {
            lookBottom = false;
        }
        i++;
    }
    return legalMoves;
}

moveList Bishop::getMoves(Board& board) {
    moveList legalMoves;

    bool lookTopRight = true;
    bool lookTopLeft = true;
    bool lookBottomRight = true;
    bool lookBottomLeft = true;
    int i = 1;
    while (i <= 7) {
        // top right
        if (lookTopRight && this->position.row - i >= 0 && this->position.col + i <= 7) {
            Position coord = {this->position.row - i, this->position.col + i};
            Piece* piece = board.getPiece(coord);
            if (piece == nullptr) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::BISHOP});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::BISHOP});
                lookTopRight = false;
            } else {
                lookTopRight = false;
            }
        } else {
            lookTopRight = false;
        }
        // top left
        if (lookTopLeft && this->position.col - i >= 0 && this->position.row - i >= 0) {
            Position coord = {this->position.row - i, this->position.col - i};
            Piece* piece = board.getPiece(coord);
            if (piece == nullptr) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::BISHOP});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::BISHOP});
                lookTopLeft = false;
            } else {
                lookTopLeft = false;
            }
        } else {
            lookTopLeft = false;
        }
        // bottom right
        if (lookBottomRight && this->position.col + i <= 7 && this->position.row + i <= 7) {
            Position coord = {this->position.row + i, this->position.col + i};
            Piece* piece = board.getPiece(coord);
            if (piece == nullptr) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::BISHOP});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::BISHOP});
                lookBottomRight = false;
            } else {
                lookBottomRight = false;
            }
        } else {
            lookBottomRight = false;
        }
        // bottom left
        if (lookBottomLeft && this->position.row + i <= 7 && this->position.col - i >= 0) {
            Position coord = {this->position.row + i, this->position.col - i};
            Piece* piece = board.getPiece(coord);
            if (piece == nullptr) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::BISHOP});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::BISHOP});
                lookBottomLeft = false;
            } else {
                lookBottomLeft = false;
            }
        } else {
            lookBottomLeft = false;
        }
        i++;
    }
    return legalMoves;
}

moveList Queen::getMoves(Board& board) {
    moveList legalMoves;

    bool lookTop = true;
    bool lookLeft = true;
    bool lookRight = true;
    bool lookBottom = true;

    bool lookTopRight = true;
    bool lookTopLeft = true;
    bool lookBottomRight = true;
    bool lookBottomLeft = true;
    int i = 1;
    while (i <= 7) {
        // top
        if (lookTop && this->position.row - i >= 0) {
            Position coord = {this->position.row - i, this->position.col};
            Piece* piece = board.getPiece(coord);
            if (piece == nullptr) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::QUEEN});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::QUEEN});
                lookTop = false;
            } else {
                lookTop = false;
            }
        } else {
            lookTop = false;
        }
        // left
        if (lookLeft && this->position.col - i >= 0) {
            Position coord = {this->position.row, this->position.col - i};
            Piece* piece = board.getPiece(coord);
            if (piece == nullptr) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::QUEEN});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::QUEEN});
                lookLeft = false;
            } else {
                lookLeft = false;
            }
        } else {
            lookLeft = false;
        }
        // right
        if (lookRight && this->position.col + i <= 7) {
            Position coord = {this->position.row, this->position.col + i};
            Piece* piece = board.getPiece(coord);
            if (piece == nullptr) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::QUEEN});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::QUEEN});
                lookRight = false;
            } else {
                lookRight = false;
            }
        } else {
            lookRight = false;
        }
        // bottom
        if (lookBottom && this->position.row + i <= 7) {
            Position coord = {this->position.row + i, this->position.col};
            Piece* piece = board.getPiece(coord);
            if (piece == nullptr) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::QUEEN});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::QUEEN});
                lookBottom = false;
            } else {
                lookBottom = false;
            }
        } else {
            lookBottom = false;
        }

        // top right
        if (lookTopRight && this->position.row - i >= 0 && this->position.col + i <= 7) {
            Position coord = {this->position.row - i, this->position.col + i};
            Piece* piece = board.getPiece(coord);
            if (piece == nullptr) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::QUEEN});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::QUEEN});
                lookTopRight = false;
            } else {
                lookTopRight = false;
            }
        } else {
            lookTopRight = false;
        }
        // top left
        if (lookTopLeft && this->position.col - i >= 0 && this->position.row - i >= 0) {
            Position coord = {this->position.row - i, this->position.col - i};
            Piece* piece = board.getPiece(coord);
            if (piece == nullptr) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::QUEEN});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::QUEEN});
                lookTopLeft = false;
            } else {
                lookTopLeft = false;
            }
        } else {
            lookTopLeft = false;
        }
        // bottom right
        if (lookBottomRight && this->position.col + i <= 7 && this->position.row + i <= 7) {
            Position coord = {this->position.row + i, this->position.col + i};
            Piece* piece = board.getPiece(coord);
            if (piece == nullptr) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::QUEEN});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::QUEEN});
                lookBottomRight = false;
            } else {
                lookBottomRight = false;
            }
        } else {
            lookBottomRight = false;
        }
        // bottom left
        if (lookBottomLeft && this->position.row + i <= 7 && this->position.col - i >= 0) {
            Position coord = {this->position.row + i, this->position.col - i};
            Piece* piece = board.getPiece(coord);
            if (piece == nullptr) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::QUEEN});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back(Move{.from=this->position, .to=coord, .pieceType=pieceType::QUEEN});
                lookBottomLeft = false;
            } else {
                lookBottomLeft = false;
            }
        } else {
            lookBottomLeft = false;
        }
        i++;
    }
    return legalMoves;
}

moveList Knight::getMoves(Board& board) {
    // returns [from, to] coordinates defining the new move.
    // check if move leads to king being in check.
    moveList legalMoves;
    Position topRight = Position{this->position.row - 2, this->position.col + 1};
    Position topLeft = {this->position.row - 2, this->position.col - 1};
    Position rightTop = {this->position.row - 1, this->position.col + 2};
    Position rightBottom = {this->position.row + 1, this->position.col + 2};
    Position bottomRight = {this->position.row + 2, this->position.col + 1};
    Position bottomLeft = {this->position.row + 2, this->position.col - 1};
    Position leftTop = {this->position.row + 1, this->position.col - 2};
    Position leftBottom = {this->position.row - 1, this->position.col - 2};
    std::vector<Position> allMoves = {
        topRight, topLeft, rightTop, rightBottom, bottomRight, bottomLeft, leftTop, leftBottom
    };

    for (Position move : allMoves) {
        if (move.row >= 0 && move.row <= 7 && move.col >= 0 && move.col <= 7) {
            Piece* piece = board.getPiece(move);
            if (piece == nullptr) {
                legalMoves.push_back(Move{.from=this->position, .to=move, .pieceType=pieceType::KNIGHT});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back(Move{.from=this->position, .to=move, .pieceType=pieceType::KNIGHT});
            }
        }
    }
    
    return legalMoves;
};

moveList King::getMoves(Board& board) {
    // returns [from, to] coordinates defining the new move.
    // check if move leads to king being in check.
    moveList legalMoves;
    Position top = {this->position.row - 1, this->position.col};
    Position right = {this->position.row, this->position.col + 1};
    Position left = {this->position.row, this->position.col - 1};
    Position bottom = {this->position.row + 1, this->position.col};
    Position topRight = {this->position.row - 1, this->position.col + 1};
    Position topLeft = {this->position.row - 1, this->position.col - 1};
    Position bottomRight = {this->position.row + 1, this->position.col + 1};
    Position bottomLeft = {this->position.row + 1, this->position.col - 1};
    std::vector<Position> allMoves = {
        top, right, left, bottom, topRight, topLeft, bottomRight, bottomLeft
    };

    for (Position move : allMoves) {
        if (move.row >= 0 && move.row <= 7 && move.col >= 0 && move.col <= 7) {
            Piece* piece = board.getPiece(move);
            if (piece == nullptr) {
                legalMoves.push_back(Move{.from=this->position, .to=move, .pieceType=pieceType::KING});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back(Move{.from=this->position, .to=move, .pieceType=pieceType::KING});
            }
        }
    }
    return legalMoves;
};