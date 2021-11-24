#pragma once

void name_choice();
int player_choice();
void top_players();
int board_size();
void play_screen(char names[2][64]);
void playerInput(int pIndex, int velkostPola);
int letterToIndex(char letter);
void clearBoard(int velkostPola);
void printBoard(int velkostPola, int first);
void new_game(int mode);
void play_screen(int first, char names[2][64], int input);
void against_bot(int);