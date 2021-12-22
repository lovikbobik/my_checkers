#include "Checker.h"
#include <iostream>
#include "MoveStatus.h"

Checker::~Checker() = default;

MoveStatus Checker::move(std::vector<std::vector<Square>> tiles, int new_y, int new_x) {
    if (tiles[new_y][new_x].hasPiece() || (new_y + new_x) % 2 == 0) {
        return {NONE};
    }

    int y0 = this->getY();
    int x0 = this->getX();

    if (new_y - y0 == (int) (this->getColor()) && abs(new_x - x0) == 1)
        return {NORMAL};
    else if (new_y - y0 == (int) (this->getColor()) * 2 && abs(new_x - x0) == 2) {
        int other_y = y0 + (new_y - y0) / 2;
        int other_x = x0 + (new_x - x0) / 2;
        if (tiles[other_y][other_x].hasPiece() && tiles[other_y][other_x].getPiece()->getColor() != this->getColor()) {
            return {KILL, tiles[other_y][other_x].getPiece()};
        }
    }
    return {NONE};
}

void Checker::print() {
    if (this->getColor() == Color(-1))
        std::cout << "w ";
    else
        std::cout << "b ";
}

