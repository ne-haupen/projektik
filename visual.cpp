#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "visual.h"
#include "logic.h"
#include "bot.h"

char board[26][26];

typedef struct players {
    char names[2][64];
    int pocet_tahu=1;
};

players p;

void name_choice() {
    int choice;
    get_names(p.names); //ulozi do promenych jmena hracu z minule hry
    printf("last players: %s, %s\n", p.names[0], p.names[1]);
    while (1) {
        printf("1 -> vybrat nove jmena\n");
        printf("2 -> pouzit jmena z minule hry\n");
        printf("3 -> hall of fame\n");
        printf("4 -> hra proti botovi\n");
        printf("5 -> exit\n");
        printf("vyber: ");
        scanf_s(" %d", &choice);
        while (getchar() != '\n');
        switch (choice) {
        case 1:
            new_game(0);
            break;
        case 2:
            new_game(1);
            break;
        case 3:
            top_players();
            break;
        case 4:
            new_game(2);
            break;
        case 5:
            exit(1);
        default:
            printf("invalid vyber\n");
        }
    }
}

void against_bot(int board_size){
    int needed = win_value(board_size);
    int moves[2] = { 0,0 };
    //needed je hodnota pro funkci minimax
    //redukuje hraci plochu jen na pocet policek potrebnych pro vyhru
    if (needed % 2 == 0) {
        needed++;
    }
    strcpy(p.names[1], "clovek");
    system("cls");
    clearBoard(board_size);
    printBoard(board_size, 1);

    while (check_win(board, board_size) == 0) {
        playerInput(1, board_size);
        if (check_win(board, board_size) != 0) {
            printf("clovek vyhral(a) v %i tazich\n",(p.pocet_tahu)/2);
            break;
        }
        else if (check_win(board, board_size) == -1) {
            printf("remiza");
            break;
        }
        if (computer_move(board, board_size, needed, moves) == -1) {
            printf("surrender\n ");
            break;
        }
        board[moves[0]][moves[1]] = 'O';
        p.pocet_tahu++;
        printBoard(board_size, 1);
    }
    exit_menu();
    return;
}

//mody jsou dva podle zpusobu zadavani jmen
//mod 0 umoznuje hracum vybrat nove jmena
//mod 1 pouzije jmena ulozene z minule hry
//mod 2 spusti hru s botem
void new_game(int mode) {
    int first, input;
    switch(mode){
    case 0:
        memset(p.names[0], 0, strlen(p.names[0]));
        memset(p.names[1], 0, strlen(p.names[1]));
        printf("jmeno prvniho hrace: \n");
        fgets(p.names[0], 63, stdin);
        printf("jmeno druheho hrace: \n");
        fgets(p.names[1], 63, stdin);
        save_data(p.names);     //po vyberu novych jmen se jmena ulozi
        break;
    case 1:
        get_names(p.names);
        break;
    case 2:
        input = board_size();
        against_bot(input);
        break;
    }
    if (mode != 2) {
        play_screen(p.names);
    }
    return;
}

void exit_menu() {
    printf("1 -> exit\n");
    printf("2 -> nova hra\n");
    int choice = 0;
    scanf_s(" %d", &choice);
    if (choice == 1) {
        exit(1);
    }
    system("cls");
    return;
}
void play_screen(char names[2][64]) {
    int input = board_size();       //umozni hracum vybrat velikost hraciho pole
    system("cls");
    clearBoard(input);      //pripravi hraci pole podle velikosti hraci plochy
    int first = player_choice();    //nahodne se vybere prvni na rade
    printBoard(input, first);       //vypise se hraci pole s nazvem hrace na tahu
    //samotna hra
    while (check_win(board, input) == 0) {
        first = (first + 1) % 2;
        playerInput(first, input);
    }
    system("cls");

    //pokud nekdo vyhral zaznamena se v hall of fame
    if (check_win(board, input) == 1) {
        first = (first + 1) % 2;
        hallff_add(p.names[first], (p.pocet_tahu) / 2);
        printf("%s vyhral(a) v %i tazich\n", p.names[first], (p.pocet_tahu) / 2);
    }else if(check_win(board, input == -1)){
        printf("remiza\n");
    }
    exit_menu;
    return;
}

