#pragma once
void computer_move(int board_size, char board[26][26]);
int minimax(int depth, int isMaximizing, char board[26][26], int board_size);