#include <iostream>
#include "./Board/Board.h"

using namespace std;

int main() {

    Board *board = Board::GetBoardPointer();
    board->initialize();


    while (board->checkWinCondition() != true) {

        cout << "####################################################################" << endl;
        cout << endl;
        cout << "Welcome to checkers!" << endl;
        cout << "Instructions: enter the coordinates of the selected checker," << endl;
        cout << "then the coordinates of the cell where you want to go." << endl;
        cout << "Example command: b3 c4" << endl;
        cout << endl;
        cout << "I wish you an enjoyable hunger games!" << endl;
        cout << "####################################################################" << endl;

        cout << "Score for white: " << 12 - board->getBlackCounter() << endl;
        cout << "Score for black: " << 12 - board->getWhiteCounter() << endl << endl;

        board->printBoard();
        int oldY, newY;
        char oldX, newX;

        cout << endl;
        if (board->getPlayerTurn() == -1) { cout << endl << "Turn: WHITE" << endl; }
        else { cout << endl << "Turn: BLACK" << endl; }


        cout << "Pick your piece (number letter): " << endl;
        cin >> oldY;
        cin >> oldX;

        cout << "Pick your move (number letter): " << endl;
        cin >> newY;
        cin >> newX;

        board->tryMove(oldY, oldX, newY, newX);
    }
    return 0;
}