int player_choice() {
    srand(time(0));
    if (rand() % 2 == 1) {
        return 1;
    }
    else {
        return 0;
    }
}

int board_size() {
    int input = 0;
    while (input == 0) {
        printf("Zadajte velkost hracej plochy (Najvacsie mozne pole je 26 a najmensie mozne pole je 3): \n");
        scanf_s(" %d", &input);
        while (getchar() != '\n');
        if (input > 26 || input < 3) {
            system("cls");
            input = 0;
        }
    }
    return input;
}


void top_players(){
    printf("\nhall of fame: \n");
    FILE* fd;
    char name[64], ch;
    int moves, win;
    int count = 0;
    fd = fopen("halloffame.txt", "r");
    while ((ch = fgetc(fd)) != EOF) {
        if (ch == '\n')
            count++;
    }
    fseek(fd, 0, SEEK_SET);
    for (int n = 0; n<count; n++) {
        fseek(fd, 0, SEEK_CUR);
        fscanf(fd, "%s %d %d", name, &moves, &win);     //fcan pouzit aby bylo mozne printnout m: W: k datum. pro lepsi orientaci.
        printf("%s m:%d W:%d\n", name, moves, win);
    }
    printf("\n\n\n");
    fclose(fd);
    return;
}

void printBoard(int velkostPola, int first) //vypis hracej plochy
{
    system("cls");
    char abc[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (first != -1) {
        printf("%s je na rade \n", p.names[first]);
    }
    printf("*  ");
    for (int n = 0; n < velkostPola; n++) {
        printf("%c ", abc[n]);
    }
    printf("\n");
    for (int j = 0; j < velkostPola; j++)
    {
        if (j < 9) {
            printf(" %i ", j + 1);
        }
        else {
            printf("%i ", j + 1);
        }

        for (int i = 0; i < velkostPola; i++)
        {
            printf("%c ", board[j][i]);
        }
        printf("\n");
    }
}

//pole ma pevnou velikost 26, podle uzivatelskeho vyberu se pak pracuje jen s casti pole.
void clearBoard(int velkostPola) //vynulovanie hracej plochy
{
    for (int j = 0; j < velkostPola; j++)
    {
        for (int i = 0; i < velkostPola; i++)
        {
            board[j][i] = '*';
        }
    }
}

int letterToIndex(char letter)
{
    char abc[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int n = 0; n < strlen(abc); n++) {
        if ((letter == abc[n]) || (letter == tolower(abc[n]))) {
            return n;
        }
    }
    return -1;
}

void playerInput(int pIndex, int velkostPola) {
    char xo[] = "OX";
    bool done = false;
    int number;
    int alphaIndex;
    char letter;
    while(done == false){
        number = 0;
        letter = ' ';
        printf("Zadajte poziciu v tvare PismenoCislo, alebo najprv Pismeno\n");
        scanf_s(" %c%d", &letter, 1, &number);
        if (letterToIndex(letter) == -1 || (number<1 || number > velkostPola + 2)){
            //zkontroluje se zda uzivatel nezadal pozici naopak.
            if (0 < int(letter - '0') <= velkostPola && letterToIndex((char)number) != -1) {
                int placeholder = number;
                number = int(letter - '0');
                letter = (char)placeholder;
                board[number - 1][letterToIndex(letter)] = xo[pIndex];
                done = true;
            }else{
                printf("Zadali ste nespravny index\n");
                //printf("%c %d\n", letter, number);
            }
        }else{
            if (board[number - 1][letterToIndex(letter)] != '*'){
                printf("Na mieste s tymito suradnicami sa uz nachadza X/O\n");
            }else {
                board[number - 1][letterToIndex(letter)] = xo[pIndex];
                done = true;
            }
        }
    }
    p.pocet_tahu++;
    printBoard(velkostPola, pIndex);
    return;
}
