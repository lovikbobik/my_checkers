#include "Board.h"
#include "Checker.h"
#include "Queen.h"
#include <iostream>

const char row[] = "ABCDEFGH";

void Board::printBoard() const {
    for (int y = 0; y < 8; y++) {
        std::cout << y + 1 << " ";
        for (int x = 0; x < 8; x++) {
            if (_tiles[y][x].hasPiece())
                _tiles[y][x].getPiece()->print();
            else if (!_tiles[y][x].hasPiece() && (x + y) % 2)
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

    MoveStatus moveStatus = NONE;

    if (_tiles[oldY][oldX].hasPiece() && !_tiles[newY][newX].hasPiece() &&
        _playerTurn == _tiles[oldY][oldX].getPiece()->getColor()) {
        moveStatus = _tiles[oldY][oldX].getPiece()->move(_tiles, newY, newX);
        if (moveStatus.getType() != NONE) {
            if (_playerTurn == 1)
                _playerTurn = -1;
            else
                _playerTurn = 1;
        } else {
            std::cout << "Wrong position!" << std::endl;
        }
    }


    switch (moveStatus.getType()) {

        case NONE:
            break;
        case NORMAL: {
            Piece *piece = _tiles[oldY][oldX].getPiece();
            piece->setY(newY);
            piece->setX(newX);

            if ((piece->getColor() == 1 && newY == 7) || (piece->getColor() == -1 && newY == 0)) {
                int color = piece->getColor();
                _tiles[newY][newX].setPiece(new Queen(newY, newX, Color(color)));
            } else
                _tiles[newY][newX].setPiece(piece);

            _tiles[oldY][oldX].setPiece(nullptr);
            break;
        }

        case KILL:
            Piece *piece = _tiles[oldY][oldX].getPiece();
            piece->setY(newY);
            piece->setX(newX);
            if ((piece->getColor() == 1 && newY == 7) || (piece->getColor() == -1 && newY == 0)) {
                int color = piece->getColor();
                _tiles[newY][newX].setPiece(new Queen(newY, newX, Color(color)));
            } else
                _tiles[newY][newX].setPiece(piece);
            _tiles[oldY][oldX].setPiece(nullptr);

            Piece *otherPiece = moveStatus.getPiece();
            _tiles[otherPiece->getY()][otherPiece->getX()].setPiece(nullptr);

            if (piece->getColor() == 1)
                this->_whiteCounter--;
            else
                this->_blackCounter--;

            break;
    }
}

bool Board::checkWinCondition() const {

    if (_blackCounter == 0) {
        std::cout << "White player wins" << std::endl;
        return true;
    } else if (_whiteCounter == 0) {
        std::cout << "Black player wins" << std::endl;
        return true;
    } else
        return false;

}

int Board::getBlackCounter() const {
    return _blackCounter;
}

int Board::getWhiteCounter() const {
    return _whiteCounter;
}

int Board::getPlayerTurn() const {
    return _playerTurn;
}

Board::Board() {

    for (int y = 0; y < 8; y++) {
        std::vector<Square> v1;
        v1.reserve(8);
        for (int x = 0; x < 8; x++) {
            v1.emplace_back();
        }
        _tiles.push_back(v1);
    }

    this->_whiteCounter = 0;
    this->_blackCounter = 0;

    for (int y = 5; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if ((y + x) % 2) {
                this->_tiles[y][x].setPiece(new Checker(y, x, Color(-1)));
                this->_whiteCounter++;
            }
        }
    }

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 8; x++) {
            if ((y + x) % 2) {
                this->_tiles[y][x].setPiece(new Checker(y, x, Color(1)));
                this->_blackCounter++;
            }
        }
    }

    _playerTurn = -1;
}


