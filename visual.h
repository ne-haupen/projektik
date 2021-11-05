#pragma once

void menu();
void name_choice();
int player_choice();
int deck_size();
void top_players();
void play_screen(int first, char names[2][64]);
void end_screen();
void clear_screen();
void playerInput(int pIndex, int velkostPola);
int letterToIndex(char letter);
void clearBoard(int velkostPola);
void printBoard(int velkostPola)
