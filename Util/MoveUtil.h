#pragma once

#include "../Pieces/Piece.h"

enum MoveType {
    NONE, NORMAL, KILL
};

class Piece;

class MoveUtil {
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

    MoveUtil(MoveType type);

    MoveUtil(MoveType type, Piece *piece);
};

