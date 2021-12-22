#include <iostream>
#include "./Board/Board.h"

using namespace std;

int main() {

    auto *board = new Board();


    cout << "####################################################################" << endl
         << endl
         << "Welcome to checkers!" << endl
         << "Instructions: enter the coordinates of the selected checker," << endl
         << "then the coordinates of the cell where you want to go." << endl
         << "Example command: 6 A and then: 5 B" << endl
         << endl
         << "I wish you an enjoyable hunger games!" << endl
         << "####################################################################" << endl;

    while (!board->checkWinCondition()) {

        board->printBoard();
        int oldY, newY;
        char oldX, newX;

        cout << endl;
        if (board->getPlayerTurn() == -1) { cout << endl << "Turn: WHITE" << endl; }
        else { cout << endl << "Turn: BLACK" << endl; }


        cout << "Pick your _piece (number letter): " << endl;
        cin >> oldY;
        cin >> oldX;

        cout << "Pick your move (number letter): " << endl;
        cin >> newY;
        cin >> newX;

        board->tryMove(oldY, oldX, newY, newX);
    }
    return 0;
}
