#include "Square.h"


void Square::setPiece(Piece *piece) {
    Square::_piece = piece;
}

Piece *Square::getPiece() const {
    return _piece;
}

bool Square::hasPiece() {
    return this->_piece != nullptr;
}

Square::Square() {
    this->_piece = nullptr;
}
