/*
 * Zachary Thomas
 * 9/12/2017
 *
 * Holds the board logic for Reversi.
 */
#include <string>
#include "Board.h"
#include <iostream>

/**
 * Constructor used to copy a board.
 *
 * @param toBeCopied board to be copied
 */
Board::Board(Board *toBeCopied) {

    // Sets the count for each player's pieces
    player1Pieces = (*toBeCopied).playerPieces(1);
    player2Pieces = (*toBeCopied).playerPieces(2);

    size = 8;

    // Creates the board
    boardState = new int *[size];
    for (int row = 0; row < size; row++) {
        boardState[row] = new int[size];
    }

    // Copies the board
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            boardState[row][col] = (*toBeCopied).boardState[row][col];
        }
    }
}

/**
 * Constructor for a new game board.
 */
Board::Board() {
    // Each player starts out with two pieces
    player1Pieces = 2;
    player2Pieces = 2;

    size = 8;

    // Creates the board
    boardState = new int *[size];
    for (int row = 0; row < size; row++) {
        boardState[row] = new int[size];
    }

    // Clears off the board
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            boardState[row][col] = 0;
        }
    }

    // Places the first pieces
    boardState[3][3] = 1;
    boardState[3][4] = 2;
    boardState[4][3] = 2;
    boardState[4][4] = 1;

}

/**
 * Displays the current state of the board.
 */
void Board::printBoard() {

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            std::cout << boardState[row][col] << " ";
        }
        std::cout << std::endl;
    }
}


/**
 * Checks to see if he move is valid for the player.
 *
 * @param player The player making the move
 * @param xPos The column of the move
 * @param yPos The row of the move
 * @return
 */
bool Board::isMoveValid(int player, int xPos, int yPos) {

    // If the there is another piece in this position not valid
    if (boardState[yPos][xPos] != 0) {
        return false;
    }

    return checkColors(player, xPos, yPos);
}

/**
 * Checks off in all directions to see if this move is valid. The move is valid if there is at least one opponent piece
 * between one of the player's pieces and the one that we are trying to place. All the checker functions have a boolean
 * to tell it whether to change the pieces or not. The function will first be called with this variable false, but if
 * the move is valid it will be called agian with true passed to it.
 * @param player
 * @param xPos
 * @param yPos
 * @return
 */
bool Board::checkColors(int player, int xPos, int yPos) {
    bool validMove = false;
    if (checkUpperLeftDiagonal(player, xPos, yPos, false)) {
        checkUpperLeftDiagonal(player, xPos, yPos, true);
        validMove = true;
    }

    if (checkUp(player, xPos, yPos, false)) {
        checkUp(player, xPos, yPos, true);
        validMove = true;
    }

    if (checkUpperRightDiagonal(player, xPos, yPos, false)) {
        checkUpperRightDiagonal(player, xPos, yPos, true);
        validMove = true;
    }

    if (checkRight(player, xPos, yPos, false)) {
        checkRight(player, xPos, yPos, true);
        validMove = true;
    }

    if (checkLowerRightDiagonal(player, xPos, yPos, false)) {
        checkLowerRightDiagonal(player, xPos, yPos, true);
        validMove = true;
    }

    if (checkDown(player, xPos, yPos, false)) {
        checkDown(player, xPos, yPos, true);
        validMove = true;
    }

    if (checkLowerLeftDiagonal(player, xPos, yPos, false)) {
        checkLowerLeftDiagonal(player, xPos, yPos, true);
        validMove = true;
    }

    if (checkLeft(player, xPos, yPos, false)) {
        checkLeft(player, xPos, yPos, true);
        validMove = true;
    }


    // Place the pievce and add it to the counts
    if (validMove) {
        boardState[yPos][xPos] = player;
        if (player == 1)  player1Pieces++;
        else              player2Pieces++;
    }

    return validMove;
}

/**
 * Checks upper left diagonal off piece being placed.
 *
 * @param player Player making the move
 * @param xPos Column of the move
 * @param yPos Row of the move
 * @param switchColor Tells it to switch the color or not
 *
 * @return true if able to place here
 */
bool Board::checkUpperLeftDiagonal(int player, int xPos, int yPos, bool switchColor) {
    bool foundOtherColor = false;
    if (boardState[yPos][xPos] != 0) return false;
    for (int row = yPos - 1, col = xPos - 1; row > -1 && col > -1; row--, col--) {
        switch (checker(player, row, col, switchColor, &foundOtherColor)) {
            case 0:
                return false;
            case 1:
                return true;
        }

    }
    return false;
}

/**
 * Checks upper right diagonal off piece being placed.
 *
 * @param player Player making the move
 * @param xPos Column of the move
 * @param yPos Row of the move
 * @param switchColor Tells it to switch the color or not
 *
 * @return true if able to place here
 */
bool Board::checkUpperRightDiagonal(int player, int xPos, int yPos, bool switchColor) {
    bool foundOtherColor = false;
    if (boardState[yPos][xPos] != 0) return false;
    for (int row = yPos - 1, col = xPos + 1; row > -1 && col < size; row--, col++) {
        switch (checker(player, row, col, switchColor, &foundOtherColor)) {
            case 0:
                return false;
            case 1:
                return true;
        }
    }
    return false;
}

