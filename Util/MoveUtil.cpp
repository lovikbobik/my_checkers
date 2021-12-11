#include "MoveUtil.h"

MoveUtil::MoveUtil(MoveType type, Piece *piece) {
    this->type = type;
    this->piece = piece;
}

MoveUtil::MoveUtil(MoveType type) {
    this->type = type;
}

Piece* MoveUtil::getPiece() const {
    return this->piece;
}