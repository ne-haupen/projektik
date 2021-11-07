#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "visual.h"
#include "logic.h"

char abc[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char board[26][26];

typedef struct players {
    char names[2][64];
    int pocet_tahu=1;
};

players p;

void name_choice() {
    int choice;
    get_names(p.names);
    while (1) {
        printf("last players: %s, %s\n", p.names[0], p.names[1]);
        printf("1 -> vybrat nove jmena\n");
        printf("2 -> pouzit jmena z minule hry\n");
        printf("3 -> hall of fame\n");
        printf("4 -> exit\n");
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
            exit(1);
        default:
            printf("invalid vyber\n");
        }
    }
}

void new_game(int mode) {
    int first;
    if (mode == 0) {
        memset(p.names[0], 0, strlen(p.names[0]));
        memset(p.names[1], 0, strlen(p.names[1]));
        printf("jmeno prvniho hrace: \n");
        fgets(p.names[0], 63, stdin);
        printf("jmeno druheho hrace: \n");
        fgets(p.names[1], 63, stdin);
        save_data(p.names);
    }
    else {
        get_names(p.names);
    }
    first = player_choice();
    play_screen(first, p.names);
}

void play_screen(int first, char names[2][64]) {
    int input = 0;
    while (input == 0) {
        printf("Zadajte velkost hracej plochy (Najvacsie mozne pole je 15 a najmensie mozne pole je 3): \n");
        scanf_s(" %d", &input);
        while (getchar() != '\n');
        if (input > 26 || input < 3) {
            system("cls");
            input = 0;
        }
        else {
            system("cls");
            clearBoard(input);
            printBoard(input, first);
        }
    }
    while (check_win(board, input) == 0) {
        first = (first + 1) % 2;
        playerInput(first, input);
    }
    first++;
    printf("%s vyhral(a) v %i tazich\n", p.names[first], (p.pocet_tahu)/2);
    hallff_add(p.names[first], (p.pocet_tahu) / 2);
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


void top_players() {
    printf("hall of fame: \n");
    FILE* fd;
    char s;
    fd = fopen("halloffame.txt", "r");
    while ((s = fgetc(fd)) != EOF) {
        printf("%c", s);
    }
    printf("\n\n\n");
    fclose(fd);
    return;
}

void printBoard(int velkostPola, int first) //vypis hracej plochy
{
    printf("%s je na rade \n", p.names[first]);
    printf("* ");
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
    for (int n = 0; n < strlen(abc); n++) {
        if ((letter == abc[n]) || (letter == tolower(abc[n]))) {
            return n;
        }
    }
    return -1;
}

void playerInput(int pIndex, int velkostPola) {
    char xo[] = "XO";
    bool done = false;
    int number, alphaIndex;
    char letter;
    while(done == false){
        printf("Zadajte poziciu v tvare PismenoCislo, alebo najprv Pismeno\n");
        scanf_s(" %c %d", &letter, 1, &number);
        if (letterToIndex(letter) == -1 || (number<1 || number > velkostPola + 2)){
            if (0 < int(letter - '0') <= velkostPola && letterToIndex((char)number) != -1) {
                int placeholder = number;
                number = int(letter - '0');
                letter = (char)placeholder;
                board[number - 1][letterToIndex(letter)] = xo[pIndex];
                done = true;
            }else{
                printf("Zadali ste nespravny index\n\n");
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
    system("cls");
    printBoard(velkostPola, pIndex);
    return;
}
