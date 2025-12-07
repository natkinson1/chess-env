#include <vector>
#include <string>
#include <unordered_map>
#include "board.cpp"

class Piece {
private:
public:
};

class Pawn : public Piece {
private:
    std::vector<int> position;
    int colour;
    int encoding = 1;
    bool taken = false;
    bool hasMoved = false;
    int direction = colour * -1;

public:
    std::vector<std::vector<std::vector<int>>> getMoves(const Board& board) {
        // returns [from, to] coordinates defining the new move.
        // check if move leads to king being in check.
        std::vector<std::vector<std::vector<int>>> legalMoves;

        if (!hasMoved) {
            const std::vector<int> forward = {position[0] + direction * 2, position[1]};
            const std::vector<int> forwardPiece = board.getPiece(forward);
            if (forwardPiece[1] == 0) {
                legalMoves.push_back({position, forward});
            };
        };
        // can move 1 forward
        const std::vector<int> forward = {position[0] + direction, position[1]};
        const std::vector<int> forwardPiece = board.getPiece(forward);
        if (forwardPiece[1] == 0) {
            legalMoves.push_back({position, forward});
        }
        // can take diagRight
        const std::vector<int> rightDiag = {position[0] - direction, position[1] + 1};
        if (rightDiag[0] > 0 && rightDiag[0] < 8 && rightDiag[1] < 8) {
            const std::vector<int> rightDiagPiece = board.getPiece(rightDiag);
            if (rightDiagPiece[1] == colour * -1) {
                legalMoves.push_back({position, rightDiag});
            };
        };
        
        // can take diagLeft
        const std::vector<int> leftDiag = {position[0] - direction, position[1] - 1};
        if (leftDiag[0] > 0 && leftDiag[0] < 8 && leftDiag[1] > 0) {
            const std::vector<int> leftDiagPiece = board.getPiece(leftDiag);
            if (leftDiagPiece[1] == colour * -1) {
                legalMoves.push_back({position, leftDiag});
            }
        }
        // en passen
        // if promotes
        return legalMoves;
    };
};

