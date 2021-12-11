#include "Normal.h"
#include <iostream>
#include "MoveUtil.h"

Normal::~Normal() {

}

MoveUtil Normal::move(std::vector<std::vector<Square>> boardFields, int new_y, int new_x) {
    if (boardFields[new_y][new_x].hasPiece() || (new_y + new_x) % 2 == 0) {
        return {NONE};
    }

    int y_0 = this->get_Y();
    int x_0 = this->get_X();

    if (new_y - y_0 == (int) (this->getColor()) && abs(new_x - x_0) == 1)
        return {NORMAL};
    else if (new_y - y_0 == (int) (this->getColor()) * 2 && abs(new_x - x_0) == 2) {
        int other_y = y_0 + (new_y - y_0) / 2;
        int other_x = x_0 + (new_x - x_0) / 2;
        if (boardFields[other_y][other_x].hasPiece() && boardFields[other_y][other_x].getPiece()->getColor() != this->getColor()) {
            return {KILL, boardFields[other_y][other_x].getPiece()};
        }
    }
    return {NONE};
}

void Normal::print() {
    if (this->getColor() == Color(-1))
        std::cout << "w ";
    else
        std::cout << "b ";
}

