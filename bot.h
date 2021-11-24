#pragma once
int computer_move(char board[26][26], int board_size, int needed, int moves[2]);
int check_win_s(char gamee[26][26], int size);
int moves_left(char board[26][26], int focus[2], int needed, int size);
void get_focus(char board[26][26], int size, int needed, int focus[2]);
int minimax(char board[26][26], int depth, bool isMax, int size, int focus[2], int needed);
