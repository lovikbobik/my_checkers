#pragma once

#include "Piece.h"

class Piece;

class Square {
public:
    Square();

    void setPiece(Piece *piece);

    Piece *const getPiece() const;

    bool hasPiece();
private:
    Piece *_piece;
};

