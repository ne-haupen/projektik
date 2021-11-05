#include "visual.h"
#include "logic.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char abc[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char board[15][15];

void name_choice(){
  int choice;
  while(1){
    printf("1 -> vybrat nove jmena\n");
    printf("2 -> pouzit jmena z minule hry\n");
    printf("3 -> hall of fame\n");
    printf("4 -> exit\n");
    scanf("zvolte cislem: %i\n", &choice);
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
        clear_screen();
        break;
    }
  }
}

void new_game(int mode){
  char names[2][64];
  int name_len[2];
  int first;
  int size;
  if(mode == 0){
    printf("jmeno prvniho hrace: ");
    scanf("%63s\n", names[0]);
    printf("jmeno druheho hrace: ");
    scanf("%63s\n", names[1]);
    for(int n = 0; n<2; n++){
      for(int k = 0; k<64; k++){
        if((names[n][k] < 126) && (names[n][k] > 31)){
          name_len[n]++;
        }else{
          break;
        }
      }
    }
    save_data(names, name_len, "./data/players");
  }else{
    //fixnout
    get_names(names);
  }
  first = player_choice();
  play_screen(first, names);
}

void play_screen(int first, char names[2][64]){
  int input =0;
  while(input==0){
    printf("Zadajte velkost hracej plochy (Najvacsie mozne pole je 15 a najmensie mozne pole je 3): \n");
    scanf("%i", &input);
    printf("%i \n", input);
    if (input > 15 || input < 3){
        system("clear");
        input = 0;
    }
    else{
        system("clear");
        clearBoard(input);
        printBoard(input);
    }
}
  while(check_win(board, input)==0){
    playerInput(first%2, input);
    first++;
  }
  return 0;
}

int player_choice(){
  srand(time(0));
  if(rand()%2==1){
    return 1;
  }else{
    return 0;
  }
}


void top_players(){
  clear_screen();
  printf("hall of fame: \n");
  FILE *fd;
  char s;
  fd = fopen("./data/top_ten", "r");
  while((s=fgetc(fd))!=EOF){
    printf("%c", s);
  }
  fclose(fd);
  return;
}

void printBoard(int velkostPola, board[15][15]) //vypis hracej plochy
{
    printf("* ");
    for(int n=0; n< velkostPola; n++){
      printf("%c ", abc[n]);
    }
    printf("\n");
    for (int j = 0; j < velkostPola; j++)
    {
        printf("%i ", j+1);

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
    for(int n=0; n<strlen(abc); n++){
      if((letter == abc[n])||(letter == tolower(abc[n]))){
        return n;
      }
    }
    return -1;
}

void playerInput(int pIndex, int velkostPola){
  char xo[] = "XO";
  indexAlpha:
  printf("Zadajte poziciu v tvare PismenoCislo, alebo najprv Pismeno\n");
  int number =0;
  char letter;
  scanf("%c%i", &letter, &number);
  if (letterToIndex(letter) == -1 || (number<1 || number > velkostPola+2))
  {
      if(0<(int)letter<=velkostPola && letterToIndex((char)number)!=-1){
        int placeholder = number;
        number = (int)letter;
        letter = (char)number;
      }else{
        printf("tadyZadali ste nespravny index\n\n");
        goto indexAlpha;
      }
  }
  else
  {
    int alphaIndex = letterToIndex(letter);
    if (board[number-1][alphaIndex] != '*')
    {
        printf("Na mieste s tymito suradnicami sa uz nachadza X/O");
        goto indexAlpha;
    }
    board[number-1][alphaIndex] = xo[pIndex];
}
  system("clear");
  printBoard(velkostPola);
}
