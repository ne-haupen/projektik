#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "visual.h"
#include "logic.h"
#define COMPUTER_AI 'X'
int minimax(int depth, int isMaximizing, char board[26][26], int board_size);

void computer_move(int board_size, char board[26][26])
{
    char board_number;
    int move_i, move_j;
    float bestScore = -INFINITY;
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            if (board[i][j] == '*')
            {
                board_number = board[i][j];
                board[i][j] = COMPUTER_AI;
                float score = minimax(0, 0, board, board_size);
                board[i][j] = board_number;
                if (score > bestScore)
                {
                    bestScore = score;
                    move_i = i;
                    move_j = j;
                }
            }
        }
    }
    board[move_i][move_j] = COMPUTER_AI;
    printBoard(board_size, -1);
}


int minimax(int depth, int isMaximizing, char board[26][26], int board_size)
{
    if (isMaximizing)
    {
        float bestScore = -INFINITY;
        for (int row = 0; row < board_size; row++)
        {
            for (int col = 0; col < board_size; col++)
            {
                if (board[row][col] == '*')
                {
                    char board_number = board[row][col];
                    board[row][col] = COMPUTER_AI;
                    float score = minimax(depth + 1, 0, board, board_size);
                    board[row][col] = board_number;
                    if (score > bestScore)
                    {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    }
    else
    {
        float bestScore = INFINITY;

        for (int row = 0; row < board_size; row++)
        {
            for (int col = 0; col < board_size; col++)
            {
                if (board[row][col] == '*')
                {
                    char board_number = board[row][col];
                    board[row][col] = 'X';
                    float score = minimax(depth + 1, 1, board, board_size);
                    board[row][col] = '*';
                    if (score < bestScore)
                    {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    }
}