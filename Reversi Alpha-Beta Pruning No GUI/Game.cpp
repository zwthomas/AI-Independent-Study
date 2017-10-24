/*
 * Zachary Thomas
 * 9/19/2017
 *
 * Holds the game logic for Reversi.
 */

#include "Game.h"
#include <iostream>

using namespace std;

/**
 * Constructor for the game. Creates the game board. Marks the game as running. Sets the starting player. Initializes
 * player plys.
 *
 * @param ply1 The number of moves ahead player 1 will look
 * @param ply2 The number of moves ahead player 2 will look
 */
Game::Game(int ply1, int ply2) {
    board = new Board();
    gameover = false;
    playersMove = 1;
    player1Ply = ply1;
    player2Ply = ply2;
}

/**
 * Runs full game. The moves are generated using alpha-beta pruning. The simple heuristic used is number of pieces. Runs
 * until both players do not have a move.
 */
void Game::run() {
    bool maxPlayer = true, movesLeftPlayer1, movesLeftPlayer2;

    // Game loop
    while (!gameover) {
        movesLeftPlayer1 = true;
        movesLeftPlayer2 = true;

        // If player 1 has a move make it
        if (moveRemaining(board, 1)) {
            alphabeta(board, player1Ply, -70, 70, maxPlayer, 1, player1Ply);
        } else {
            movesLeftPlayer1 = false;
        }

        // If player 2 has a move make it
        if (moveRemaining(board, 2)) {
            alphabeta(board, player2Ply, -70, 70, !maxPlayer, 2, player2Ply);
        } else {
            movesLeftPlayer2 = false;
        }

        // If both players couldn't make move game is over
        if (!movesLeftPlayer1 && !movesLeftPlayer2) {
            gameover = true;
        }

    }

    // Display results
    std::pair<int, int> score = (*board).score();
    if (score.first > score.second)
        std::cout << "Player 1 won" << std::endl;
    else
        std::cout << "Player 2 won" << std::endl;

    std::cout << "Score: " << std::endl;
    std::cout << "Player 1: " << score.first << std::endl;
    std::cout << "Player 2: " << score.second << std::endl;
    (*board).printBoard();
}

/**
 * For testing purposes. Allows moves to manually be entered.
 */
void Game::readInMove() {
    validMove = false;
    int inputRow;
    int inputCol;

    // Reads in moves until a valid move is entered
    while (!validMove) {
        // Prompts and read input
        std::cout << "Player " << playersMove << " enter the row and column to place your piece (both 0-7):"
                  << std::endl;
        std::cin >> inputRow >> inputCol;

        // Checks if valid
        if (inputCol < 8 && inputRow > -1 && inputRow < 8 && inputCol > -1 &&
            (*board).isMoveValid(playersMove, inputCol, inputRow)) {
            validMove = true;
        } else {
            std::cout << "Input values are not a valid move." << std::endl;
        }
    }
    std::cout << "Point accepted" << std::endl;
}

/**
 * Iterates over the board checking each position to see if there a piece belonging to player can be placed there.
 *
 * @param state The game board
 * @param player The player whose moves we are checking for
 * @return true if player has a least 1 move
 */
bool Game::moveRemaining(Board *state, int player) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (checkPosition(state, player, col, row, false)) return true;
        }
    }
    return false;
}

/**
 * Checks all positions off current position to see if the move is valid.
 *
 * @param b The game board
 * @param player The player whose turn it is
 * @param xPos The column of the move
 * @param yPos The row of the move
 * @param makeMove Boolean to tell if the piece should be placed.
 * @return true if piece can be placed here
 */
bool Game::checkPosition(Board *b, int player, int xPos, int yPos, bool makeMove) {
    if ((*b).checkUpperLeftDiagonal(player, xPos, yPos, makeMove)) {
        return true;
    }

    if ((*b).checkUp(player, xPos, yPos, makeMove)) {
        return true;
    }

    if ((*b).checkUpperRightDiagonal(player, xPos, yPos, makeMove)) {
        return true;
    }

    if ((*b).checkRight(player, xPos, yPos, makeMove)) {
        return true;
    }

    if ((*b).checkLowerRightDiagonal(player, xPos, yPos, makeMove)) {
        return true;
    }

    if ((*b).checkDown(player, xPos, yPos, makeMove)) {
        return true;
    }

    if ((*b).checkLowerLeftDiagonal(player, xPos, yPos, makeMove)) {
        return true;
    }

    if ((*b).checkLeft(player, xPos, yPos, makeMove)) {
        return true;
    }

    return false;
}

/**
 * Performs the alpha-beta pruning to find the best move.
 *
 * @param state The game board
 * @param depth Recursion depth
 * @param alpha Alpha value
 * @param beta Beta value
 * @param maximizingPlayer Tells us if me are trying to maximize of minimize
 * @param player The player whose turn it is
 * @param startDepth Saved start depth because this is a count down
 * @return heuristic from the search
 */
int Game::alphabeta(Board *state, int depth, int alpha, int beta, bool maximizingPlayer, int player, int startDepth) {
    int bRow, bCol;
    int otherPlayer;

    // Determines other player for recursive call
    if (player == 1) {
        otherPlayer = 2;
    } else {
        otherPlayer = 1;
    }

    // Base case
    if (depth == 0 || !moveRemaining(state, player)) {
        if (maximizingPlayer) {
            return (*state).playerPieces(player);
        } else {
            return -1 * (*state).playerPieces(player);
        }
    }

    // Init v
    int v;
    if (maximizingPlayer)       v = -70;
    else                        v = 70;

    // Go through all the positions on the board
    for (int row = 0; row < (*state).size; row++) {
        for (int col = 0; col < (*state).size; col++) {

            // If the input player can make a move at this position
            if (checkPosition(state, player, col, row, false)) {

                Board *copy = new Board(state); // Copy the board
                (*copy).isMoveValid(player, col, row); // Have them make move on copy

                if (maximizingPlayer) {

                    // Recursive search
                    v = std::max(v, alphabeta(copy, depth - 1, alpha, beta, false, otherPlayer, startDepth));

                    // Prune
                    if (v >= beta)      return v;

                    // Alpha needs updated
                    if (alpha < v) {

                        // If we are in the base case this is the new move we are going to make
                        if (depth == startDepth) {
                            bRow = row;
                            bCol = col;
                        } else {
                            delete copy; // Delete the no longer needed board
                        }
                        alpha = v; // Update alpha
                    }

                } else {

                    // Recursive search
                    v = std::min(v, alphabeta(copy, depth - 1, alpha, beta, true, otherPlayer, startDepth));

                    // Prune
                    if (v <= alpha)
                        return v;

                    // Beta needs updated
                    if (v < beta) {

                        // If we are at first turn in the search this is the move we are going to make
                        if (depth == startDepth) {
                            bRow = row;
                            bCol = col;
                        } else {
                            delete copy; // Delete no longer needed board
                        }
                        beta = v; // Update beta
                    }
                }

            }
        }
    }

    // Make the best move
    if (depth == startDepth) {
        (*board).isMoveValid(player, bCol, bRow);
    }
    return v;
}


