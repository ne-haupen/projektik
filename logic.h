#pragma once
int check_win(char gamee[26][26], int size);
int check_surrounding(int a, int b, char xo, char game[26][26]);
void save_data(char data[2][64]);
void get_names(char names[2][64]);
void hallff_add(char name[64], int pocet_tahu);

