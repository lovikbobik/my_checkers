#pragma once

#include <vector>
#include "Square.h"


enum Color {
    BLACK = 1, WHITE = -1
};

class Square;

class MoveUtil;

class Piece {
public:
    Piece(int y, int x, Color color);

    virtual ~Piece() {};

    int getColor() const;

    void setColor(Color color);

    void setX(int x);

    void setY(int y);

    int get_Y() const;

    int get_X() const;

    virtual MoveUtil move(std::vector<std::vector<Square>>, int, int) = 0;

    virtual void print() = 0;

private:
    int x;
    int y;
    Color color;
};

