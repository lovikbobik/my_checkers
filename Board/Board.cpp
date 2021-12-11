#include "Board.h"
#include "Normal.h"
#include "Queen.h"
#include <iostream>

const char row[] = "ABCDEFGH";

Board *Board::boardPointer = nullptr;

void Board::initialize() {

    for (int y = 0; y < 8; y++) {
        std::vector<Square> v1;
        for (int x = 0; x < 8; x++) {
            v1.push_back(Square());
        }
        boardFields.push_back(v1);
    }

    this->whiteCounter = 0;
    this->blackCounter = 0;

    for (int y = 5; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if ((y + x) % 2) {
                this->boardFields[y][x].setPiece(new Normal(y, x, Color(-1)));
                this->whiteCounter++;
            }
        }
    }

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 8; x++) {
            if ((y + x) % 2) {
                this->boardFields[y][x].setPiece(new Normal(y, x, Color(1)));
                this->blackCounter++;
            }
        }
    }

    playerTurn = -1;
}


void Board::printBoard() const {
    for (int y = 0; y < 8; y++) {
        std::cout << y + 1 << " ";
        for (int x = 0; x < 8; x++) {
            if (boardFields[y][x].hasPiece())
                boardFields[y][x].getPiece()->print();
            else if (!boardFields[y][x].hasPiece() && (x + y) % 2)
                std::cout << ". ";
            else
                std::cout << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << "  ";

    for (int x = 0; x < 8; x++) {
        std::cout << row[x] << " ";
    }
}


void Board::tryMove(int old_number, char old_letter, int new_number, char new_letter) {
    int oldY = int(old_number) - 1, oldX = 0;
    int newY = int(new_number) - 1, newX = 0;
    int j = 0;
    for (char i: row) {
        if (i == old_letter)
            oldX = j;
        ++j;
    }
    j = 0;
    for (char i: row) {
        if (i == new_letter)
            newX = j;
        ++j;
    }

    MoveStatus turn = NONE;

    if (boardFields[oldY][oldX].hasPiece() && !boardFields[newY][newX].hasPiece() &&
        playerTurn == boardFields[oldY][oldX].getPiece()->getColor()) {
        turn = boardFields[oldY][oldX].getPiece()->move(boardFields, newY, newX);
        if (turn.getType() != NONE) {
            if (playerTurn == 1)
                playerTurn = -1;
            else
                playerTurn = 1;
        } else {
            std::cout << "Wrong position!" << std::endl;
        }
    }


    switch (turn.getType()) {

        case NONE:
            break;
        case NORMAL: {
            Piece *piece = boardFields[oldY][oldX].getPiece();
            piece->setY(newY);
            piece->setX(newX);

            if ((piece->getColor() == 1 && newY == 7) || (piece->getColor() == -1 && newY == 0)) {
                int color = piece->getColor();
                boardFields[newY][newX].setPiece(new Queen(newY, newX, Color(color)));
            } else
                boardFields[newY][newX].setPiece(piece);

            boardFields[oldY][oldX].setPiece(nullptr);
            break;
        }

        case KILL:
            Piece *piece = boardFields[oldY][oldX].getPiece();
            piece->setY(newY);
            piece->setX(newX);
            if ((piece->getColor() == 1 && newY == 7) || (piece->getColor() == -1 && newY == 0)) {
                int color = piece->getColor();
                boardFields[newY][newX].setPiece(new Queen(newY, newX, Color(color)));
            } else
                boardFields[newY][newX].setPiece(piece);
            boardFields[oldY][oldX].setPiece(nullptr);

            Piece *otherPiece = turn.getPiece();
            boardFields[otherPiece->get_Y()][otherPiece->get_X()].setPiece(nullptr);

            if (piece->getColor() == 1)
                this->whiteCounter--;
            else
                this->blackCounter--;

            break;
    }
}

bool Board::checkWinCondition() const {

    if (blackCounter == 0) {
        std::cout << "White player wins" << std::endl;
        return true;
    } else if (whiteCounter == 0) {
        std::cout << "Black player wins" << std::endl;
        return true;
    } else
        return false;

}

Board *Board::GetBoardPointer() {
    if (boardPointer == nullptr)
        boardPointer = new Board();

    return boardPointer;
}

int Board::getBlackCounter() const {
    return blackCounter;
}

int Board::getWhiteCounter() const {
    return whiteCounter;
}

int Board::getPlayerTurn() const {
    return playerTurn;
}