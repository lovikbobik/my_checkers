#include "MoveStatus.h"

MoveStatus::MoveStatus(MoveType type, Piece *piece) {
    this->type = type;
    this->piece = piece;
}

MoveStatus::MoveStatus(MoveType type) {
    this->type = type;
}

Piece* MoveStatus::getPiece() const {
    return this->piece;
}