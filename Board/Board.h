#pragma once

#include <vector>
#include "Square.h"

class Board {
public:
    static Board *GetBoardPointer();

    ~Board() = default;

    void initialize();

    void printBoard() const;

    void tryMove(int, char, int, char);

    bool checkWinCondition() const;

    int getBlackCounter() const;

    int getWhiteCounter() const;

    int getPlayerTurn() const;

private:
    mutable std::vector<std::vector<Square>> boardFields;
    int blackCounter;
    int whiteCounter;
    int playerTurn;
    static Board *boardPointer;
};
