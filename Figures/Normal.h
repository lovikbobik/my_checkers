#pragma once

#include <Piece.h>


class Normal : public Piece {
public:
    using Piece::Piece;

    ~Normal();

    MoveStatus move(std::vector<std::vector<Square>> array, int new_y, int new_x) override;

    void print() override;
};

