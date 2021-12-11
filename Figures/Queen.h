#pragma once

#include <Piece.h>
#include "MoveStatus.h"

class Queen : public Piece {
    using Piece::Piece;

public:
    ~Queen();
    MoveStatus move(std::vector<std::vector<Square>> array, int newY, int newX) override;
    void print() override;

private:
    static Piece *checkDiagonal(std::vector<std::vector<Square>> vector, int y0, int x0, int y, int x) ;
};