/**
 * Checks lower left diagonal off piece being placed.
 *
 * @param player Player making the move
 * @param xPos Column of the move
 * @param yPos Row of the move
 * @param switchColor Tells it to switch the color or not
 *
 * @return true if able to place here
 */
bool Board::checkLowerLeftDiagonal(int player, int xPos, int yPos, bool switchColor) {
    bool foundOtherColor = false;
    if (boardState[yPos][xPos] != 0) return false;
    for (int row = yPos + 1, col = xPos - 1; row < size && col > -1; row++, col--) {
        switch (checker(player, row, col, switchColor, &foundOtherColor)) {
            case 0:
                return false;
            case 1:
                return true;
        }
    }
    return false;
}

/**
 * Checks lower right diagonal off piece being placed.
 *
 * @param player Player making the move
 * @param xPos Column of the move
 * @param yPos Row of the move
 * @param switchColor Tells it to switch the color or not
 *
 * @return true if able to place here
 */
bool Board::checkLowerRightDiagonal(int player, int xPos, int yPos, bool switchColor) {
    bool foundOtherColor = false;
    if (boardState[yPos][xPos] != 0) return false;
    for (int row = yPos + 1, col = xPos + 1; row < size && col < size; row++, col++) {
        switch (checker(player, row, col, switchColor, &foundOtherColor)) {
            case 0:
                return false;
            case 1:
                return true;
        }
    }
    return false;
}

/**
 * Checks up off piece being placed.
 *
 * @param player Player making the move
 * @param xPos Column of the move
 * @param yPos Row of the move
 * @param switchColor Tells it to switch the color or not
 *
 * @return true if able to place here
 */
bool Board::checkUp(int player, int xPos, int yPos, bool switchColor) {
    bool foundOtherColor = false;
    if (boardState[yPos][xPos] != 0) return false;
    for (int row = yPos - 1; row > -1; row--) {
        switch (checker(player, row, xPos, switchColor, &foundOtherColor)) {
            case 0:
                return false;
            case 1:
                return true;
        }
    }
    return false;
}

/**
 * Checks right off piece being placed.
 *
 * @param player Player making the move
 * @param xPos Column of the move
 * @param yPos Row of the move
 * @param switchColor Tells it to switch the color or not
 *
 * @return true if able to place here
 */
bool Board::checkRight(int player, int xPos, int yPos, bool switchColor) {
    bool foundOtherColor = false;
    if (boardState[yPos][xPos] != 0) return false;
    for (int col = xPos + 1; col < size; col++) {
        switch (checker(player, yPos, col, switchColor, &foundOtherColor)) {
            case 0:
                return false;
            case 1:
                return true;
        }
    }
    return false;
}

/**
 * Checks down off piece being placed.
 *
 * @param player Player making the move
 * @param xPos Column of the move
 * @param yPos Row of the move
 * @param switchColor Tells it to switch the color or not
 *
 * @return true if able to place here
 */
bool Board::checkDown(int player, int xPos, int yPos, bool switchColor) {
    bool foundOtherColor = false;
    if (boardState[yPos][xPos] != 0) return false;
    for (int row = yPos + 1; row < size; row++) {
        switch (checker(player, row, xPos, switchColor, &foundOtherColor)) {
            case 0:
                return false;
            case 1:
                return true;
        }
    }
    return false;
}

/**
 * Checks left off piece being placed.
 *
 * @param player Player making the move
 * @param xPos Column of the move
 * @param yPos Row of the move
 * @param switchColor Tells it to switch the color or not
 *
 * @return true if able to place here
 */
bool Board::checkLeft(int player, int xPos, int yPos, bool switchColor) {
    bool foundOtherColor = false;
    if (boardState[yPos][xPos] != 0) return false;
    for (int col = xPos - 1; col > -1; col--) {
        switch (checker(player, yPos, col, switchColor, &foundOtherColor)) {
            case 0:
                return false;
            case 1:
                return true;
        }
    }
    return false;
}

int Board::checker(int player, int row, int col, bool switchColor, bool *seen) {
    if (boardState[row][col] == 0) return 0;
    // If the first piece found is same color not valid move
    if (boardState[row][col] == player && !(*seen)) return 0;
        // Opponent piece between this one and the one to be placed the move is valid
    else if (boardState[row][col] == player && (*seen)) return 1;
        // This piece belongs to the opponent
    else {
        // Mark that we have seen an opponents piece
        *seen = true;
       // If the boolean tells us to switch the color
        if (switchColor) {
            // Change the piece
            boardState[row][col] = player;
            // Change the count on the number of pieces
            if (player == 1) {
                player2Pieces--;
                player1Pieces++;
            } else {
                player1Pieces--;
                player2Pieces++;
            }
        }
    }
    return 3;
}

/**
 * A pair containing the score of both players
 *
 * @return both players scores
 */
std::pair<int, int> Board::score() {
    return std::pair<int, int>(player1Pieces,player2Pieces);
}

/**
 * Returns the number of pieces that the input player has.
 *
 * @param player The player in question
 *
 * @return The number of pieces that player has
 */
int Board::playerPieces(int player) {
    if (player == 1)
        return player1Pieces;
    else
        return player2Pieces;
}













