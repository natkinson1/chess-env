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

    if (!hasMoved) {
        Position coord1 = {this->position.row + direction, this->position.col};
        Position coord2 = {this->position.row + direction * 2, this->position.col};
        Piece* piece1 = board.getPiece(coord1);
        Piece* piece2 = board.getPiece(coord2);
        Move move = {.from=position, .to=coord2};
        if (piece1 == nullptr && piece2 == nullptr) {
            legalMoves.push_back({position, coord2});
        };
    };
    // can move 1 forward
    Position forward = {this->position.row + direction, this->position.col};
    Piece* piece = board.getPiece(forward);
    if (piece == nullptr) {
        legalMoves.push_back({position, forward});
    }
    // can take diagRight
    Position rightDiag = {this->position.row - direction, this->position.col + 1};
    if (rightDiag.row > 0 && rightDiag.row <= 7 && rightDiag.col <= 7) {
        Piece* piece = board.getPiece(rightDiag);
        if (piece == nullptr) {
        } else if (piece->colour != this->colour) {
            legalMoves.push_back({position, rightDiag});
        };
    };
    
    // can take diagLeft
    Position leftDiag = {this->position.row - direction, this->position.col - 1};
    if (leftDiag.row > 0 && leftDiag.row < 8 && leftDiag.col > 0) {
        Piece* piece = board.getPiece(leftDiag);
        if (piece == nullptr) {
        } else if (piece->colour != this->colour) {
            legalMoves.push_back({position, leftDiag});
        }
    }
    // en passen
    // if promotes
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
                legalMoves.push_back({position, coord});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back({position, coord});
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
                legalMoves.push_back({position, coord});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back({position, coord});
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
                legalMoves.push_back({position, coord});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back({position, coord});
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
                legalMoves.push_back({position, coord});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back({position, coord});
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
                legalMoves.push_back({position, coord});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back({position, coord});
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
                legalMoves.push_back({position, coord});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back({position, coord});
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
                legalMoves.push_back({position, coord});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back({position, coord});
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
                legalMoves.push_back({position, coord});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back({position, coord});
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
                legalMoves.push_back({position, coord});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back({position, coord});
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
                legalMoves.push_back({position, coord});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back({position, coord});
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
                legalMoves.push_back({position, coord});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back({position, coord});
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
                legalMoves.push_back({position, coord});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back({position, coord});
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
                legalMoves.push_back({position, coord});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back({position, coord});
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
                legalMoves.push_back({position, coord});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back({position, coord});
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
                legalMoves.push_back({position, coord});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back({position, coord});
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
                legalMoves.push_back({position, coord});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back({position, coord});
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
    Position bottomLeft = {this->position.row + 2, this->position.col + 1};
    Position leftTop = {this->position.row + 1, this->position.col - 2};
    Position leftBottom = {this->position.row - 1, this->position.col - 2};
    std::vector<Position> allMoves = {
        topRight, topLeft, rightTop, rightBottom, bottomRight, bottomLeft, leftTop, leftBottom
    };

    for (Position move : allMoves) {
        if (move.row >= 0 && move.row <= 7 && move.col >= 0 && move.col <= 7) {
            Piece* piece = board.getPiece(move);
            if (piece == nullptr) {
                legalMoves.push_back({position, move});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back({position, move});
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
    Position bottomLeft = {this->position.row + 1, this->position.col + 1};
    std::vector<Position> allMoves = {
        top, right, left, bottom, topRight, topLeft, bottomRight, bottomLeft
    };

    for (Position move : allMoves) {
        if (move.row >= 0 && move.row <= 7 && move.col >= 0 && move.col <= 7) {
            Piece* piece = board.getPiece(move);
            if (piece == nullptr) {
                legalMoves.push_back({position, move});
            } else if (piece->colour != this->colour) {
                legalMoves.push_back({position, move});
            }
        }
    }
    
    return legalMoves;
};