#include "Piece.h"

Piece::Piece(int y, int x, Color color) {
    this->x = x;
    this->y = y;
    setColor(color);
}

int Piece::getColor() const {
    return this->color;
}

void Piece::setColor(Color color) {
    Piece::color = color;
}

int Piece::get_Y() const {
    return y;
}

int Piece::get_X() const {
    return x;
}

void Piece::setX(int x) {
    Piece::x = x;
}

void Piece::setY(int y) {
    Piece::y = y;
}


