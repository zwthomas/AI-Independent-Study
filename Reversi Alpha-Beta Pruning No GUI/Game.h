//
// Created by Craven on 9/19/2017.
//

#ifndef REVERSI_RUNGAME_H
#define REVERSI_RUNGAME_H


#include <utility>
#include "Board.h"


class Game {
public:
    Game(int ply1, int ply2);
    void run();
protected:

private:
    Board *board;
    int player1Ply;
    int player2Ply;
    bool gameover;

    int playersMove;
    bool validMove;
    bool moveRemaining(Board *state, int player);
    bool checkPosition(Board *b, int player, int xPos, int yPos, bool makeMove);
    void readInMove();
    int alphabeta(Board *state, int depth, int alpha, int beta, bool maximizingPlayer, int player, int startDepth);
};


#endif //REVERSI_RUNGAME_H