class Rook : public Piece {
private:
    std::vector<int> position;
    int colour;
    int encoding = 4;
    bool taken = false;
    bool hasMoved = false;
public:
    std::vector<std::vector<std::vector<int>>> getMoves(const Board& board) {
        std::vector<std::vector<std::vector<int>>> legalMoves;

        bool lookTop = true;
        bool lookLeft = true;
        bool lookRight = true;
        bool lookBottom = true;
        int i = 0;
        while (i <= 7) {
            // top
            if (lookTop && position[0] - i >= 0) {
                std::vector<int> coord = {position[0] - i, position[1]};
                std::vector<int> piece = board.getPiece(coord);
                if (piece[1] == 0) {
                    legalMoves.push_back({position, coord});
                } else if (piece[1] != colour) {
                    legalMoves.push_back({position, coord});
                    lookTop = false;
                } else {
                    lookTop = false;
                }
            } else {
                lookTop = false;
            }
            // left
            if (lookLeft && position[1] - i >= 0) {
                std::vector<int> coord = {position[0], position[1] - i};
                std::vector<int> piece = board.getPiece(coord);
                if (piece[1] == 0) {
                    legalMoves.push_back({position, coord});
                } else if (piece[1] != colour) {
                    legalMoves.push_back({position, coord});
                    lookLeft = false;
                } else {
                    lookLeft = false;
                }
            } else {
                lookLeft = false;
            }
            // right
            if (lookRight && position[1] + i <= 7) {
                std::vector<int> coord = {position[0], position[1] + i};
                std::vector<int> piece = board.getPiece(coord);
                if (piece[1] == 0) {
                    legalMoves.push_back({position, coord});
                } else if (piece[1] != colour) {
                    legalMoves.push_back({position, coord});
                    lookRight = false;
                } else {
                    lookRight = false;
                }
            } else {
                lookRight = false;
            }
            // bottom
            if (lookBottom && position[0] + i <= 7) {
                std::vector<int> coord = {position[0] + i, position[1]};
                std::vector<int> piece = board.getPiece(coord);
                if (piece[1] == 0) {
                    legalMoves.push_back({position, coord});
                } else if (piece[1] != colour) {
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
};

class Bishop : public Piece {
private:
    std::vector<int> position;
    int colour;
    int encoding = 2;
    bool taken = false;
public:
    std::vector<std::vector<std::vector<int>>> getMoves(const Board& board) {
        std::vector<std::vector<std::vector<int>>> legalMoves;

        bool lookTopRight = true;
        bool lookTopLeft = true;
        bool lookBottomRight = true;
        bool lookBottomLeft = true;
        int i = 0;
        while (i <= 7) {
            // top right
            if (lookTopRight && position[0] - i >= 0 && position[1] + i <= 7) {
                std::vector<int> coord = {position[0] - i, position[1] + i};
                std::vector<int> piece = board.getPiece(coord);
                if (piece[1] == 0) {
                    legalMoves.push_back({position, coord});
                } else if (piece[1] != colour) {
                    legalMoves.push_back({position, coord});
                    lookTopRight = false;
                } else {
                    lookTopRight = false;
                }
            } else {
                lookTopRight = false;
            }
            // top left
            if (lookTopLeft && position[1] - i >= 0 && position[0] - i >= 0) {
                std::vector<int> coord = {position[0] - i, position[1] - i};
                std::vector<int> piece = board.getPiece(coord);
                if (piece[1] == 0) {
                    legalMoves.push_back({position, coord});
                } else if (piece[1] != colour) {
                    legalMoves.push_back({position, coord});
                    lookTopLeft = false;
                } else {
                    lookTopLeft = false;
                }
            } else {
                lookTopLeft = false;
            }
            // bottom right
            if (lookBottomRight && position[1] + i <= 7 && position[0] + i <= 7) {
                std::vector<int> coord = {position[0] + i, position[1] + i};
                std::vector<int> piece = board.getPiece(coord);
                if (piece[1] == 0) {
                    legalMoves.push_back({position, coord});
                } else if (piece[1] != colour) {
                    legalMoves.push_back({position, coord});
                    lookBottomRight = false;
                } else {
                    lookBottomRight = false;
                }
            } else {
                lookBottomRight = false;
            }
            // bottom left
            if (lookBottomLeft && position[0] + i <= 7 && position[1] - i >= 0) {
                std::vector<int> coord = {position[0] + i, position[1] - i};
                std::vector<int> piece = board.getPiece(coord);
                if (piece[1] == 0) {
                    legalMoves.push_back({position, coord});
                } else if (piece[1] != colour) {
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
};

class Queen : public Piece {
private:
    std::vector<int> position;
    int colour;
    int encoding = 5;
    bool taken = false;
public:
    std::vector<std::vector<std::vector<int>>> getMoves(const Board& board) {
        std::vector<std::vector<std::vector<int>>> legalMoves;

        bool lookTop = true;
        bool lookLeft = true;
        bool lookRight = true;
        bool lookBottom = true;

        bool lookTopRight = true;
        bool lookTopLeft = true;
        bool lookBottomRight = true;
        bool lookBottomLeft = true;
        int i = 0;
        while (i <= 7) {
            // top
            if (lookTop && position[0] - i >= 0) {
                std::vector<int> coord = {position[0] - i, position[1]};
                std::vector<int> piece = board.getPiece(coord);
                if (piece[1] == 0) {
                    legalMoves.push_back({position, coord});
                } else if (piece[1] != colour) {
                    legalMoves.push_back({position, coord});
                    lookTop = false;
                } else {
                    lookTop = false;
                }
            } else {
                lookTop = false;
            }
            // left
            if (lookLeft && position[1] - i >= 0) {
                std::vector<int> coord = {position[0], position[1] - i};
                std::vector<int> piece = board.getPiece(coord);
                if (piece[1] == 0) {
                    legalMoves.push_back({position, coord});
                } else if (piece[1] != colour) {
                    legalMoves.push_back({position, coord});
                    lookLeft = false;
                } else {
                    lookLeft = false;
                }
            } else {
                lookLeft = false;
            }
            // right
            if (lookRight && position[1] + i <= 7) {
                std::vector<int> coord = {position[0], position[1] + i};
                std::vector<int> piece = board.getPiece(coord);
                if (piece[1] == 0) {
                    legalMoves.push_back({position, coord});
                } else if (piece[1] != colour) {
                    legalMoves.push_back({position, coord});
                    lookRight = false;
                } else {
                    lookRight = false;
                }
            } else {
                lookRight = false;
            }
            // bottom
            if (lookBottom && position[0] + i <= 7) {
                std::vector<int> coord = {position[0] + i, position[1]};
                std::vector<int> piece = board.getPiece(coord);
                if (piece[1] == 0) {
                    legalMoves.push_back({position, coord});
                } else if (piece[1] != colour) {
                    legalMoves.push_back({position, coord});
                    lookBottom = false;
                } else {
                    lookBottom = false;
                }
            } else {
                lookBottom = false;
            }

            // top right
            if (lookTopRight && position[0] - i >= 0 && position[1] + i <= 7) {
                std::vector<int> coord = {position[0] - i, position[1] + i};
                std::vector<int> piece = board.getPiece(coord);
                if (piece[1] == 0) {
                    legalMoves.push_back({position, coord});
                } else if (piece[1] != colour) {
                    legalMoves.push_back({position, coord});
                    lookTopRight = false;
                } else {
                    lookTopRight = false;
                }
            } else {
                lookTopRight = false;
            }
            // top left
            if (lookTopLeft && position[1] - i >= 0 && position[0] - i >= 0) {
                std::vector<int> coord = {position[0] - i, position[1] - i};
                std::vector<int> piece = board.getPiece(coord);
                if (piece[1] == 0) {
                    legalMoves.push_back({position, coord});
                } else if (piece[1] != colour) {
                    legalMoves.push_back({position, coord});
                    lookTopLeft = false;
                } else {
                    lookTopLeft = false;
                }
            } else {
                lookTopLeft = false;
            }
            // bottom right
            if (lookBottomRight && position[1] + i <= 7 && position[0] + i <= 7) {
                std::vector<int> coord = {position[0] + i, position[1] + i};
                std::vector<int> piece = board.getPiece(coord);
                if (piece[1] == 0) {
                    legalMoves.push_back({position, coord});
                } else if (piece[1] != colour) {
                    legalMoves.push_back({position, coord});
                    lookBottomRight = false;
                } else {
                    lookBottomRight = false;
                }
            } else {
                lookBottomRight = false;
            }
            // bottom left
            if (lookBottomLeft && position[0] + i <= 7 && position[1] - i >= 0) {
                std::vector<int> coord = {position[0] + i, position[1] - i};
                std::vector<int> piece = board.getPiece(coord);
                if (piece[1] == 0) {
                    legalMoves.push_back({position, coord});
                } else if (piece[1] != colour) {
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
};

class Knight : public Piece {
private:
    std::vector<int> position;
    int colour;
    int encoding = 1;
    bool taken = false;

public:
    std::vector<std::vector<std::vector<int>>> getMoves(const Board& board) {
        // returns [from, to] coordinates defining the new move.
        // check if move leads to king being in check.
        std::vector<std::vector<std::vector<int>>> legalMoves;
        std::vector<int> topRight = {position[0] - 2, position[1] + 1};
        std::vector<int> topLeft = {position[0] - 2, position[1] - 1};
        std::vector<int> rightTop = {position[0] - 1, position[1] + 2};
        std::vector<int> rightBottom = {position[0] + 1, position[1] + 2};
        std::vector<int> bottomRight = {position[0] + 2, position[1] + 1};
        std::vector<int> bottomLeft = {position[0] + 2, position[1] + 1};
        std::vector<int> leftTop = {position[0] + 1, position[1] - 2};
        std::vector<int> leftBottom = {position[0] - 1, position[1] - 2};
        std::vector<std::vector<int>> allMoves = {
            topRight, topLeft, rightTop, rightBottom, bottomRight, bottomLeft, leftTop, leftBottom
        };

        for (std::vector<int> move : allMoves) {
            if (move[0] >= 0 && move[0] <= 7 && move[1] >= 0 && move[1] <= 7) {
                std::vector<int> piece = board.getPiece(move);
                if (piece[1] == 0) {
                    legalMoves.push_back({position, move});
                } else if (piece[1] != colour) {
                    legalMoves.push_back({position, move});
                }
            }
        }
        
        return legalMoves;
    };
};

class King : public Piece {
private:
    std::vector<int> position;
    int colour;
    int encoding = 1;
    bool taken = false;

public:
    std::vector<std::vector<std::vector<int>>> getMoves(const Board& board) {
        // returns [from, to] coordinates defining the new move.
        // check if move leads to king being in check.
        std::vector<std::vector<std::vector<int>>> legalMoves;
        std::vector<int> top = {position[0] - 1, position[1]};
        std::vector<int> right = {position[0], position[1] + 1};
        std::vector<int> left = {position[0], position[1] - 1};
        std::vector<int> bottom = {position[0] + 1, position[1]};
        std::vector<int> topRight = {position[0] - 1, position[1] + 1};
        std::vector<int> topLeft = {position[0] - 1, position[1] - 1};
        std::vector<int> bottomRight = {position[0] + 1, position[1] + 1};
        std::vector<int> bottomLeft = {position[0] + 1, position[1] + 1};
        std::vector<std::vector<int>> allMoves = {
            top, right, left, bottom, topRight, topLeft, bottomRight, bottomLeft
        };

        for (std::vector<int> move : allMoves) {
            if (move[0] >= 0 && move[0] <= 7 && move[1] >= 0 && move[1] <= 7) {
                std::vector<int> piece = board.getPiece(move);
                if (piece[1] == 0) {
                    legalMoves.push_back({position, move});
                } else if (piece[1] != colour) {
                    legalMoves.push_back({position, move});
                }
            }
        }
        
        return legalMoves;
    };
};