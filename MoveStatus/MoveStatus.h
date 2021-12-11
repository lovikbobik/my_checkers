#pragma once

#include "../Pieces/Piece.h"

enum MoveType {
    NONE, NORMAL, KILL
};

class Piece;

class MoveStatus {
private:
    MoveType type;
public:
    MoveType getType() const {
        return type;
    }

private:
    Piece *piece{};
public:
    Piece *getPiece() const;

    MoveStatus(MoveType type);

    MoveStatus(MoveType type, Piece *piece);
};

