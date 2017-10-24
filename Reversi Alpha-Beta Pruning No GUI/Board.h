//
// Created by Craven on 9/12/2017.
//

#ifndef REVERSI_BOARD_H
#define REVERSI_BOARD_H


class Board {
public:
//    bool checkPosition(Board *b, int player, int xPos, int yPos, bool makeMove);
//    bool moveRemaining(Board *state, int player);
    Board();
    Board(Board *toBeCopied);
//    Board(int i);
    bool isMoveValid(int player, int xPos, int yPos);
    bool checkUpperLeftDiagonal(int player, int xPos, int yPos, bool switchColor);
    bool checkUpperRightDiagonal(int player, int xPos, int yPos, bool switchColor);
    bool checkLowerLeftDiagonal(int player, int xPos, int yPos, bool switchColor);
    bool checkLowerRightDiagonal(int player, int xPos, int yPos, bool switchColor);
    bool checkUp(int player, int xPos, int yPos, bool switchColor);
    bool checkRight(int player, int xPos, int yPos, bool switchColor);
    bool checkDown(int player, int xPos, int yPos, bool switchColor);
    bool checkLeft(int player, int xPos, int yPos, bool switchColor);
    void printBoard();
    std::pair<int, int> score();
    int playerPieces(int player);
    int size;
    Board copyBoard();
    int **boardState;

protected:

private:


    int player1Pieces;
    int player2Pieces;

    bool checkColors(int player, int xPos, int yPos);
    int checker(int player, int row, int col, bool switchColor, bool *seen);

};


#endif //REVERSI_BOARD_H