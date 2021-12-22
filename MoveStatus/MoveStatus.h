#pragma once

#include "../Pieces/Piece.h"

enum MoveType {
    NONE, NORMAL, KILL
};

class Piece;

class MoveStatus {
private:
    MoveType _type;
public:
    MoveType getType() const {
        return _type;
    }

private:
    Piece *_piece{};
public:
    Piece *getPiece() const;

    MoveStatus(MoveType type);

    MoveStatus(MoveType type, Piece *piece);
};

