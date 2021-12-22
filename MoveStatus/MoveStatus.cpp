#include "MoveStatus.h"

MoveStatus::MoveStatus(MoveType type, Piece *piece) {
    this->_type = type;
    this->_piece = piece;
}

MoveStatus::MoveStatus(MoveType type) {
    this->_type = type;
}

Piece* MoveStatus::getPiece() const {
    return this->_piece;
}