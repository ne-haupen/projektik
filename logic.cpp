#include "logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void save_data(char data[2][64]) {
    FILE* fptr;

    fptr = fopen("players.txt", "w");

    if (fptr == NULL) {
        printf("error while opening file");
        exit(1);
    }

    for (int n = 0; n < 2; n++) {
           fprintf(fptr, "%s", data[n]);
    }
    fclose(fptr);
    return;
}

int compare(char ch1[64], char ch2[64]){
    for (int i = 0; ch1[i]!='\0'; i++) {
        ch1[i] = tolower(ch1[i]);
    }
    for (int i = 0; ch2[i]!='\0'; i++) {
        ch2[i] = tolower(ch2[i]);
    }
    return strcmp(ch2, ch1);
}
void hallff_add(char name[64], int pocet_tahu) {
    FILE* fp;
    char names[10][64];
    char moves[10];
    char wins[10];
    int lines = 0;
    fp = fopen("halloffame.txt", "r");
    for (int n = 0; (fgetc(fp)) != EOF; n++) {
        fscanf(fp, "%s %d %d", names[n], &moves[n], &wins[n]);
    }
    for (int n = 0; n < 10; n++) {
        if (strcmp(name, names[n]) == 0) {
            moves[n] += pocet_tahu;
            wins[n]++;
            return;
        }
    }
    fclose(fp);
    fp = fopen("halloffame.txt", "a");
    fprintf(fp, "%s %d %d\n", name, pocet_tahu, 1);
    fclose(fp);
    fp = fopen("halloffame.txt", "r");
    for (int n = 0; (fgetc(fp)) != EOF; n++) {
        fscanf(fp, "%s %d %d", names[n], &moves[n], &wins[n]);
    }

    char nswap[64];
    int wswap;
    int mswap;
    for (int c = 0; c < 9; c++)
    {
        for (int d = 0; ((d < 9 - c)&&(wins[c]>=1)); d++)
        {
            if (wins[d] < wins[d + 1])
            {
                wswap = wins[d];
                mswap = moves[d];
                strcpy(nswap, names[d]);
                wins[d] = wins[d + 1];
                wins[d + 1] = wswap;
                moves[d] = moves[d + 1];
                moves[d + 1] = mswap;
                strcpy(names[d + 1], names[d]);
                strcpy(names[d], nswap);
            }
        }
    }
    for (int n = 0; n < 10; n++) {
        printf("%s %d %d\n", names[n], moves[n], wins[n]);
    }

    int k=0;
    scanf_s(" %d", k);
    fclose(fp);
    fp = fopen("halloffame.txt", "w");
    for (int a = 0; fgetc(fp) != EOF; a++) {
        fprintf(fp, "%s %d %d", names[a], moves[a], wins[a]);
    }
    fclose(fp);
    return;

}


void get_names(char names[2][64]) {
    FILE* fp;
    char ch;
    fp = fopen("players.txt", "r");
    if (fp == NULL) {
        printf("error while opening file");
        exit(1);
    }
    for (int n = 0; n < 2; n++) {
        fscanf(fp, "%s", names[n]);
    }
    fclose(fp);

    return;
}

int check_win(char gamee[26][26], int size) {
    for (int n = 0; n < size; n++) {
        for (int k = 0; k < size; k++) {
            if (gamee[n][k] != '*') {
                if (check_surrounding(n, k, gamee[n][k], gamee) == 1) {
                    return 1;
                }
            }
        }
    }
    return 0;
}


int check_surrounding(int a, int b, char xo, char game[26][26]) {
    int hm[] = { -1, 0, 1 };
    int current = 1;
    int c, d;
    c = a;
    d = b;
    const int win_value = 3; //pocet znaku za sebou pro win fixxxxxxx
    for (int n = 0; n < 3; n++) {
        for (int k = 0; k < 3; k++) {
            current = 1;
            if ((game[a + hm[k]][b + hm[n]] == xo)) {
                if ((hm[k] == 0 && hm[n] == 0)) {
                    break;
                }
                //printf("dd cur %i k %i n %i\n", current, k, n);
                while (game[a + hm[k]][b + hm[n]] == xo) {
                    if ((0 <= a + hm[k] < 4) && (0 <= b + hm[n] < 4)) {
                        current++;
                    }
                    else {
                        break;
                    }
                    a = a + hm[k];
                    b = b + hm[n];
                }
                if (current == win_value) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
