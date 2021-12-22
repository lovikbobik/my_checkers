#pragma once

#include <Piece.h>


class Checker : public Piece {
public:
    using Piece::Piece;

    ~Checker() override;

    MoveStatus move(std::vector<std::vector<Square>> tiles, int new_y, int new_x) override;

    void print() override;
};

