#include "Queen.h"
#include <iostream>


Queen::~Queen() {
}

void Queen::print() {
    if (this->getColor() == Color(-1))
        std::cout << "W ";
    else
        std::cout << "B ";
}

MoveStatus Queen::move(std::vector<std::vector<Square>> boardFields, int newY, int newX) {

    if (boardFields[newY][newX].hasPiece() || (newX + newY) % 2 == 0) {
        return {NONE};
    }

    int qy = this->get_Y();
    int qx = this->get_X();
    bool isPieceOnWay = false;

    if (abs(newY - qy) == abs(newX - qx)) {
        Piece *piece = checkDiagonal(boardFields, qy, qx, newY, newX);
        if (piece != nullptr && piece->getColor() != boardFields[qy][qx].getPiece()->getColor()) {
            isPieceOnWay = true;
        }
        if (isPieceOnWay) {
            return {KILL, piece};
        }

        return {NORMAL};
    } else return {NONE};

}

Piece *Queen::checkDiagonal(std::vector<std::vector<Square>> boardFields, int oldY, int oldX, int newY, int newX) {
    if (newX - oldX > 0 && newY - oldY < 0) {
        for (int y = oldY - 1, x = oldX + 1; y > newY && x < newX; x++, y--) {
            if (boardFields[y][x].hasPiece()) {
                return boardFields[y][x].getPiece();
            }
        }
    }
    if (newX - oldX < 0 && newY - oldY > 0) {
        for (int y = oldY + 1, x = oldX - 1; y < newY && x > newX; x--, y++) {
            if (boardFields[y][x].hasPiece()) {
                return boardFields[y][x].getPiece();
            }
        }
    }
    if (newX - oldX < 0 && newY - oldY < 0) {
        for (int y = oldY - 1, x = oldX - 1; y > newY && x > newX; x--, y--) {
            if (boardFields[y][x].hasPiece()) {
                return boardFields[y][x].getPiece();
            }
        }
    }
    if (newX - oldX > 0 && newY - oldY > 0) {
        for (int y = oldY + 1, x = oldX + 1; y < newY && x < newX; x++, y++) {
            if (boardFields[y][x].hasPiece()) {
                return boardFields[y][x].getPiece();
            }
        }
    }
    return nullptr;
}
