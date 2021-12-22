#include "Piece.h"

Piece::Piece(int y, int x, Color color) {
    this->_x = x;
    this->_y = y;
    setColor(color);
}

int Piece::getColor() const {
    return this->_color;
}

void Piece::setColor(Color color) {
    Piece::_color = color;
}

int Piece::getY() const {
    return _y;
}

int Piece::getX() const {
    return _x;
}

void Piece::setX(int x) {
    Piece::_x = x;
}

void Piece::setY(int y) {
    Piece::_y = y;
}


