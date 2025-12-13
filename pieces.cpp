#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include "pieces.h"
#include "board.h"

moveList Pawn::getMoves(const Board& board) const {
    // returns [from, to] coordinates defining the new move.
    // check if move leads to king being in check.
    moveList legalMoves;

    if (!hasMoved) {
        Position coord1 = {position.row + direction, position.col};
        Position coord2 = {position.row + direction * 2, position.col};
        auto [piece1, pieceColour1] = board.getPiece(coord1);
        auto [piece2, pieceColour2] = board.getPiece(coord2);
        if (pieceColour1 == 0 && pieceColour2 == 0) {
            legalMoves.push_back({position, coord2});
        };
    };
    // can move 1 forward
    Position forward = {position.row + direction, position.col};
    auto [piece, pieceColour] = board.getPiece(forward);
    if (pieceColour == 0) {
        legalMoves.push_back({position, forward});
    }
    // can take diagRight
    Position rightDiag = {position.row - direction, position.col + 1};
    if (rightDiag.row > 0 && rightDiag.row <= 7 && rightDiag.col <= 7) {
        auto [piece, pieceColour] = board.getPiece(rightDiag);
        if (pieceColour != colour && pieceColour != 0) {
            legalMoves.push_back({position, rightDiag});
        };
    };
    
    // can take diagLeft
    Position leftDiag = {position.row - direction, position.col - 1};
    if (leftDiag.row > 0 && leftDiag.row < 8 && leftDiag.col > 0) {
        auto [piece, pieceColour] = board.getPiece(leftDiag);
        if (pieceColour != colour && pieceColour != 0) {
            legalMoves.push_back({position, leftDiag});
        }
    }
    // en passen
    // if promotes
    return legalMoves;
};

