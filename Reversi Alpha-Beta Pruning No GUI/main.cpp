/*
 * Zachary Thomas
 * 10/24/17
 *
 * Runs the Reversi game with different ply for each player
 */
#include <iostream>
#include "Game.h"
using namespace std;


int main() {
    cout << "Running Reversi Test: " << endl;

    for (int p1 = 2; p1 <= 6; p1++) {
        for (int p2 = 2; p2 <= 6; p2++) {
            cout << "\n\nPlayer 1 ply: " << p1 << endl;
            cout << "Player 2 ply:" << p2 << endl << endl;
            Game g = Game(p1,p2);
            g.run();
        }
    }




    return 0;
}