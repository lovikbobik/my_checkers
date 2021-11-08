#include <iostream>
#include "game.h"

using namespace std;

int main() {
    Game *game = new Game();
    Motion *motion = new Motion();

    cout << "####################################################################" << endl;
    cout << endl;
    cout << "Welcome to checkers!" << endl;
    cout << "Instructions: enter the coordinates of the selected checker," << endl;
    cout << "then the coordinates of the cell where you want to go."<< endl;
    cout << "Example command: b3 c4" << endl;
    cout << endl;
    cout << "I wish you an enjoyable hunger games!"<< endl;
    cout << "####################################################################" << endl;

    while (true) {
        game->createListOfValidMotion();
        game->drawBoard();
        char player = game->get_player();
        int winner_code = game->get_winner();

        if (winner_code > 0) {
            cout << "\n-- player " << player << " wins\n" << endl;
            return winner_code;
        }

        cout << "\nplayer '" << player << "': ";
        cin.clear();
        cin.getline(motion->data(), Motion::data_len);
        cout << endl;

        if (game->isCheckMathingValidMotion(motion)) {
            motion->inputCoords();
            game->shiftPawn(motion);
            game->setNextPlayer();
        } else {
            cout << "-- invalid motion\n" << endl;
            game->setInvalidMotion();
        }
    }
}
