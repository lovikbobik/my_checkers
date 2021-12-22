#include "Queen.h"
#include <iostream>


Queen::~Queen() = default;

void Queen::print() {
    if (this->getColor() == Color(-1))
        std::cout << "W ";
    else
        std::cout << "B ";
}

MoveStatus Queen::move(std::vector<std::vector<Square>> tiles, int newY, int newX) {

    if (tiles[newY][newX].hasPiece() || (newX + newY) % 2 == 0) {
        return {NONE};
    }

    int qy = this->getY();
    int qx = this->getX();
    bool isPieceOnWay = false;

    if (abs(newY - qy) == abs(newX - qx)) {
        Piece *piece = checkDiagonal(tiles, qy, qx, newY, newX);
        if (piece != nullptr && piece->getColor() != tiles[qy][qx].getPiece()->getColor()) {
            isPieceOnWay = true;
        }
        if (isPieceOnWay) {
            return {KILL, piece};
        }

        return {NORMAL};
    } else return {NONE};

}

Piece *Queen::checkDiagonal(std::vector<std::vector<Square>> tiles, int oldY, int oldX, int newY, int newX) {
    if (newX - oldX > 0 && newY - oldY < 0) {
        for (int y = oldY - 1, x = oldX + 1; y > newY && x < newX; x++, y--) {
            if (tiles[y][x].hasPiece()) {
                return tiles[y][x].getPiece();
            }
        }
    }
    if (newX - oldX < 0 && newY - oldY > 0) {
        for (int y = oldY + 1, x = oldX - 1; y < newY && x > newX; x--, y++) {
            if (tiles[y][x].hasPiece()) {
                return tiles[y][x].getPiece();
            }
        }
    }
    if (newX - oldX < 0 && newY - oldY < 0) {
        for (int y = oldY - 1, x = oldX - 1; y > newY && x > newX; x--, y--) {
            if (tiles[y][x].hasPiece()) {
                return tiles[y][x].getPiece();
            }
        }
    }
    if (newX - oldX > 0 && newY - oldY > 0) {
        for (int y = oldY + 1, x = oldX + 1; y < newY && x < newX; x++, y++) {
            if (tiles[y][x].hasPiece()) {
                return tiles[y][x].getPiece();
            }
        }
    }
    return nullptr;
}
