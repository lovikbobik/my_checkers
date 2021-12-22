#pragma once

#include <vector>
#include "Square.h"

class Board {
public:

    ~Board() = default;

    Board();

    void printBoard() const;

    void tryMove(int, char, int, char);

    bool checkWinCondition() const;

    int getBlackCounter() const;

    int getWhiteCounter() const;

    int getPlayerTurn() const;

private:
    mutable std::vector<std::vector<Square>> _tiles;
    int _blackCounter;
    int _whiteCounter;
    int _playerTurn;
};
