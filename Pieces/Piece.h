#pragma once

#include <vector>
#include "Square.h"


enum Color {
    BLACK = 1, WHITE = -1
};

class Square;

class MoveStatus;

class Piece {
public:
    Piece(int y, int x, Color color);

    virtual ~Piece() = default;

    int getColor() const;

    void setColor(Color color);

    void setX(int x);

    void setY(int y);

    int getY() const;

    int getX() const;

    virtual MoveStatus move(std::vector<std::vector<Square>>, int, int) = 0;

    virtual void print() = 0;

private:
    int _x;
    int _y;
    Color _color;
};

