#include "bot.h"
#include "logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//ulozi zadane jmena do .txt souboru
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

//ulozi vyherce do hall of fame a seradi hrace podle poctu vyher
void hallff_add(char name[64], int pocet_tahu) {
    FILE* fp;
    char names[10][64];
    char moves[10];
    char wins[10];
    int lines = 0;
    if (fopen("halloffame.txt", "r") == NULL) {     //pokud soubor neexistuje vytvori se
        fp = fopen("halloffame.txt", "w");
        fclose(fp);
    }
    fp = fopen("halloffame.txt", "r+");
    for (int n = 0; (fgetc(fp)) != EOF; n++) {      //do promennych se ulozi veskera data
        fseek(fp, -1, SEEK_CUR);
        fscanf(fp, "%s %d %d", names[n], &moves[n], &wins[n]);
        lines++;
    }
    lines--;
    if (lines == -1) {      //pokud je soubor prazdny ulozi se data hrace a funkce se vrati
        fclose(fp);
        fp = fopen("halloffame.txt", "w");
        fprintf(fp, "%s %d %d\n", name, pocet_tahu, 1);
        fclose(fp);
        return;
    }
     for (int n = 0; n < lines; n++) {         //zkontroluje se zda ma hrac uz v hall of fame zaznam
        if (strcmp(name, names[n]) == 0) {
            moves[n] += pocet_tahu;
            wins[n]++;
            break;
        }
        else if (n == lines-1) {            //pokud ne ulozi se data na konec souboru
            fseek(fp, 0, SEEK_END);
            fprintf(fp, "%s %d %d \n", name, pocet_tahu, 1);
            strcpy(names[lines], name);
            wins[lines] = 1;
            moves[lines] = pocet_tahu;
        }
    }
    char nswap[64];
    int wswap;
    int mswap;
    //sort
    for (int c = 0; c < lines-1; c++)
    {
        for (int d = 0; (d < lines - c - 1); d++)
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
                strcpy(names[d], names[d+1]);
                strcpy(names[d+1], nswap);
            }
        }
    }

    fclose(fp);
    fp = fopen("halloffame.txt", "w");      //soubor se znovu otevre aby se vymazaly stare data
    //vepsani serazenych dat zpet do souboru
    for (int a = 0; wins[a]>0; a++) {
        fprintf(fp, "%s %d %d\n", names[a], moves[a], wins[a]);
    }
    fclose(fp);
    return;

}


void get_names(char names[2][64]) {
    FILE* fp;
    char ch;
    fp = fopen("players.txt", "r");
    if (fp == NULL) {       //pokud zadne predchozi jmena neexistuji nastavi se vychozi hodnota
        fp = fopen("players.txt", "w+");
        fprintf(fp, "%s %s", "player1", "player2");
        fseek(fp, 0, SEEK_SET);
    }
    for (int n = 0; n < 2; n++) {
        fscanf(fp, "%s", names[n]);
    }
    fclose(fp);

    return;
}

//funkce pro kontrolu zda hra jeste muze pokracovat
int check_win(char gamee[26][26], int size) {
    int count = 0;
    int winc = win_value(size);
    for (int n = 0; n < size; n++) {
        for (int k = 0; k < size; k++) {
            if (gamee[n][k] != '*') {       //pokud se v poli najde neprazne policko program zkontroluje zda se v jeho okoli nenachazi stejny znak
                //pokud ano, pokracuje ve smeru toho znaku implementovano ve funkci check surrounding
                count++;
                if (check_surrounding(n, k, gamee[n][k], gamee, winc) == 1) {
                    return 1;
                }
            }
        }
    }
    if (count == size * size) {         //pokud jsou vsechny policka plne hra a nikdo nevyhral hra skoncila remizou
        return -1;
    }
    return 0;    
}


int check_surrounding(int a, int b, char xo, char game[26][26], int win_value) {
    int hm[] = { -1, 0, 1 };            //pole pro urychleni kontroly okoli
    int current = 1;
    for (int n = 0; n < 3; n++) {
        for (int k = 0; k < 3; k++) {       
            current = 1;
            if ((game[a + hm[k]][b + hm[n]] == xo)) {       
                if ((hm[k] == 0 && hm[n] == 0)) {       //nemuze porovnavat samo se sebou, program by vesel do nekonecne smycky
                    break;
                }
                while (game[a + hm[k]][b + hm[n]] == xo) {      //dokud snura znaku pokracuje
                    if ((0 <= a + hm[k] < win_value) && (0 <= b + hm[n] < win_value)) { //kontrola aby hodnota nepresla hranici pole 
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

int win_value(int size) {           //urcuje kolik znaku musi byt za sebou pro vyhru
    int value = (size - 3) / 2 + 3;
    return value;
}