moveList Rook::getMoves(const Board& board) const {
    moveList legalMoves;

    bool lookTop = true;
    bool lookLeft = true;
    bool lookRight = true;
    bool lookBottom = true;
    int i = 1;
    while (i <= 7) {
        // top
        if (lookTop && position.row - i >= 0) {
            Position coord = {position.row - i, position.col};
            auto [piece, pieceColour] = board.getPiece(coord);
            if (pieceColour == 0) {
                legalMoves.push_back({position, coord});
            } else if (pieceColour != colour) {
                legalMoves.push_back({position, coord});
                lookTop = false;
            } else {
                lookTop = false;
            }
        } else {
            lookTop = false;
        }
        // left
        if (lookLeft && position.col - i >= 0) {
            Position coord = {position.row, position.col - i};
            auto [piece, pieceColour] = board.getPiece(coord);
            if (pieceColour == 0) {
                legalMoves.push_back({position, coord});
            } else if (pieceColour != colour) {
                legalMoves.push_back({position, coord});
                lookLeft = false;
            } else {
                lookLeft = false;
            }
        } else {
            lookLeft = false;
        }
        // right
        if (lookRight && position.col + i <= 7) {
            Position coord = {position.row, position.col + i};
            auto [piece, pieceColour] = board.getPiece(coord);
            if (pieceColour == 0) {
                legalMoves.push_back({position, coord});
            } else if (pieceColour != colour) {
                legalMoves.push_back({position, coord});
                lookRight = false;
            } else {
                lookRight = false;
            }
        } else {
            lookRight = false;
        }
        // bottom
        if (lookBottom && position.row + i <= 7) {
            Position coord = {position.row + i, position.col};
            auto [piece, pieceColour] = board.getPiece(coord);
            if (pieceColour == 0) {
                legalMoves.push_back({position, coord});
            } else if (pieceColour != colour) {
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

moveList Bishop::getMoves(const Board& board) const {
    moveList legalMoves;

    bool lookTopRight = true;
    bool lookTopLeft = true;
    bool lookBottomRight = true;
    bool lookBottomLeft = true;
    int i = 1;
    while (i <= 7) {
        // top right
        if (lookTopRight && position.row - i >= 0 && position.col + i <= 7) {
            Position coord = {position.row - i, position.col + i};
            auto [piece, pieceColour] = board.getPiece(coord);
            if (pieceColour == 0) {
                legalMoves.push_back({position, coord});
            } else if (pieceColour != colour) {
                legalMoves.push_back({position, coord});
                lookTopRight = false;
            } else {
                lookTopRight = false;
            }
        } else {
            lookTopRight = false;
        }
        // top left
        if (lookTopLeft && position.col - i >= 0 && position.row - i >= 0) {
            Position coord = {position.row - i, position.col - i};
            auto [piece, pieceColour] = board.getPiece(coord);
            if (pieceColour == 0) {
                legalMoves.push_back({position, coord});
            } else if (pieceColour != colour) {
                legalMoves.push_back({position, coord});
                lookTopLeft = false;
            } else {
                lookTopLeft = false;
            }
        } else {
            lookTopLeft = false;
        }
        // bottom right
        if (lookBottomRight && position.col + i <= 7 && position.row + i <= 7) {
            Position coord = {position.row + i, position.col + i};
            auto [piece, pieceColour] = board.getPiece(coord);
            if (pieceColour == 0) {
                legalMoves.push_back({position, coord});
            } else if (pieceColour != colour) {
                legalMoves.push_back({position, coord});
                lookBottomRight = false;
            } else {
                lookBottomRight = false;
            }
        } else {
            lookBottomRight = false;
        }
        // bottom left
        if (lookBottomLeft && position.row + i <= 7 && position.col - i >= 0) {
            Position coord = {position.row + i, position.col - i};
            auto [piece, pieceColour] = board.getPiece(coord);
            if (pieceColour == 0) {
                legalMoves.push_back({position, coord});
            } else if (pieceColour != colour) {
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

moveList Queen::getMoves(const Board& board) const {
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
        if (lookTop && position.row - i >= 0) {
            Position coord = {position.row - i, position.col};
            auto [piece, pieceColour] = board.getPiece(coord);
            if (pieceColour == 0) {
                legalMoves.push_back({position, coord});
            } else if (pieceColour != colour) {
                legalMoves.push_back({position, coord});
                lookTop = false;
            } else {
                lookTop = false;
            }
        } else {
            lookTop = false;
        }
        // left
        if (lookLeft && position.col - i >= 0) {
            Position coord = {position.row, position.col - i};
            auto [piece, pieceColour] = board.getPiece(coord);
            if (pieceColour == 0) {
                legalMoves.push_back({position, coord});
            } else if (pieceColour != colour) {
                legalMoves.push_back({position, coord});
                lookLeft = false;
            } else {
                lookLeft = false;
            }
        } else {
            lookLeft = false;
        }
        // right
        if (lookRight && position.col + i <= 7) {
            Position coord = {position.row, position.col + i};
            auto [piece, pieceColour] = board.getPiece(coord);
            if (pieceColour == 0) {
                legalMoves.push_back({position, coord});
            } else if (pieceColour != colour) {
                legalMoves.push_back({position, coord});
                lookRight = false;
            } else {
                lookRight = false;
            }
        } else {
            lookRight = false;
        }
        // bottom
        if (lookBottom && position.row + i <= 7) {
            Position coord = {position.row + i, position.col};
            auto [piece, pieceColour] = board.getPiece(coord);
            if (pieceColour == 0) {
                legalMoves.push_back({position, coord});
            } else if (pieceColour != colour) {
                legalMoves.push_back({position, coord});
                lookBottom = false;
            } else {
                lookBottom = false;
            }
        } else {
            lookBottom = false;
        }

        // top right
        if (lookTopRight && position.row - i >= 0 && position.col + i <= 7) {
            Position coord = {position.row - i, position.col + i};
            auto [piece, pieceColour] = board.getPiece(coord);
            if (pieceColour == 0) {
                legalMoves.push_back({position, coord});
            } else if (pieceColour != colour) {
                legalMoves.push_back({position, coord});
                lookTopRight = false;
            } else {
                lookTopRight = false;
            }
        } else {
            lookTopRight = false;
        }
        // top left
        if (lookTopLeft && position.col - i >= 0 && position.row - i >= 0) {
            Position coord = {position.row - i, position.col - i};
            auto [piece, pieceColour] = board.getPiece(coord);
            if (pieceColour == 0) {
                legalMoves.push_back({position, coord});
            } else if (pieceColour != colour) {
                legalMoves.push_back({position, coord});
                lookTopLeft = false;
            } else {
                lookTopLeft = false;
            }
        } else {
            lookTopLeft = false;
        }
        // bottom right
        if (lookBottomRight && position.col + i <= 7 && position.row + i <= 7) {
            Position coord = {position.row + i, position.col + i};
            auto [piece, pieceColour] = board.getPiece(coord);
            if (pieceColour == 0) {
                legalMoves.push_back({position, coord});
            } else if (pieceColour != colour) {
                legalMoves.push_back({position, coord});
                lookBottomRight = false;
            } else {
                lookBottomRight = false;
            }
        } else {
            lookBottomRight = false;
        }
        // bottom left
        if (lookBottomLeft && position.row + i <= 7 && position.col - i >= 0) {
            Position coord = {position.row + i, position.col - i};
            auto [piece, pieceColour] = board.getPiece(coord);
            if (pieceColour == 0) {
                legalMoves.push_back({position, coord});
            } else if (pieceColour != colour) {
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

moveList Knight::getMoves(const Board& board) const {
    // returns [from, to] coordinates defining the new move.
    // check if move leads to king being in check.
    moveList legalMoves;
    Position topRight = Position{position.row - 2, position.col + 1};
    Position topLeft = {position.row - 2, position.col - 1};
    Position rightTop = {position.row - 1, position.col + 2};
    Position rightBottom = {position.row + 1, position.col + 2};
    Position bottomRight = {position.row + 2, position.col + 1};
    Position bottomLeft = {position.row + 2, position.col + 1};
    Position leftTop = {position.row + 1, position.col - 2};
    Position leftBottom = {position.row - 1, position.col - 2};
    std::vector<Position> allMoves = {
        topRight, topLeft, rightTop, rightBottom, bottomRight, bottomLeft, leftTop, leftBottom
    };

    for (Position move : allMoves) {
        if (move.row >= 0 && move.row <= 7 && move.col >= 0 && move.col <= 7) {
            auto [piece, pieceColour] = board.getPiece(move);
            if (piece == 0) {
                legalMoves.push_back({position, move});
            } else if (pieceColour != colour) {
                legalMoves.push_back({position, move});
            }
        }
    }
    
    return legalMoves;
};

moveList King::getMoves(const Board& board) const {
    // returns [from, to] coordinates defining the new move.
    // check if move leads to king being in check.
    moveList legalMoves;
    Position top = {position.row - 1, position.col};
    Position right = {position.row, position.col + 1};
    Position left = {position.row, position.col - 1};
    Position bottom = {position.row + 1, position.col};
    Position topRight = {position.row - 1, position.col + 1};
    Position topLeft = {position.row - 1, position.col - 1};
    Position bottomRight = {position.row + 1, position.col + 1};
    Position bottomLeft = {position.row + 1, position.col + 1};
    std::vector<Position> allMoves = {
        top, right, left, bottom, topRight, topLeft, bottomRight, bottomLeft
    };

    for (Position move : allMoves) {
        if (move.row >= 0 && move.row <= 7 && move.col >= 0 && move.col <= 7) {
            auto [piece, pieceColour] = board.getPiece(move);
            if (pieceColour == 0) {
                legalMoves.push_back({position, move});
            } else if (pieceColour != colour) {
                legalMoves.push_back({position, move});
            }
        }
    }
    
    return legalMoves;
};